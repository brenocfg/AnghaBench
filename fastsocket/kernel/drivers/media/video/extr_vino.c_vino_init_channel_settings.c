#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  frame_wait_queue; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  queue_mutex; } ;
struct vino_channel_settings {unsigned int channel; int decimation; TYPE_3__* vdev; TYPE_1__ fb_queue; int /*<<< orphan*/  capture_lock; int /*<<< orphan*/  mutex; scalar_t__ capturing; int /*<<< orphan*/  data_norm; int /*<<< orphan*/  data_format; scalar_t__ users; scalar_t__ alpha; int /*<<< orphan*/  input; } ;
struct video_device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/ * v4l2_dev; int /*<<< orphan*/  release; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  VINO_DATA_FMT_GREY ; 
 int /*<<< orphan*/  VINO_DATA_NORM_NTSC ; 
 int /*<<< orphan*/  VINO_INPUT_NONE ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  vdev_template ; 
 TYPE_3__* video_device_alloc () ; 
 int /*<<< orphan*/  video_device_release ; 
 int /*<<< orphan*/  video_set_drvdata (TYPE_3__*,struct vino_channel_settings*) ; 
 TYPE_2__* vino_drvdata ; 
 int /*<<< orphan*/  vino_init_stage ; 
 int /*<<< orphan*/  vino_module_cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vino_set_default_clipping (struct vino_channel_settings*) ; 
 int /*<<< orphan*/  vino_set_default_framerate (struct vino_channel_settings*) ; 

__attribute__((used)) static int vino_init_channel_settings(struct vino_channel_settings *vcs,
				 unsigned int channel, const char *name)
{
	vcs->channel = channel;
	vcs->input = VINO_INPUT_NONE;
	vcs->alpha = 0;
	vcs->users = 0;
	vcs->data_format = VINO_DATA_FMT_GREY;
	vcs->data_norm = VINO_DATA_NORM_NTSC;
	vcs->decimation = 1;
	vino_set_default_clipping(vcs);
	vino_set_default_framerate(vcs);

	vcs->capturing = 0;

	mutex_init(&vcs->mutex);
	spin_lock_init(&vcs->capture_lock);

	mutex_init(&vcs->fb_queue.queue_mutex);
	spin_lock_init(&vcs->fb_queue.queue_lock);
	init_waitqueue_head(&vcs->fb_queue.frame_wait_queue);

	vcs->vdev = video_device_alloc();
	if (!vcs->vdev) {
		vino_module_cleanup(vino_init_stage);
		return -ENOMEM;
	}
	vino_init_stage++;

	memcpy(vcs->vdev, &vdev_template,
	       sizeof(struct video_device));
	strcpy(vcs->vdev->name, name);
	vcs->vdev->release = video_device_release;
	vcs->vdev->v4l2_dev = &vino_drvdata->v4l2_dev;

	video_set_drvdata(vcs->vdev, vcs);

	return 0;
}