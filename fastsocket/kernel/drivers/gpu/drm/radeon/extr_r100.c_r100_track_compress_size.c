#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
#define  R100_TRACK_COMP_DXT1 129 
#define  R100_TRACK_COMP_DXT35 128 

__attribute__((used)) static int r100_track_compress_size(int compress_format, int w, int h)
{
	int block_width, block_height, block_bytes;
	int wblocks, hblocks;
	int min_wblocks;
	int sz;

	block_width = 4;
	block_height = 4;

	switch (compress_format) {
	case R100_TRACK_COMP_DXT1:
		block_bytes = 8;
		min_wblocks = 4;
		break;
	default:
	case R100_TRACK_COMP_DXT35:
		block_bytes = 16;
		min_wblocks = 2;
		break;
	}

	hblocks = (h + block_height - 1) / block_height;
	wblocks = (w + block_width - 1) / block_width;
	if (wblocks < min_wblocks)
		wblocks = min_wblocks;
	sz = wblocks * hblocks * block_bytes;
	return sz;
}