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
struct TYPE_2__ {unsigned int width; unsigned int height; } ;
struct vc_data {size_t vc_num; TYPE_1__ vc_font; } ;
struct fb_var_screeninfo {int xres; int yres; int activate; } ;
struct fbcon_ops {struct fb_var_screeninfo var; int /*<<< orphan*/  rotate; } ;
struct fb_videomode {int dummy; } ;
struct fb_info {struct fb_var_screeninfo var; int /*<<< orphan*/  modelist; struct fbcon_ops* fbcon_par; } ;
struct display {int dummy; } ;

/* Variables and functions */
 scalar_t__ CON_IS_VISIBLE (struct vc_data*) ; 
 int /*<<< orphan*/  DPRINTK (char*,int,int) ; 
 int EINVAL ; 
 int FBCON_SWAP (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int FB_ACTIVATE_FORCE ; 
 int FB_ACTIVATE_NOW ; 
 size_t* con2fb_map ; 
 int /*<<< orphan*/  display_to_var (struct fb_var_screeninfo*,struct display*) ; 
 struct display* fb_display ; 
 struct fb_videomode* fb_find_best_mode (struct fb_var_screeninfo*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fb_set_var (struct fb_info*,struct fb_var_screeninfo*) ; 
 int /*<<< orphan*/  fb_videomode_to_var (struct fb_var_screeninfo*,struct fb_videomode const*) ; 
 struct fb_info** registered_fb ; 
 int /*<<< orphan*/  updatescrollmode (struct display*,struct fb_info*,struct vc_data*) ; 
 int /*<<< orphan*/  var_to_display (struct display*,struct fb_var_screeninfo*,struct fb_info*) ; 

__attribute__((used)) static int fbcon_resize(struct vc_data *vc, unsigned int width, 
			unsigned int height, unsigned int user)
{
	struct fb_info *info = registered_fb[con2fb_map[vc->vc_num]];
	struct fbcon_ops *ops = info->fbcon_par;
	struct display *p = &fb_display[vc->vc_num];
	struct fb_var_screeninfo var = info->var;
	int x_diff, y_diff, virt_w, virt_h, virt_fw, virt_fh;

	virt_w = FBCON_SWAP(ops->rotate, width, height);
	virt_h = FBCON_SWAP(ops->rotate, height, width);
	virt_fw = FBCON_SWAP(ops->rotate, vc->vc_font.width,
				 vc->vc_font.height);
	virt_fh = FBCON_SWAP(ops->rotate, vc->vc_font.height,
				 vc->vc_font.width);
	var.xres = virt_w * virt_fw;
	var.yres = virt_h * virt_fh;
	x_diff = info->var.xres - var.xres;
	y_diff = info->var.yres - var.yres;
	if (x_diff < 0 || x_diff > virt_fw ||
	    y_diff < 0 || y_diff > virt_fh) {
		const struct fb_videomode *mode;

		DPRINTK("attempting resize %ix%i\n", var.xres, var.yres);
		mode = fb_find_best_mode(&var, &info->modelist);
		if (mode == NULL)
			return -EINVAL;
		display_to_var(&var, p);
		fb_videomode_to_var(&var, mode);

		if (virt_w > var.xres/virt_fw || virt_h > var.yres/virt_fh)
			return -EINVAL;

		DPRINTK("resize now %ix%i\n", var.xres, var.yres);
		if (CON_IS_VISIBLE(vc)) {
			var.activate = FB_ACTIVATE_NOW |
				FB_ACTIVATE_FORCE;
			fb_set_var(info, &var);
		}
		var_to_display(p, &info->var, info);
		ops->var = info->var;
	}
	updatescrollmode(p, info, vc);
	return 0;
}