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
typedef  int /*<<< orphan*/  u_int32_t ;
struct matrox_fb_info {int dummy; } ;
struct fb_info {scalar_t__ pseudo_palette; } ;
struct fb_fillrect {int rop; size_t color; int /*<<< orphan*/  width; int /*<<< orphan*/  height; int /*<<< orphan*/  dx; int /*<<< orphan*/  dy; } ;

/* Variables and functions */
#define  ROP_COPY 128 
 struct matrox_fb_info* info2minfo (struct fb_info*) ; 
 int /*<<< orphan*/  matroxfb_accel_clear (struct matrox_fb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void matroxfb_fillrect(struct fb_info* info, const struct fb_fillrect* rect) {
	struct matrox_fb_info *minfo = info2minfo(info);

	switch (rect->rop) {
		case ROP_COPY:
			matroxfb_accel_clear(minfo, ((u_int32_t *)info->pseudo_palette)[rect->color], rect->dy, rect->dx, rect->height, rect->width);
			break;
	}
}