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
typedef  void* u32 ;
struct v4l2_fract {int numerator; int denominator; } ;
struct TYPE_3__ {struct v4l2_fract timeperframe; } ;
struct TYPE_4__ {TYPE_1__ capture; } ;
struct v4l2_streamparm {scalar_t__ type; TYPE_2__ parm; } ;
struct v4l2_int_device {struct tcm825x_sensor* priv; } ;
struct tcm825x_sensor {struct v4l2_fract timeperframe; } ;

/* Variables and functions */
 int DEFAULT_FPS ; 
 int EINVAL ; 
 void* MAX_FPS ; 
 void* MIN_FPS ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int tcm825x_configure (struct v4l2_int_device*) ; 

__attribute__((used)) static int ioctl_s_parm(struct v4l2_int_device *s,
			     struct v4l2_streamparm *a)
{
	struct tcm825x_sensor *sensor = s->priv;
	struct v4l2_fract *timeperframe = &a->parm.capture.timeperframe;
	u32 tgt_fps;	/* target frames per secound */
	int rval;

	if (a->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;

	if ((timeperframe->numerator == 0)
	    || (timeperframe->denominator == 0)) {
		timeperframe->denominator = DEFAULT_FPS;
		timeperframe->numerator = 1;
	}

	tgt_fps = timeperframe->denominator / timeperframe->numerator;

	if (tgt_fps > MAX_FPS) {
		timeperframe->denominator = MAX_FPS;
		timeperframe->numerator = 1;
	} else if (tgt_fps < MIN_FPS) {
		timeperframe->denominator = MIN_FPS;
		timeperframe->numerator = 1;
	}

	sensor->timeperframe = *timeperframe;

	rval = tcm825x_configure(s);

	return rval;
}