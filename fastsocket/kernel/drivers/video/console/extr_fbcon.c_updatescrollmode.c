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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_6__ {int height; } ;
struct vc_data {int vc_rows; TYPE_3__ vc_font; } ;
struct fbcon_ops {int /*<<< orphan*/  rotate; } ;
struct TYPE_5__ {int /*<<< orphan*/  xres_virtual; int /*<<< orphan*/  yres_virtual; int /*<<< orphan*/  xres; int /*<<< orphan*/  yres; } ;
struct TYPE_4__ {int /*<<< orphan*/  ywrapstep; int /*<<< orphan*/  xpanstep; int /*<<< orphan*/  ypanstep; } ;
struct fb_info {int flags; TYPE_2__ var; TYPE_1__ fix; struct fbcon_ops* fbcon_par; } ;
struct display {int vrows; void* scrollmode; } ;

/* Variables and functions */
 int FBCON_SWAP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int FBINFO_HWACCEL_COPYAREA ; 
 int FBINFO_HWACCEL_DISABLED ; 
 int FBINFO_HWACCEL_IMAGEBLIT ; 
 int FBINFO_HWACCEL_YPAN ; 
 int FBINFO_HWACCEL_YWRAP ; 
 int FBINFO_READS_FAST ; 
 void* SCROLL_MOVE ; 
 void* SCROLL_PAN_MOVE ; 
 void* SCROLL_PAN_REDRAW ; 
 void* SCROLL_REDRAW ; 
 void* SCROLL_WRAP_MOVE ; 
 scalar_t__ divides (int,int) ; 

__attribute__((used)) static void updatescrollmode(struct display *p,
					struct fb_info *info,
					struct vc_data *vc)
{
	struct fbcon_ops *ops = info->fbcon_par;
	int fh = vc->vc_font.height;
	int cap = info->flags;
	u16 t = 0;
	int ypan = FBCON_SWAP(ops->rotate, info->fix.ypanstep,
				  info->fix.xpanstep);
	int ywrap = FBCON_SWAP(ops->rotate, info->fix.ywrapstep, t);
	int yres = FBCON_SWAP(ops->rotate, info->var.yres, info->var.xres);
	int vyres = FBCON_SWAP(ops->rotate, info->var.yres_virtual,
				   info->var.xres_virtual);
	int good_pan = (cap & FBINFO_HWACCEL_YPAN) &&
		divides(ypan, vc->vc_font.height) && vyres > yres;
	int good_wrap = (cap & FBINFO_HWACCEL_YWRAP) &&
		divides(ywrap, vc->vc_font.height) &&
		divides(vc->vc_font.height, vyres) &&
		divides(vc->vc_font.height, yres);
	int reading_fast = cap & FBINFO_READS_FAST;
	int fast_copyarea = (cap & FBINFO_HWACCEL_COPYAREA) &&
		!(cap & FBINFO_HWACCEL_DISABLED);
	int fast_imageblit = (cap & FBINFO_HWACCEL_IMAGEBLIT) &&
		!(cap & FBINFO_HWACCEL_DISABLED);

	p->vrows = vyres/fh;
	if (yres > (fh * (vc->vc_rows + 1)))
		p->vrows -= (yres - (fh * vc->vc_rows)) / fh;
	if ((yres % fh) && (vyres % fh < yres % fh))
		p->vrows--;

	if (good_wrap || good_pan) {
		if (reading_fast || fast_copyarea)
			p->scrollmode = good_wrap ?
				SCROLL_WRAP_MOVE : SCROLL_PAN_MOVE;
		else
			p->scrollmode = good_wrap ? SCROLL_REDRAW :
				SCROLL_PAN_REDRAW;
	} else {
		if (reading_fast || (fast_copyarea && !fast_imageblit))
			p->scrollmode = SCROLL_MOVE;
		else
			p->scrollmode = SCROLL_REDRAW;
	}
}