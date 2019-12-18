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
struct fb_var_screeninfo {int bits_per_pixel; int yoffset; int xres_virtual; int xoffset; } ;
struct TYPE_2__ {int line_length; } ;
struct fb_info {TYPE_1__ fix; } ;

/* Variables and functions */
 int /*<<< orphan*/  svga_wcrt_multi (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  vt8623_start_address_regs ; 

__attribute__((used)) static int vt8623fb_pan_display(struct fb_var_screeninfo *var, struct fb_info *info)
{
	unsigned int offset;

	/* Calculate the offset */
	if (var->bits_per_pixel == 0) {
		offset = (var->yoffset / 16) * var->xres_virtual + var->xoffset;
		offset = offset >> 3;
	} else {
		offset = (var->yoffset * info->fix.line_length) +
			 (var->xoffset * var->bits_per_pixel / 8);
		offset = offset >> ((var->bits_per_pixel == 4) ? 2 : 1);
	}

	/* Set the offset */
	svga_wcrt_multi(vt8623_start_address_regs, offset);

	return 0;
}