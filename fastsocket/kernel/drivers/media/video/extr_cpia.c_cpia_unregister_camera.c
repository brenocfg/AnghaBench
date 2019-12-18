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
struct TYPE_2__ {int /*<<< orphan*/  num; } ;
struct cam_data {scalar_t__ open_count; TYPE_1__ vdev; int /*<<< orphan*/ * ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 int /*<<< orphan*/  destroy_proc_cpia_cam (struct cam_data*) ; 
 int /*<<< orphan*/  kfree (struct cam_data*) ; 
 int /*<<< orphan*/  put_cam (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (TYPE_1__*) ; 

void cpia_unregister_camera(struct cam_data *cam)
{
	DBG("unregistering video\n");
	video_unregister_device(&cam->vdev);
	if (cam->open_count) {
		put_cam(cam->ops);
		DBG("camera open -- setting ops to NULL\n");
		cam->ops = NULL;
	}

#ifdef CONFIG_PROC_FS
	DBG("destroying /proc/cpia/video%d\n", cam->vdev.num);
	destroy_proc_cpia_cam(cam);
#endif
	if (!cam->open_count) {
		DBG("freeing camera\n");
		kfree(cam);
	}
}