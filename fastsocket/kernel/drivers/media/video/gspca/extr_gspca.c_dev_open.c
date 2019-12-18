#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int debug; } ;
struct gspca_dev {TYPE_1__ vdev; int /*<<< orphan*/  module; int /*<<< orphan*/  present; } ;
struct file {struct gspca_dev* private_data; } ;
struct TYPE_4__ {int /*<<< orphan*/  comm; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_STREAM ; 
 int D_V4L2 ; 
 int ENODEV ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int V4L2_DEBUG_IOCTL ; 
 int V4L2_DEBUG_IOCTL_ARG ; 
 TYPE_2__* current ; 
 int gspca_debug ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 scalar_t__ video_devdata (struct file*) ; 

__attribute__((used)) static int dev_open(struct file *file)
{
	struct gspca_dev *gspca_dev;

	PDEBUG(D_STREAM, "[%s] open", current->comm);
	gspca_dev = (struct gspca_dev *) video_devdata(file);
	if (!gspca_dev->present)
		return -ENODEV;

	/* protect the subdriver against rmmod */
	if (!try_module_get(gspca_dev->module))
		return -ENODEV;

	file->private_data = gspca_dev;
#ifdef GSPCA_DEBUG
	/* activate the v4l2 debug */
	if (gspca_debug & D_V4L2)
		gspca_dev->vdev.debug |= V4L2_DEBUG_IOCTL
					| V4L2_DEBUG_IOCTL_ARG;
	else
		gspca_dev->vdev.debug &= ~(V4L2_DEBUG_IOCTL
					| V4L2_DEBUG_IOCTL_ARG);
#endif
	return 0;
}