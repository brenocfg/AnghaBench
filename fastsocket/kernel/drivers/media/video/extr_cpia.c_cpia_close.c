#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct video_device {int dummy; } ;
struct file {struct video_device* private_data; } ;
struct TYPE_5__ {int /*<<< orphan*/ * data; } ;
struct cam_data {scalar_t__ open_count; TYPE_3__* ops; scalar_t__ frame_buf; TYPE_2__ decompressed_frame; int /*<<< orphan*/ * raw_image; int /*<<< orphan*/  lowlevel_data; int /*<<< orphan*/  frame; TYPE_1__* proc_entry; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* close ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {scalar_t__ uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPIA_COMMAND_GetCameraStatus ; 
 int /*<<< orphan*/  CPIA_MAX_FRAME_SIZE ; 
 int /*<<< orphan*/  CPIA_MAX_IMAGE_SIZE ; 
 int /*<<< orphan*/  do_command (struct cam_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_frame_buf (struct cam_data*) ; 
 int /*<<< orphan*/  free_frames (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  goto_low_power (struct cam_data*) ; 
 int /*<<< orphan*/  kfree (struct cam_data*) ; 
 int /*<<< orphan*/  put_cam (TYPE_3__*) ; 
 int /*<<< orphan*/  rvfree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_camera_state (struct cam_data*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 struct cam_data* video_get_drvdata (struct video_device*) ; 

__attribute__((used)) static int cpia_close(struct file *file)
{
	struct  video_device *dev = file->private_data;
	struct cam_data *cam = video_get_drvdata(dev);

	if (cam->ops) {
		/* Return ownership of /proc/cpia/videoX to root */
		if(cam->proc_entry)
			cam->proc_entry->uid = 0;

		/* save camera state for later open (developers guide ch 3.5.3) */
		save_camera_state(cam);

		/* GotoLoPower */
		goto_low_power(cam);

		/* Update the camera status */
		do_command(cam, CPIA_COMMAND_GetCameraStatus, 0, 0, 0, 0);

		/* cleanup internal state stuff */
		free_frames(cam->frame);

		/* close cpia */
		cam->ops->close(cam->lowlevel_data);

		put_cam(cam->ops);
	}

	if (--cam->open_count == 0) {
		/* clean up capture-buffers */
		if (cam->raw_image) {
			rvfree(cam->raw_image, CPIA_MAX_IMAGE_SIZE);
			cam->raw_image = NULL;
		}

		if (cam->decompressed_frame.data) {
			rvfree(cam->decompressed_frame.data, CPIA_MAX_FRAME_SIZE);
			cam->decompressed_frame.data = NULL;
		}

		if (cam->frame_buf)
			free_frame_buf(cam);

		if (!cam->ops)
			kfree(cam);
	}
	file->private_data = NULL;

	return 0;
}