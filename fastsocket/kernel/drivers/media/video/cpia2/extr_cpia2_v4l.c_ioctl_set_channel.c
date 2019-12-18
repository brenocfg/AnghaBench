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
struct video_channel {scalar_t__ channel; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int ioctl_set_channel(void *arg)
{
	struct video_channel *v;
	int retval = 0;
	v = arg;

	if (retval == 0 && v->channel != 0)
		retval = -EINVAL;

	return retval;
}