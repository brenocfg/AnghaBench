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
struct TYPE_4__ {int width; int height; scalar_t__ left; scalar_t__ top; } ;
struct TYPE_3__ {int numerator; int denominator; } ;
struct v4l2_cropcap {scalar_t__ type; TYPE_2__ bounds; TYPE_2__ defrect; TYPE_1__ pixelaspect; } ;
struct file {int dummy; } ;
struct cx25821_fh {struct cx25821_dev* dev; } ;
struct cx25821_dev {scalar_t__ tvnorm; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 scalar_t__ V4L2_STD_PAL_BG ; 

int vidioc_cropcap(struct file *file, void *priv, struct v4l2_cropcap *cropcap)
{
	struct cx25821_dev *dev = ((struct cx25821_fh *)priv)->dev;

	if (cropcap->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;
	cropcap->bounds.top = cropcap->bounds.left = 0;
	cropcap->bounds.width = 720;
	cropcap->bounds.height = dev->tvnorm == V4L2_STD_PAL_BG ? 576 : 480;
	cropcap->pixelaspect.numerator =
	    dev->tvnorm == V4L2_STD_PAL_BG ? 59 : 10;
	cropcap->pixelaspect.denominator =
	    dev->tvnorm == V4L2_STD_PAL_BG ? 54 : 11;
	cropcap->defrect = cropcap->bounds;
	return 0;
}