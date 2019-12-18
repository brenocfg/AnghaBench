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
struct TYPE_2__ {scalar_t__ xres; scalar_t__ yres; } ;
struct fb_info {int /*<<< orphan*/  screen_base; TYPE_1__ var; struct dlfb_data* par; } ;
struct dloarea {scalar_t__ x; scalar_t__ y; scalar_t__ x2; scalar_t__ y2; int /*<<< orphan*/  h; int /*<<< orphan*/  w; } ;
struct dlfb_data {int /*<<< orphan*/  edid; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ copy_to_user (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  copyarea (struct dlfb_data*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copyfb (struct dlfb_data*) ; 
 int /*<<< orphan*/  dlfb_edid (struct dlfb_data*) ; 
 int /*<<< orphan*/  image_blit (struct dlfb_data*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swapfb (struct dlfb_data*) ; 

__attribute__((used)) static int dlfb_ioctl(struct fb_info *info, unsigned int cmd, unsigned long arg)
{

	struct dlfb_data *dev_info = info->par;
	struct dloarea *area = NULL;

	if (cmd == 0xAD) {
		char *edid = (char *)arg;
		dlfb_edid(dev_info);
		if (copy_to_user(edid, dev_info->edid, 128)) {
			return -EFAULT;
		}
		return 0;
	}

	if (cmd == 0xAA || cmd == 0xAB || cmd == 0xAC) {

		area = (struct dloarea *)arg;

		if (area->x < 0)
			area->x = 0;

		if (area->x > info->var.xres)
			area->x = info->var.xres;

		if (area->y < 0)
			area->y = 0;

		if (area->y > info->var.yres)
			area->y = info->var.yres;
	}

	if (cmd == 0xAA) {
		image_blit(dev_info, area->x, area->y, area->w, area->h,
			   info->screen_base);
	}
	if (cmd == 0xAC) {
		copyfb(dev_info);
		image_blit(dev_info, area->x, area->y, area->w, area->h,
			   info->screen_base);
		swapfb(dev_info);
	} else if (cmd == 0xAB) {

		if (area->x2 < 0)
			area->x2 = 0;

		if (area->y2 < 0)
			area->y2 = 0;

		copyarea(dev_info,
			 area->x2, area->y2, area->x, area->y, area->w,
			 area->h);
	}
	return 0;
}