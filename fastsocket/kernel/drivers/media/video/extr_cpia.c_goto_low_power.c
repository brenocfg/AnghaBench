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
struct TYPE_3__ {scalar_t__ systemState; } ;
struct TYPE_4__ {TYPE_1__ status; } ;
struct cam_data {TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPIA_COMMAND_GetCameraStatus ; 
 int /*<<< orphan*/  CPIA_COMMAND_GotoLoPower ; 
 int /*<<< orphan*/  DBG (char*) ; 
 scalar_t__ LO_POWER_STATE ; 
 scalar_t__ do_command (struct cam_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printstatus (struct cam_data*) ; 

__attribute__((used)) static int goto_low_power(struct cam_data *cam)
{
	if (do_command(cam, CPIA_COMMAND_GotoLoPower, 0, 0, 0, 0))
		return -1;
	if (do_command(cam, CPIA_COMMAND_GetCameraStatus, 0, 0, 0, 0))
		return -1;
	if (cam->params.status.systemState == LO_POWER_STATE) {
		DBG("camera now in LOW power state\n");
		return 0;
	}
	printstatus(cam);
	return -1;
}