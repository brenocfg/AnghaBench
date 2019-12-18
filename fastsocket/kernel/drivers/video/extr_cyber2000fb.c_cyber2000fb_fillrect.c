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
typedef  unsigned long u32 ;
struct fb_info {int dummy; } ;
struct fb_fillrect {unsigned long color; unsigned long dx; unsigned long dy; scalar_t__ height; scalar_t__ width; } ;
struct TYPE_3__ {int accel_flags; int bits_per_pixel; unsigned long xres_virtual; } ;
struct TYPE_4__ {TYPE_1__ var; scalar_t__ pseudo_palette; } ;
struct cfb_info {TYPE_2__ fb; } ;

/* Variables and functions */
 scalar_t__ CO_CMD_H_BLITTER ; 
 scalar_t__ CO_CMD_L_PATTERN_FGCOL ; 
 unsigned long CO_FG_MIX_SRC ; 
 int /*<<< orphan*/  CO_REG_CMD_H ; 
 int /*<<< orphan*/  CO_REG_CMD_L ; 
 int /*<<< orphan*/  CO_REG_CONTROL ; 
 int /*<<< orphan*/  CO_REG_DEST_PTR ; 
 int /*<<< orphan*/  CO_REG_FGCOLOUR ; 
 int /*<<< orphan*/  CO_REG_FGMIX ; 
 int /*<<< orphan*/  CO_REG_PIXHEIGHT ; 
 int /*<<< orphan*/  CO_REG_PIXWIDTH ; 
 int /*<<< orphan*/  CO_REG_X_PHASE ; 
 int FB_ACCELF_TEXT ; 
 int /*<<< orphan*/  cfb_fillrect (struct fb_info*,struct fb_fillrect const*) ; 
 int /*<<< orphan*/  cyber2000fb_writeb (unsigned long,int /*<<< orphan*/ ,struct cfb_info*) ; 
 int /*<<< orphan*/  cyber2000fb_writel (unsigned long,int /*<<< orphan*/ ,struct cfb_info*) ; 
 int /*<<< orphan*/  cyber2000fb_writew (scalar_t__,int /*<<< orphan*/ ,struct cfb_info*) ; 

__attribute__((used)) static void
cyber2000fb_fillrect(struct fb_info *info, const struct fb_fillrect *rect)
{
	struct cfb_info *cfb = (struct cfb_info *)info;
	unsigned long dst, col;

	if (!(cfb->fb.var.accel_flags & FB_ACCELF_TEXT)) {
		cfb_fillrect(info, rect);
		return;
	}

	cyber2000fb_writeb(0, CO_REG_CONTROL, cfb);
	cyber2000fb_writew(rect->width - 1, CO_REG_PIXWIDTH, cfb);
	cyber2000fb_writew(rect->height - 1, CO_REG_PIXHEIGHT, cfb);

	col = rect->color;
	if (cfb->fb.var.bits_per_pixel > 8)
		col = ((u32 *)cfb->fb.pseudo_palette)[col];
	cyber2000fb_writel(col, CO_REG_FGCOLOUR, cfb);

	dst = rect->dx + rect->dy * cfb->fb.var.xres_virtual;
	if (cfb->fb.var.bits_per_pixel == 24) {
		cyber2000fb_writeb(dst, CO_REG_X_PHASE, cfb);
		dst *= 3;
	}

	cyber2000fb_writel(dst, CO_REG_DEST_PTR, cfb);
	cyber2000fb_writeb(CO_FG_MIX_SRC, CO_REG_FGMIX, cfb);
	cyber2000fb_writew(CO_CMD_L_PATTERN_FGCOL, CO_REG_CMD_L, cfb);
	cyber2000fb_writew(CO_CMD_H_BLITTER, CO_REG_CMD_H, cfb);
}