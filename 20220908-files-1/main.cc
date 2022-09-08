#include <iostream>
#include <fstream>
#include <cstdint>
#include <vector>
#include <cmath>

const int32_t WIDTH = 800, HEIGHT = 600;

#pragma pack(push, 1)
struct BMPHEADER
{
	char id[2];
	uint32_t file_size;
	uint16_t res1, res2;
	uint32_t pic_offset;
};

struct BITMAPINFOHEADER
{
	uint32_t hdr_size;
	int32_t  width;
	int32_t  height;
	uint16_t planes;
	uint16_t bpp;
	uint32_t comp;
	uint32_t img_size;
	uint32_t resh;
	uint32_t resv;
	uint32_t pal_size;
	uint32_t pal_used;
};
#pragma pack(pop)

int main()
{
	BMPHEADER h1;
	BITMAPINFOHEADER h2;

	h1.id[0] = 'B';
	h1.id[1] = 'M';
	h1.file_size = sizeof(BMPHEADER) +
			sizeof(BITMAPINFOHEADER) +
			WIDTH * HEIGHT * 4;
	h1.res1 = h1.res2 = 0;
	h1.pic_offset = sizeof(BMPHEADER) +
			sizeof(BITMAPINFOHEADER);

	h2.hdr_size = 40;
	h2.width = WIDTH;
	h2.height = HEIGHT;
	h2.planes = 1;
	h2.bpp = 32;
	h2.comp = 0;
	h2.resh = 2048;
	h2.resv = 2048;
	h2.pal_size = 0;
	h2.pal_used = 0;
	h2.img_size = 0; // dummy

	std::vector<uint32_t> pixels(WIDTH * HEIGHT);
	for(auto &&p: pixels) p = 0xff000000;


//	for (int x = 200; x < 600; ++x) {
//		for (int y = 100; y < 200; ++y)
//			pixels[y*WIDTH + x] = 0xffd52b1e;
//		for (int y = 200; y < 300; ++y)
//			pixels[y*WIDTH + x] = 0xff0039a6;
//		for (int y = 300; y < 400; ++y)
//			pixels[y*WIDTH + x] = 0xffffffff;
//	}

	for (int x = 0; x < 800; ++x) {
		int y = int(300+250*cos(x / 40.0));
		pixels[y*WIDTH + x] = 0xffffffff;
		pixels[y*WIDTH + x+1] = 0xff00ff00;
		pixels[y*WIDTH + x+2] = 0xffff00ff;
	}






	std::ofstream bmp_file { "test.bmp", std::ios::binary };
	bmp_file.write(
			reinterpret_cast<const char*>(&h1),
			sizeof(h1));
	bmp_file.write(
			reinterpret_cast<const char*>(&h2),
			sizeof(h2));
	bmp_file.write(
			reinterpret_cast<const char*>(&pixels[0]),
			sizeof(uint32_t)*pixels.size());
	bmp_file.close();

	return 0;
}
