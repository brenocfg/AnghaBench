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
struct v4l2_subdev {int dummy; } ;
struct v4l2_captureparm {int /*<<< orphan*/  timeperframe; int /*<<< orphan*/  capability; } ;
struct TYPE_4__ {struct v4l2_captureparm capture; } ;
struct v4l2_streamparm {scalar_t__ type; TYPE_1__ parm; } ;
struct tvp514x_decoder {int current_std; TYPE_3__* std_list; } ;
typedef  enum tvp514x_std { ____Placeholder_tvp514x_std } tvp514x_std ;
struct TYPE_5__ {int /*<<< orphan*/  frameperiod; } ;
struct TYPE_6__ {TYPE_2__ standard; } ;

/* Variables and functions */
 int EINVAL ; 
 int STD_INVALID ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  V4L2_CAP_TIMEPERFRAME ; 
 int /*<<< orphan*/  memset (struct v4l2_streamparm*,int /*<<< orphan*/ ,int) ; 
 struct tvp514x_decoder* to_decoder (struct v4l2_subdev*) ; 
 int tvp514x_get_current_std (struct v4l2_subdev*) ; 

__attribute__((used)) static int
tvp514x_g_parm(struct v4l2_subdev *sd, struct v4l2_streamparm *a)
{
	struct tvp514x_decoder *decoder = to_decoder(sd);
	struct v4l2_captureparm *cparm;
	enum tvp514x_std current_std;

	if (a == NULL)
		return -EINVAL;

	if (a->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		/* only capture is supported */
		return -EINVAL;

	memset(a, 0, sizeof(*a));
	a->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	/* get the current standard */
	current_std = tvp514x_get_current_std(sd);
	if (current_std == STD_INVALID)
		return -EINVAL;

	decoder->current_std = current_std;

	cparm = &a->parm.capture;
	cparm->capability = V4L2_CAP_TIMEPERFRAME;
	cparm->timeperframe =
		decoder->std_list[current_std].standard.frameperiod;

	return 0;
}