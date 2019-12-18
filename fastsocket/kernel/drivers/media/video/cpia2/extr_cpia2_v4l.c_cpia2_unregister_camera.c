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
struct camera_data {TYPE_1__* vdev; int /*<<< orphan*/  open_count; } ;
struct TYPE_2__ {int /*<<< orphan*/  num; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video_unregister_device (TYPE_1__*) ; 

void cpia2_unregister_camera(struct camera_data *cam)
{
	if (!cam->open_count) {
		video_unregister_device(cam->vdev);
	} else {
		LOG("/dev/video%d removed while open, "
		    "deferring video_unregister_device\n",
		    cam->vdev->num);
	}
}