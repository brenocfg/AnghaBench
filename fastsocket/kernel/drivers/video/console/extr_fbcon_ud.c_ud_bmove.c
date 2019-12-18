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
typedef  void* u32 ;
struct TYPE_5__ {int height; int width; } ;
struct vc_data {TYPE_2__ vc_font; } ;
struct fbcon_ops {TYPE_1__* p; } ;
struct fb_info {TYPE_3__* fbops; struct fbcon_ops* fbcon_par; } ;
struct fb_copyarea {int height; int width; void* dx; void* dy; void* sx; void* sy; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* fb_copyarea ) (struct fb_info*,struct fb_copyarea*) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  scrollmode; } ;

/* Variables and functions */
 void* GETVXRES (int /*<<< orphan*/ ,struct fb_info*) ; 
 void* GETVYRES (int /*<<< orphan*/ ,struct fb_info*) ; 
 int /*<<< orphan*/  stub1 (struct fb_info*,struct fb_copyarea*) ; 

__attribute__((used)) static void ud_bmove(struct vc_data *vc, struct fb_info *info, int sy,
		     int sx, int dy, int dx, int height, int width)
{
	struct fbcon_ops *ops = info->fbcon_par;
	struct fb_copyarea area;
	u32 vyres = GETVYRES(ops->p->scrollmode, info);
	u32 vxres = GETVXRES(ops->p->scrollmode, info);

	area.sy = vyres - ((sy + height) * vc->vc_font.height);
	area.sx = vxres - ((sx + width) * vc->vc_font.width);
	area.dy = vyres - ((dy + height) * vc->vc_font.height);
	area.dx = vxres - ((dx + width) * vc->vc_font.width);
	area.height = height * vc->vc_font.height;
	area.width  = width * vc->vc_font.width;

	info->fbops->fb_copyarea(info, &area);
}