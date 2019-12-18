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
typedef  int /*<<< orphan*/  u16 ;
struct v4l2_subdev {int dummy; } ;
struct v4l2_fract {int /*<<< orphan*/  denominator; int /*<<< orphan*/  numerator; } ;
struct v4l2_captureparm {scalar_t__ extendedmode; struct v4l2_fract timeperframe; } ;
struct TYPE_2__ {struct v4l2_captureparm capture; } ;
struct v4l2_streamparm {scalar_t__ type; TYPE_1__ parm; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  R0A_MT9V011_CLK_SPEED ; 
 scalar_t__ V4L2_BUF_TYPE_VIDEO_CAPTURE ; 
 int /*<<< orphan*/  calc_fps (struct v4l2_subdev*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  calc_speed (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug ; 
 int /*<<< orphan*/  mt9v011_write (struct v4l2_subdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_dbg (int,int /*<<< orphan*/ ,struct v4l2_subdev*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt9v011_s_parm(struct v4l2_subdev *sd, struct v4l2_streamparm *parms)
{
	struct v4l2_captureparm *cp = &parms->parm.capture;
	struct v4l2_fract *tpf = &cp->timeperframe;
	u16 speed;

	if (parms->type != V4L2_BUF_TYPE_VIDEO_CAPTURE)
		return -EINVAL;
	if (cp->extendedmode != 0)
		return -EINVAL;

	speed = calc_speed(sd, tpf->numerator, tpf->denominator);

	mt9v011_write(sd, R0A_MT9V011_CLK_SPEED, speed);
	v4l2_dbg(1, debug, sd, "Setting speed to %d\n", speed);

	/* Recalculate and update fps info */
	calc_fps(sd, &tpf->numerator, &tpf->denominator);

	return 0;
}