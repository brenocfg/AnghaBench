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
struct TYPE_2__ {int abs_count; } ;
typedef  TYPE_1__ in_evdev_t ;

/* Variables and functions */
#define  IN_CFG_ABS_AXIS_COUNT 128 

__attribute__((used)) static int in_evdev_get_config(void *drv_data, int what, int *val)
{
	in_evdev_t *dev = drv_data;

	switch (what) {
	case IN_CFG_ABS_AXIS_COUNT:
		*val = dev->abs_count;
		break;
	default:
		return -1;
	}

	return 0;
}