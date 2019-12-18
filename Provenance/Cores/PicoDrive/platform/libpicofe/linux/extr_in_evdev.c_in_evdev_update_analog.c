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
struct input_absinfo {int value; } ;
struct TYPE_2__ {int* abs_adj; int* abs_mult; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ in_evdev_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVIOCGABS (int) ; 
 unsigned int MAX_ABS_DEVS ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct input_absinfo*) ; 

__attribute__((used)) static int in_evdev_update_analog(void *drv_data, int axis_id, int *result)
{
	struct input_absinfo ainfo;
	in_evdev_t *dev = drv_data;
	int ret;

	if ((unsigned int)axis_id >= MAX_ABS_DEVS)
		return -1;

	ret = ioctl(dev->fd, EVIOCGABS(axis_id), &ainfo);
	if (ret != 0)
		return ret;

	*result = (ainfo.value + dev->abs_adj[axis_id]) * dev->abs_mult[axis_id];
	*result >>= 16;
	return 0;
}