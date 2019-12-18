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
struct fb_info {struct dlfb_data* par; } ;
struct fb_copyarea {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  sy; int /*<<< orphan*/  sx; int /*<<< orphan*/  dy; int /*<<< orphan*/  dx; } ;
struct dlfb_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  copyarea (struct dlfb_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dlfb_copyarea(struct fb_info *info, const struct fb_copyarea *area)
{

	struct dlfb_data *dev = info->par;

	copyarea(dev, area->dx, area->dy, area->sx, area->sy, area->width,
		 area->height);

	/* printk("COPY AREA %d %d %d %d %d %d !!!\n", area->dx, area->dy, area->sx, area->sy, area->width, area->height); */

}