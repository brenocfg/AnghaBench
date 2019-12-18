#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sh_mobile_lcdc_chan {int new_pan_offset; int pan_offset; int /*<<< orphan*/  lcdc; } ;
struct fb_var_screeninfo {int xoffset; int yoffset; } ;
struct TYPE_4__ {int xoffset; int yoffset; int bits_per_pixel; } ;
struct TYPE_3__ {int line_length; } ;
struct fb_info {TYPE_2__ var; TYPE_1__ fix; struct sh_mobile_lcdc_chan* par; } ;

/* Variables and functions */
 unsigned long LDINTR_VEE ; 
 int /*<<< orphan*/  _LDINTR ; 
 unsigned long lcdc_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lcdc_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  sh_mobile_lcdc_deferred_io_touch (struct fb_info*) ; 

__attribute__((used)) static int sh_mobile_fb_pan_display(struct fb_var_screeninfo *var,
				     struct fb_info *info)
{
	struct sh_mobile_lcdc_chan *ch = info->par;

	if (info->var.xoffset == var->xoffset &&
	    info->var.yoffset == var->yoffset)
		return 0;	/* No change, do nothing */

	ch->new_pan_offset = (var->yoffset * info->fix.line_length) +
		(var->xoffset * (info->var.bits_per_pixel / 8));

	if (ch->new_pan_offset != ch->pan_offset) {
		unsigned long ldintr;
		ldintr = lcdc_read(ch->lcdc, _LDINTR);
		ldintr |= LDINTR_VEE;
		lcdc_write(ch->lcdc, _LDINTR, ldintr);
		sh_mobile_lcdc_deferred_io_touch(info);
	}

	return 0;
}