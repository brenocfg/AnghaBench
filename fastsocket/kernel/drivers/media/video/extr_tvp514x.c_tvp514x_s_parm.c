#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int dummy; } ;
struct v4l2_fract {int dummy; } ;
struct TYPE_7__ {struct v4l2_fract timeperframe; } ;
struct TYPE_8__ {TYPE_3__ capture; } ;
struct v4l2_streamparm {scalar_t__ type; TYPE_4__ parm; } ;
struct tvp514x_decoder {int current_std; TYPE_2__* std_list; } ;
typedef  enum tvp514x_std { ____Placeholder_tvp514x_std } tvp514x_std ;
struct TYPE_5__ {struct v4l2_fract frameperiod; } ;
struct TYPE_6__ {TYPE_1__ standard; } ;

/* Variables and functions */
 int EINVAL ; 
 int STD_INVALID ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 struct tvp514x_decoder* to_decoder (struct v4l2_subdev*) ; 
 int tvp514x_get_current_std (struct v4l2_subdev*) ; 

__attribute__((used)) static int
tvp514x_s_parm(struct v4l2_subdev *sd, struct v4l2_streamparm *a)
{
	struct tvp514x_decoder *decoder = to_decoder(sd);
	struct v4l2_fract *timeperframe;
	enum tvp514x_std current_std;

	if (a == NULL)
		return -EINVAL;

	if (a->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		/* only capture is supported */
		return -EINVAL;

	timeperframe = &a->parm.capture.timeperframe;

	/* get the current standard */
	current_std = tvp514x_get_current_std(sd);
	if (current_std == STD_INVALID)
		return -EINVAL;

	decoder->current_std = current_std;

	*timeperframe =
	    decoder->std_list[current_std].standard.frameperiod;

	return 0;
}