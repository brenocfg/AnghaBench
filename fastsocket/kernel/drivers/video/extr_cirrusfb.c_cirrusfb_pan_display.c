#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct fb_var_screeninfo {int vmode; int xoffset; int yoffset; } ;
struct TYPE_5__ {int bits_per_pixel; } ;
struct TYPE_4__ {int line_length; } ;
struct fb_info {TYPE_2__ var; TYPE_1__ fix; struct cirrusfb_info* par; } ;
struct cirrusfb_info {size_t btype; int /*<<< orphan*/  regbase; } ;
struct TYPE_6__ {scalar_t__ scrn_start_bit19; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_AR33 ; 
 int /*<<< orphan*/  CL_CRT1B ; 
 int /*<<< orphan*/  CL_CRT1D ; 
 int EINVAL ; 
 int FB_VMODE_YWRAP ; 
 int /*<<< orphan*/  VGA_CRTC_START_HI ; 
 int /*<<< orphan*/  VGA_CRTC_START_LO ; 
 int /*<<< orphan*/  cirrusfb_WaitBLT (int /*<<< orphan*/ ) ; 
 TYPE_3__* cirrusfb_board_info ; 
 scalar_t__ is_laguna (struct cirrusfb_info*) ; 
 int vga_rcrt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vga_wattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  vga_wcrt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int cirrusfb_pan_display(struct fb_var_screeninfo *var,
				struct fb_info *info)
{
	int xoffset;
	unsigned long base;
	unsigned char tmp, xpix;
	struct cirrusfb_info *cinfo = info->par;

	/* no range checks for xoffset and yoffset,   */
	/* as fb_pan_display has already done this */
	if (var->vmode & FB_VMODE_YWRAP)
		return -EINVAL;

	xoffset = var->xoffset * info->var.bits_per_pixel / 8;

	base = var->yoffset * info->fix.line_length + xoffset;

	if (info->var.bits_per_pixel == 1) {
		/* base is already correct */
		xpix = (unsigned char) (var->xoffset % 8);
	} else {
		base /= 4;
		xpix = (unsigned char) ((xoffset % 4) * 2);
	}

	if (!is_laguna(cinfo))
		cirrusfb_WaitBLT(cinfo->regbase);

	/* lower 8 + 8 bits of screen start address */
	vga_wcrt(cinfo->regbase, VGA_CRTC_START_LO, base & 0xff);
	vga_wcrt(cinfo->regbase, VGA_CRTC_START_HI, (base >> 8) & 0xff);

	/* 0xf2 is %11110010, exclude tmp bits */
	tmp = vga_rcrt(cinfo->regbase, CL_CRT1B) & 0xf2;
	/* construct bits 16, 17 and 18 of screen start address */
	if (base & 0x10000)
		tmp |= 0x01;
	if (base & 0x20000)
		tmp |= 0x04;
	if (base & 0x40000)
		tmp |= 0x08;

	vga_wcrt(cinfo->regbase, CL_CRT1B, tmp);

	/* construct bit 19 of screen start address */
	if (cirrusfb_board_info[cinfo->btype].scrn_start_bit19) {
		tmp = vga_rcrt(cinfo->regbase, CL_CRT1D);
		if (is_laguna(cinfo))
			tmp = (tmp & ~0x18) | ((base >> 16) & 0x18);
		else
			tmp = (tmp & ~0x80) | ((base >> 12) & 0x80);
		vga_wcrt(cinfo->regbase, CL_CRT1D, tmp);
	}

	/* write pixel panning value to AR33; this does not quite work in 8bpp
	 *
	 * ### Piccolo..? Will this work?
	 */
	if (info->var.bits_per_pixel == 1)
		vga_wattr(cinfo->regbase, CL_AR33, xpix);

	return 0;
}