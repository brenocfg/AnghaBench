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
 unsigned int IMS332_REG_COLOR_PALETTE ; 
 int /*<<< orphan*/  maxinefb_ims332_write_register (unsigned int,unsigned long) ; 

__attribute__((used)) static int maxinefb_setcolreg(unsigned regno, unsigned red, unsigned green,
			      unsigned blue, unsigned transp, struct fb_info *info)
{
	/* value to be written into the palette reg. */
	unsigned long hw_colorvalue = 0;

	red   >>= 8;    /* The cmap fields are 16 bits    */
	green >>= 8;    /* wide, but the harware colormap */
	blue  >>= 8;    /* registers are only 8 bits wide */

	hw_colorvalue = (blue << 16) + (green << 8) + (red);

	maxinefb_ims332_write_register(IMS332_REG_COLOR_PALETTE + regno,
				       hw_colorvalue);
	return 0;
}