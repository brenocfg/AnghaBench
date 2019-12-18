#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct PicoVideo {int* reg; } ;
struct TYPE_2__ {int* vram; struct PicoVideo video; } ;

/* Variables and functions */
 int LINE_WIDTH ; 
 TYPE_1__ Pico ; 
 unsigned char* PicoDraw2FB ; 
 int START_ROW ; 
 int TileXflipYflip (unsigned char*,int,unsigned char) ; 
 int TileXflipYnorm (unsigned char*,int,unsigned char) ; 
 int TileXnormYflip (unsigned char*,int,unsigned char) ; 
 int TileXnormYnorm (unsigned char*,int,unsigned char) ; 

__attribute__((used)) static void DrawWindowFull(int start, int end, int prio)
{
	struct PicoVideo *pvid=&Pico.video;
	int nametab, nametab_step, trow, tilex, blank=-1, code;
	unsigned char *scrpos = PicoDraw2FB;
	int tile_start, tile_end; // in cells

	// parse ranges
	tile_start = start>>16;
	tile_end = end>>16;
	start = start<<16>>16;
	end = end<<16>>16;

	// Find name table line:
	if (pvid->reg[12]&1)
	{
		nametab=(pvid->reg[3]&0x3c)<<9; // 40-cell mode
		nametab_step = 1<<6;
	}
	else
	{
		nametab=(pvid->reg[3]&0x3e)<<9; // 32-cell mode
		nametab_step = 1<<5;
	}
	nametab += nametab_step*start;

	// check priority
	code=Pico.vram[nametab+tile_start];
	if ((code>>15) != prio) return; // hack: just assume that whole window uses same priority

	scrpos+=8*LINE_WIDTH+8;
	scrpos+=8*LINE_WIDTH*(start-START_ROW);

	// do a window until we reach planestart row
	for(trow = start; trow < end; trow++, nametab+=nametab_step) { // current tile row
		for (tilex=tile_start; tilex<tile_end; tilex++)
		{
			int code,addr,zero=0;
//			unsigned short *pal=NULL;
			unsigned char pal;

			code=Pico.vram[nametab+tilex];
			if (code==blank) continue;

			// Get tile address/2:
			addr=(code&0x7ff)<<4;

//			pal=PicoCramHigh+((code>>9)&0x30);
			pal=(unsigned char)((code>>9)&0x30);

			switch((code>>11)&3) {
				case 0: zero=TileXnormYnorm(scrpos+(tilex<<3),addr,pal); break;
				case 1: zero=TileXflipYnorm(scrpos+(tilex<<3),addr,pal); break;
				case 2: zero=TileXnormYflip(scrpos+(tilex<<3),addr,pal); break;
				case 3: zero=TileXflipYflip(scrpos+(tilex<<3),addr,pal); break;
			}
			if(zero) blank=code; // We know this tile is blank now
		}

		scrpos += LINE_WIDTH*8;
	}
}