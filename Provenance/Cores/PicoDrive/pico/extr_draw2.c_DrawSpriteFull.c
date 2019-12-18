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
 int END_ROW ; 
 int LINE_WIDTH ; 
 unsigned char* PicoDraw2FB ; 
 int START_ROW ; 
 int /*<<< orphan*/  TileXflipYflip (unsigned char*,int,unsigned char) ; 
 int /*<<< orphan*/  TileXflipYnorm (unsigned char*,int,unsigned char) ; 
 int /*<<< orphan*/  TileXnormYflip (unsigned char*,int,unsigned char) ; 
 int /*<<< orphan*/  TileXnormYnorm (unsigned char*,int,unsigned char) ; 

__attribute__((used)) static void DrawSpriteFull(unsigned int *sprite)
{
	int width=0,height=0;
//	unsigned short *pal=NULL;
	unsigned char pal;
	int tile,code,tdeltax,tdeltay;
	unsigned char *scrpos;
	int sx, sy;

	sy=sprite[0];
	height=sy>>24;
	sy=(sy&0x1ff)-0x78; // Y
	width=(height>>2)&3; height&=3;
	width++; height++; // Width and height in tiles

	code=sprite[1];
	sx=((code>>16)&0x1ff)-0x78; // X

	tile=code&0x7ff; // Tile number
	tdeltax=height; // Delta to increase tile by going right
	tdeltay=1;      // Delta to increase tile by going down
	if (code&0x0800) { tdeltax=-tdeltax; tile+=height*(width-1); } // Flip X
	if (code&0x1000) { tdeltay=-tdeltay; tile+=height-1; } // Flip Y

	//delta<<=4; // Delta of address
//	pal=PicoCramHigh+((code>>9)&0x30); // Get palette pointer
	pal=(unsigned char)((code>>9)&0x30);

	// goto first vertically visible tile
	while(sy <= START_ROW*8) { sy+=8; tile+=tdeltay; height--; }

	scrpos = PicoDraw2FB;
	scrpos+=(sy-START_ROW*8)*LINE_WIDTH;

	for (; height > 0; height--, sy+=8, tile+=tdeltay)
	{
		int w = width, x=sx, t=tile;

		if(sy >= END_ROW*8+8) return; // offscreen

		for (; w; w--,x+=8,t+=tdeltax)
		{
			if(x<=0)   continue;
			if(x>=328) break; // Offscreen

			t&=0x7fff; // Clip tile address
			switch((code>>11)&3) {
				case 0: TileXnormYnorm(scrpos+x,t<<4,pal); break;
				case 1: TileXflipYnorm(scrpos+x,t<<4,pal); break;
				case 2: TileXnormYflip(scrpos+x,t<<4,pal); break;
				case 3: TileXflipYflip(scrpos+x,t<<4,pal); break;
			}
		}

		scrpos+=8*LINE_WIDTH;
	}
}