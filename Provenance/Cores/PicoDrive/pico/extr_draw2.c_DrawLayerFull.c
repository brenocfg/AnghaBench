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
struct TYPE_2__ {int* vram; int* vsram; struct PicoVideo video; } ;

/* Variables and functions */
 int LINE_WIDTH ; 
 TYPE_1__ Pico ; 
 unsigned char* PicoDraw2FB ; 
 int START_ROW ; 
 int TileXflipYflip (unsigned char*,int,unsigned char) ; 
 int TileXflipYnorm (unsigned char*,int,unsigned char) ; 
 int TileXnormYflip (unsigned char*,int,unsigned char) ; 
 int TileXnormYnorm (unsigned char*,int,unsigned char) ; 

__attribute__((used)) static void DrawLayerFull(int plane, int *hcache, int planestart, int planeend)
{
	struct PicoVideo *pvid=&Pico.video;
	static char shift[4]={5,6,6,7}; // 32,64 or 128 sized tilemaps
	int width, height, ymask, htab;
	int nametab, hscroll=0, vscroll, cells;
	unsigned char *scrpos;
	int blank=-1, xmask, nametab_row, trow;

	// parse ranges
	cells = (planeend>>16)-(planestart>>16);
	planestart = planestart<<16>>16;
	planeend = planeend<<16>>16;

	// Work out the Tiles to draw

	htab=pvid->reg[13]<<9; // Horizontal scroll table address
//	if ( pvid->reg[11]&2)     htab+=Scanline<<1; // Offset by line
//	if ((pvid->reg[11]&1)==0) htab&=~0xf; // Offset by tile
	htab+=plane; // A or B

	if(!(pvid->reg[11]&3)) { // full screen scroll
		// Get horizontal scroll value
		hscroll=Pico.vram[htab&0x7fff];
		htab = 0; // this marks that we don't have to update scroll value
	}

	// Work out the name table size: 32 64 or 128 tiles (0-3)
	width=pvid->reg[16];
	height=(width>>4)&3; width&=3;

	xmask=(1<<shift[width ])-1; // X Mask in tiles
	ymask=(height<<5)|0x1f;     // Y Mask in tiles
	if(width == 1)   ymask&=0x3f;
	else if(width>1) ymask =0x1f;

	// Find name table:
	if (plane==0) nametab=(pvid->reg[2]&0x38)<< 9; // A
	else          nametab=(pvid->reg[4]&0x07)<<12; // B

	scrpos = PicoDraw2FB;
	scrpos+=8*LINE_WIDTH*(planestart-START_ROW);

	// Get vertical scroll value:
	vscroll=Pico.vsram[plane]&0x1ff;
	scrpos+=(8-(vscroll&7))*LINE_WIDTH;
	if(vscroll&7) planeend++; // we have vertically clipped tiles due to vscroll, so we need 1 more row

	*hcache++ = 8-(vscroll&7); // push y-offset to tilecache


	for(trow = planestart; trow < planeend; trow++) { // current tile row
		int cellc=cells,tilex,dx;

		// Find the tile row in the name table
		//ts.line=(vscroll+Scanline)&ymask;
		//ts.nametab+=(ts.line>>3)<<shift[width];
		nametab_row = nametab + (((trow+(vscroll>>3))&ymask)<<shift[width]); // pointer to nametable entries for this row

		// update hscroll if needed
		if(htab) {
			int htaddr=htab+(trow<<4);
			if(trow) htaddr-=(vscroll&7)<<1;
			hscroll=Pico.vram[htaddr&0x7fff];
		}

		// Draw tiles across screen:
		tilex=(-hscroll)>>3;
		dx=((hscroll-1)&7)+1;
		if(dx != 8) cellc++; // have hscroll, do more cells

		for (; cellc; dx+=8,tilex++,cellc--)
		{
			int code=0,addr=0,zero=0;
//			unsigned short *pal=NULL;
			unsigned char pal;

			code=Pico.vram[nametab_row+(tilex&xmask)];
			if (code==blank) continue;

			if (code>>15) { // high priority tile
				*hcache++ = code|(dx<<16)|(trow<<27); // cache it
				continue;
			}

			// Get tile address/2:
			addr=(code&0x7ff)<<4;

//			pal=PicoCramHigh+((code>>9)&0x30);
			pal=(unsigned char)((code>>9)&0x30);

			switch((code>>11)&3) {
				case 0: zero=TileXnormYnorm(scrpos+dx,addr,pal); break;
				case 1: zero=TileXflipYnorm(scrpos+dx,addr,pal); break;
				case 2: zero=TileXnormYflip(scrpos+dx,addr,pal); break;
				case 3: zero=TileXflipYflip(scrpos+dx,addr,pal); break;
			}
			if(zero) blank=code; // We know this tile is blank now
		}

		scrpos += LINE_WIDTH*8;
	}

	*hcache = 0; // terminate cache
}