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
struct TYPE_4__ {unsigned int numerator; int denominator; } ;
struct TYPE_5__ {scalar_t__ capturemode; TYPE_1__ timeperframe; } ;
struct TYPE_6__ {TYPE_2__ capture; } ;
struct v4l2_streamparm {scalar_t__ type; TYPE_3__ parm; } ;
struct go7007_file {struct go7007* go; } ;
struct go7007 {unsigned int sensor_framerate; unsigned int fps_scale; } ;
struct file {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 

__attribute__((used)) static int vidioc_s_parm(struct file *filp, void *priv,
		struct v4l2_streamparm *parm)
{
	struct go7007 *go = ((struct go7007_file *) priv)->go;
	unsigned int n, d;

	if (parm->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;
	if (parm->parm.capture.capturemode != 0)
		return -EINVAL;

	n = go->sensor_framerate *
		parm->parm.capture.timeperframe.numerator;
	d = 1001 * parm->parm.capture.timeperframe.denominator;
	if (n != 0 && d != 0 && n > d)
		go->fps_scale = (n + d/2) / d;
	else
		go->fps_scale = 1;

	return 0;
}