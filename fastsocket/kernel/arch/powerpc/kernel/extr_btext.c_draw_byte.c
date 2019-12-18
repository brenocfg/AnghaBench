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
 unsigned char* calc_base (long,long) ; 
 int dispDeviceDepth ; 
 int dispDeviceRowBytes ; 
 int /*<<< orphan*/  draw_byte_16 (unsigned char*,unsigned int*,int) ; 
 int /*<<< orphan*/  draw_byte_32 (unsigned char*,unsigned int*,int) ; 
 int /*<<< orphan*/  draw_byte_8 (unsigned char*,unsigned int*,int) ; 
 unsigned char* vga_font ; 

__attribute__((used)) static void draw_byte(unsigned char c, long locX, long locY)
{
	unsigned char *base	= calc_base(locX << 3, locY << 4);
	unsigned char *font	= &vga_font[((unsigned int)c) * 16];
	int rb			= dispDeviceRowBytes;

	switch(dispDeviceDepth) {
	case 24:
	case 32:
		draw_byte_32(font, (unsigned int *)base, rb);
		break;
	case 15:
	case 16:
		draw_byte_16(font, (unsigned int *)base, rb);
		break;
	case 8:
		draw_byte_8(font, (unsigned int *)base, rb);
		break;
	}
}