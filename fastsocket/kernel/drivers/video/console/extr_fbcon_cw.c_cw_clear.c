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
typedef  scalar_t__ u32 ;
struct TYPE_5__ {int height; int width; } ;
struct vc_data {TYPE_2__ vc_font; scalar_t__ vc_hi_font_mask; } ;
struct fbcon_ops {TYPE_1__* p; } ;
struct fb_info {TYPE_3__* fbops; struct fbcon_ops* fbcon_par; } ;
struct fb_fillrect {int dy; int height; int width; int /*<<< orphan*/  rop; scalar_t__ dx; int /*<<< orphan*/  color; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* fb_fillrect ) (struct fb_info*,struct fb_fillrect*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  scrollmode; } ;

/* Variables and functions */
 scalar_t__ GETVXRES (int /*<<< orphan*/ ,struct fb_info*) ; 
 int /*<<< orphan*/  ROP_COPY ; 
 int /*<<< orphan*/  attr_bgcol_ec (int,struct vc_data*,struct fb_info*) ; 
 int /*<<< orphan*/  stub1 (struct fb_info*,struct fb_fillrect*) ; 

__attribute__((used)) static void cw_clear(struct vc_data *vc, struct fb_info *info, int sy,
		     int sx, int height, int width)
{
	struct fbcon_ops *ops = info->fbcon_par;
	struct fb_fillrect region;
	int bgshift = (vc->vc_hi_font_mask) ? 13 : 12;
	u32 vxres = GETVXRES(ops->p->scrollmode, info);

	region.color = attr_bgcol_ec(bgshift,vc,info);
	region.dx = vxres - ((sy + height) * vc->vc_font.height);
	region.dy = sx *  vc->vc_font.width;
	region.height = width * vc->vc_font.width;
	region.width = height * vc->vc_font.height;
	region.rop = ROP_COPY;

	info->fbops->fb_fillrect(info, &region);
}