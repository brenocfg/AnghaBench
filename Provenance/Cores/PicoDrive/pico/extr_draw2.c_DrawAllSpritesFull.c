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
struct TYPE_2__ {scalar_t__ vram; struct PicoVideo video; } ;

/* Variables and functions */
 int /*<<< orphan*/  DrawSpriteFull (unsigned int*) ; 
 int END_ROW ; 
 TYPE_1__ Pico ; 
 int START_ROW ; 

__attribute__((used)) static void DrawAllSpritesFull(int prio, int maxwidth)
{
	struct PicoVideo *pvid=&Pico.video;
	int table=0,maskrange=0;
	int i,u,link=0;
	unsigned int *sprites[80]; // Sprites
	int y_min=START_ROW*8, y_max=END_ROW*8; // for a simple sprite masking

	table=pvid->reg[5]&0x7f;
	if (pvid->reg[12]&1) table&=0x7e; // Lowest bit 0 in 40-cell mode
	table<<=8; // Get sprite table address/2

	for (i=u=0; u < 80; u++)
	{
		unsigned int *sprite=NULL;
		int code, code2, sx, sy, height;

		sprite=(unsigned int *)(Pico.vram+((table+(link<<2))&0x7ffc)); // Find sprite

		// get sprite info
		code = sprite[0];

		// check if it is not hidden vertically
		sy = (code&0x1ff)-0x80;
		height = (((code>>24)&3)+1)<<3;
		if(sy+height <= y_min || sy > y_max) goto nextsprite;

		// masking sprite?
		code2=sprite[1];
		sx = (code2>>16)&0x1ff;
		if(!sx) {
			int to = sy+height; // sy ~ from
			if(maskrange) {
				// try to merge with previous range
				if((maskrange>>16)+1 >= sy && (maskrange>>16) <= to && (maskrange&0xffff) < sy) sy = (maskrange&0xffff);
				else if((maskrange&0xffff)-1 <= to && (maskrange&0xffff) >= sy && (maskrange>>16) > to) to = (maskrange>>16);
			}
			// support only very simple masking (top and bottom of screen)
			if(sy <= y_min && to+1 > y_min) y_min = to+1;
			else if(to >= y_max && sy-1 < y_max) y_max = sy-1;
			else maskrange=sy|(to<<16);

			goto nextsprite;
		}

		// priority
		if(((code2>>15)&1) != prio) goto nextsprite; // wrong priority

		// check if sprite is not hidden horizontally
		sx -= 0x78; // Get X coordinate + 8
		if(sx <= -8*3 || sx >= maxwidth) goto nextsprite;

		// sprite is good, save it's index
		sprites[i++]=sprite;

		nextsprite:
		// Find next sprite
		link=(code>>16)&0x7f;
		if(!link) break; // End of sprites
	}

	// Go through sprites backwards:
	for (i-- ;i>=0; i--)
	{
		DrawSpriteFull(sprites[i]);
	}
}