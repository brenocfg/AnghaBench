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
struct video_device {TYPE_1__* ioctl_ops; int /*<<< orphan*/  flags; } ;
struct v4l2_fh {int /*<<< orphan*/ * events; struct video_device* vdev; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {scalar_t__ vidioc_subscribe_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V4L2_FL_USES_V4L2_FH ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int v4l2_event_init (struct v4l2_fh*) ; 

int v4l2_fh_init(struct v4l2_fh *fh, struct video_device *vdev)
{
	fh->vdev = vdev;
	INIT_LIST_HEAD(&fh->list);
	set_bit(V4L2_FL_USES_V4L2_FH, &fh->vdev->flags);

	/*
	 * fh->events only needs to be initialized if the driver
	 * supports the VIDIOC_SUBSCRIBE_EVENT ioctl.
	 */
	if (vdev->ioctl_ops && vdev->ioctl_ops->vidioc_subscribe_event)
		return v4l2_event_init(fh);

	fh->events = NULL;

	return 0;
}