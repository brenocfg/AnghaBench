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
typedef  int u32 ;
struct TYPE_2__ {int bits_per_pixel; } ;
struct fb_info {scalar_t__ pseudo_palette; TYPE_1__ var; } ;
struct fb_fillrect {scalar_t__ rop; size_t color; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;

/* Variables and functions */
 int /*<<< orphan*/  HD64461_BBTMDR ; 
 int /*<<< orphan*/  HD64461_BBTROPR ; 
 int /*<<< orphan*/  HD64461_GRSCR ; 
 scalar_t__ ROP_COPY ; 
 int /*<<< orphan*/  cfb_fillrect (struct fb_info*,struct fb_fillrect const*) ; 
 int /*<<< orphan*/  fb_writew (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hitfb_accel_set_dest (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hitfb_accel_start (int) ; 
 int /*<<< orphan*/  hitfb_accel_wait () ; 

__attribute__((used)) static void hitfb_fillrect(struct fb_info *p, const struct fb_fillrect *rect)
{
	if (rect->rop != ROP_COPY)
		cfb_fillrect(p, rect);
	else {
		hitfb_accel_wait();
		fb_writew(0x00f0, HD64461_BBTROPR);
		fb_writew(16, HD64461_BBTMDR);

		if (p->var.bits_per_pixel == 16) {
			fb_writew(((u32 *) (p->pseudo_palette))[rect->color],
				  HD64461_GRSCR);
			hitfb_accel_set_dest(1, rect->dx, rect->dy, rect->width,
					     rect->height);
			hitfb_accel_start(1);
		} else {
			fb_writew(rect->color, HD64461_GRSCR);
			hitfb_accel_set_dest(0, rect->dx, rect->dy, rect->width,
					     rect->height);
			hitfb_accel_start(0);
		}
	}
}