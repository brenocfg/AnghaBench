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
struct video_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  video_device_release (struct video_device*) ; 
 scalar_t__ video_is_registered (struct video_device*) ; 
 int /*<<< orphan*/  video_unregister_device (struct video_device*) ; 

void destroy_video_device(struct video_device **v_dev)
{
	struct video_device *dev = *v_dev;

	if (dev == NULL)
		return;

	if (video_is_registered(dev))
		video_unregister_device(dev);
	else
		video_device_release(dev);
	*v_dev = NULL;
}