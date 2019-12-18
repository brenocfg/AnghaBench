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
 int __video_register_device (struct video_device*,int,int,int /*<<< orphan*/ ) ; 

int video_register_device_no_warn(struct video_device *vdev, int type, int nr)
{
	return __video_register_device(vdev, type, nr, 0);
}