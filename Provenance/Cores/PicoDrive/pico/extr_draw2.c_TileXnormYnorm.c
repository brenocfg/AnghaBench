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
struct TYPE_2__ {scalar_t__ vram; } ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_WIDTH ; 
 TYPE_1__ Pico ; 

__attribute__((used)) static int TileXnormYnorm(unsigned char *pd,int addr,unsigned char pal)
{
	unsigned int pack=0; unsigned int t=0, blank = 1;
	int i;

	for(i=8; i; i--, addr+=2, pd += LINE_WIDTH) {
		pack=*(unsigned int *)(Pico.vram+addr); // Get 8 pixels
		if(!pack) continue;

		t=pack&0x0000f000; if (t) pd[0]=(unsigned char)((t>>12)|pal);
		t=pack&0x00000f00; if (t) pd[1]=(unsigned char)((t>> 8)|pal);
		t=pack&0x000000f0; if (t) pd[2]=(unsigned char)((t>> 4)|pal);
		t=pack&0x0000000f; if (t) pd[3]=(unsigned char)((t    )|pal);
		t=pack&0xf0000000; if (t) pd[4]=(unsigned char)((t>>28)|pal);
		t=pack&0x0f000000; if (t) pd[5]=(unsigned char)((t>>24)|pal);
		t=pack&0x00f00000; if (t) pd[6]=(unsigned char)((t>>20)|pal);
		t=pack&0x000f0000; if (t) pd[7]=(unsigned char)((t>>16)|pal);
		blank = 0;
	}

	return blank; // Tile blank?
}