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
typedef  int u8 ;
struct fb_info {int dummy; } ;
struct fb_fillrect {int color; scalar_t__ rop; int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;

/* Variables and functions */
 scalar_t__ BUSY ; 
 scalar_t__ ROP_COPY ; 
 int RR_CLEAR ; 
 int RR_INVERT ; 
 int RR_NOOP ; 
 int RR_SET ; 
 scalar_t__ TC_WEN ; 
 scalar_t__ WMRR ; 
 int fb_bitmask ; 
 scalar_t__ fb_regs ; 
 int in_8 (scalar_t__) ; 
 int /*<<< orphan*/  out_8 (scalar_t__,int) ; 
 int /*<<< orphan*/  topcat_blit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hpfb_fillrect(struct fb_info *p, const struct fb_fillrect *region)
{
	u8 clr;

	clr = region->color & 0xff;

	while (in_8(fb_regs + BUSY) & fb_bitmask)
		;

	/* Foreground */
	out_8(fb_regs + TC_WEN, fb_bitmask & clr);
	out_8(fb_regs + WMRR, (region->rop == ROP_COPY ? RR_SET : RR_INVERT));

	/* Background */
	out_8(fb_regs + TC_WEN, fb_bitmask & ~clr);
	out_8(fb_regs + WMRR, (region->rop == ROP_COPY ? RR_CLEAR : RR_NOOP));

	topcat_blit(region->dx, region->dy, region->dx, region->dy, region->width, region->height, -1);
}