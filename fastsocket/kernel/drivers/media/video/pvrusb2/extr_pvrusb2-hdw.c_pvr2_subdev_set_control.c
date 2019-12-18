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
struct v4l2_control {int id; int value; } ;
struct pvr2_hdw {int /*<<< orphan*/  v4l2_dev; } ;
typedef  int /*<<< orphan*/  ctrl ;

/* Variables and functions */
 int /*<<< orphan*/  PVR2_TRACE_CHIPS ; 
 int /*<<< orphan*/  core ; 
 int /*<<< orphan*/  memset (struct v4l2_control*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pvr2_trace (int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  s_ctrl ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct v4l2_control*) ; 

__attribute__((used)) static void pvr2_subdev_set_control(struct pvr2_hdw *hdw, int id,
				    const char *name, int val)
{
	struct v4l2_control ctrl;
	pvr2_trace(PVR2_TRACE_CHIPS, "subdev v4l2 %s=%d", name, val);
	memset(&ctrl, 0, sizeof(ctrl));
	ctrl.id = id;
	ctrl.value = val;
	v4l2_device_call_all(&hdw->v4l2_dev, 0, core, s_ctrl, &ctrl);
}