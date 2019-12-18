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
struct cx18_open_id {struct cx18* cx; } ;
struct cx18 {scalar_t__ is_50hz; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 

__attribute__((used)) static int cx18_cropcap(struct file *file, void *fh,
			struct v4l2_cropcap *cropcap)
{
	struct cx18 *cx = ((struct cx18_open_id *)fh)->cx;

	if (cropcap->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;
	cropcap->bounds.top = cropcap->bounds.left = 0;
	cropcap->bounds.width = 720;
	cropcap->bounds.height = cx->is_50hz ? 576 : 480;
	cropcap->pixelaspect.numerator = cx->is_50hz ? 59 : 10;
	cropcap->pixelaspect.denominator = cx->is_50hz ? 54 : 11;
	cropcap->defrect = cropcap->bounds;
	return 0;
}