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
struct fbcon_ops {int flags; } ;
struct fb_info {struct fbcon_ops* fbcon_par; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int FBCON_FLAGS_CURSOR_TIMER ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  acquire_console_sem () ; 
 int* con2fb_map ; 
 scalar_t__ fbcon_has_exited ; 
 size_t fg_console ; 
 struct fb_info** registered_fb ; 
 int /*<<< orphan*/  release_console_sem () ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ssize_t show_cursor_blink(struct device *device,
				 struct device_attribute *attr, char *buf)
{
	struct fb_info *info;
	struct fbcon_ops *ops;
	int idx, blink = -1;

	if (fbcon_has_exited)
		return 0;

	acquire_console_sem();
	idx = con2fb_map[fg_console];

	if (idx == -1 || registered_fb[idx] == NULL)
		goto err;

	info = registered_fb[idx];
	ops = info->fbcon_par;

	if (!ops)
		goto err;

	blink = (ops->flags & FBCON_FLAGS_CURSOR_TIMER) ? 1 : 0;
err:
	release_console_sem();
	return snprintf(buf, PAGE_SIZE, "%d\n", blink);
}