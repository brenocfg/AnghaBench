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
struct v4l2_capability {int capabilities; int /*<<< orphan*/  version; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  card; int /*<<< orphan*/  driver; } ;
struct file {int dummy; } ;
struct au0828_fh {struct au0828_dev* dev; } ;
struct TYPE_3__ {char* name; } ;
struct TYPE_4__ {char* name; } ;
struct au0828_dev {TYPE_1__ v4l2_dev; TYPE_2__ board; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU0828_VERSION_CODE ; 
 int V4L2_CAP_AUDIO ; 
 int V4L2_CAP_READWRITE ; 
 int V4L2_CAP_STREAMING ; 
 int V4L2_CAP_TUNER ; 
 int V4L2_CAP_VBI_CAPTURE ; 
 int V4L2_CAP_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int vidioc_querycap(struct file *file, void  *priv,
			   struct v4l2_capability *cap)
{
	struct au0828_fh *fh  = priv;
	struct au0828_dev *dev = fh->dev;

	strlcpy(cap->driver, "au0828", sizeof(cap->driver));
	strlcpy(cap->card, dev->board.name, sizeof(cap->card));
	strlcpy(cap->bus_info, dev->v4l2_dev.name, sizeof(cap->bus_info));

	cap->version = AU0828_VERSION_CODE;

	/*set the device capabilities */
	cap->capabilities = V4L2_CAP_VIDEO_CAPTURE |
		V4L2_CAP_VBI_CAPTURE |
		V4L2_CAP_AUDIO |
		V4L2_CAP_READWRITE |
		V4L2_CAP_STREAMING |
		V4L2_CAP_TUNER;
	return 0;
}