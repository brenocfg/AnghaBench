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
struct vga16fb_par {scalar_t__ isVGA; } ;
struct TYPE_2__ {int grayscale; } ;
struct fb_info {TYPE_1__ var; struct vga16fb_par* par; } ;

/* Variables and functions */
 int /*<<< orphan*/  ega16_setpalette (unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  vga16_setpalette (unsigned int,unsigned int,unsigned int,unsigned int) ; 

__attribute__((used)) static int vga16fb_setcolreg(unsigned regno, unsigned red, unsigned green,
			     unsigned blue, unsigned transp,
			     struct fb_info *info)
{
	struct vga16fb_par *par = info->par;
	int gray;

	/*
	 *  Set a single color register. The values supplied are
	 *  already rounded down to the hardware's capabilities
	 *  (according to the entries in the `var' structure). Return
	 *  != 0 for invalid regno.
	 */
	
	if (regno >= 256)
		return 1;

	gray = info->var.grayscale;
	
	if (gray) {
		/* gray = 0.30*R + 0.59*G + 0.11*B */
		red = green = blue = (red * 77 + green * 151 + blue * 28) >> 8;
	}
	if (par->isVGA) 
		vga16_setpalette(regno,red,green,blue);
	else
		ega16_setpalette(regno,red,green,blue);
	return 0;
}