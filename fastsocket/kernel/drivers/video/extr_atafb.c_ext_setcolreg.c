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
struct fb_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DACDelay ; 
#define  IS_MV300 129 
#define  IS_VGA 128 
 int* MV300_reg ; 
 int /*<<< orphan*/  OUTB (int,unsigned int) ; 
 int external_bitspercol ; 
 int external_card_type ; 
 int /*<<< orphan*/  external_vgaiobase ; 

__attribute__((used)) static int ext_setcolreg(unsigned int regno, unsigned int red,
			 unsigned int green, unsigned int blue,
			 unsigned int transp, struct fb_info *info)
{
	unsigned char colmask = (1 << external_bitspercol) - 1;

	if (!external_vgaiobase)
		return 1;

	switch (external_card_type) {
	case IS_VGA:
		OUTB(0x3c8, regno);
		DACDelay;
		OUTB(0x3c9, red & colmask);
		DACDelay;
		OUTB(0x3c9, green & colmask);
		DACDelay;
		OUTB(0x3c9, blue & colmask);
		DACDelay;
		return 0;

	case IS_MV300:
		OUTB((MV300_reg[regno] << 2) + 1, red);
		OUTB((MV300_reg[regno] << 2) + 1, green);
		OUTB((MV300_reg[regno] << 2) + 1, blue);
		return 0;

	default:
		return 1;
	}
}