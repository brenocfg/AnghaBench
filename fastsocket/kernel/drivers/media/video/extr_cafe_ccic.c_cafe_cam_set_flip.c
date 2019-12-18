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
struct v4l2_control {int /*<<< orphan*/  value; int /*<<< orphan*/  id; } ;
struct cafe_camera {int dummy; } ;
typedef  int /*<<< orphan*/  ctrl ;

/* Variables and functions */
 int /*<<< orphan*/  V4L2_CID_VFLIP ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  flip ; 
 int /*<<< orphan*/  memset (struct v4l2_control*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s_ctrl ; 
 int sensor_call (struct cafe_camera*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_control*) ; 

__attribute__((used)) static int cafe_cam_set_flip(struct cafe_camera *cam)
{
	struct v4l2_control ctrl;

	memset(&ctrl, 0, sizeof(ctrl));
	ctrl.id = V4L2_CID_VFLIP;
	ctrl.value = flip;
	return sensor_call(cam, core, s_ctrl, &ctrl);
}