#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct v4l2_mbus_framefmt {int dummy; } ;
struct cafe_camera {int /*<<< orphan*/  mbus_code; int /*<<< orphan*/  pix_format; } ;

/* Variables and functions */
 scalar_t__ cafe_cam_set_flip (struct cafe_camera*) ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  init ; 
 int /*<<< orphan*/  s_mbus_fmt ; 
 int sensor_call (struct cafe_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_mbus_framefmt*) ; 
 int /*<<< orphan*/  v4l2_fill_mbus_format (struct v4l2_mbus_framefmt*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static int cafe_cam_configure(struct cafe_camera *cam)
{
	struct v4l2_mbus_framefmt mbus_fmt;
	int ret;

	v4l2_fill_mbus_format(&mbus_fmt, &cam->pix_format, cam->mbus_code);
	ret = sensor_call(cam, core, init, 0);
	if (ret == 0)
		ret = sensor_call(cam, video, s_mbus_fmt, &mbus_fmt);
	/*
	 * OV7670 does weird things if flip is set *before* format...
	 */
	ret += cafe_cam_set_flip(cam);
	return ret;
}