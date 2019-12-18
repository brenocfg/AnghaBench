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
struct fb_videomode {int dummy; } ;
struct fb_info {int /*<<< orphan*/  modelist; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acquire_console_sem () ; 
 struct fb_info* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  fb_destroy_modelist (int /*<<< orphan*/ *) ; 
 scalar_t__ fb_new_modelist (struct fb_info*) ; 
 int /*<<< orphan*/  fb_videomode_to_modelist (struct fb_videomode const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  old_list ; 
 int /*<<< orphan*/  release_console_sem () ; 

__attribute__((used)) static ssize_t store_modes(struct device *device,
			   struct device_attribute *attr,
			   const char *buf, size_t count)
{
	struct fb_info *fb_info = dev_get_drvdata(device);
	LIST_HEAD(old_list);
	int i = count / sizeof(struct fb_videomode);

	if (i * sizeof(struct fb_videomode) != count)
		return -EINVAL;

	acquire_console_sem();
	list_splice(&fb_info->modelist, &old_list);
	fb_videomode_to_modelist((const struct fb_videomode *)buf, i,
				 &fb_info->modelist);
	if (fb_new_modelist(fb_info)) {
		fb_destroy_modelist(&fb_info->modelist);
		list_splice(&old_list, &fb_info->modelist);
	} else
		fb_destroy_modelist(&old_list);

	release_console_sem();

	return 0;
}