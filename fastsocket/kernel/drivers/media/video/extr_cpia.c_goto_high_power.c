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
 int /*<<< orphan*/  CPIA_COMMAND_GotoHiPower ; 
 int /*<<< orphan*/  DBG (char*) ; 
 int EINTR ; 
 int EIO ; 
 scalar_t__ HI_POWER_STATE ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ do_command (struct cam_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  printstatus (struct cam_data*) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int goto_high_power(struct cam_data *cam)
{
	if (do_command(cam, CPIA_COMMAND_GotoHiPower, 0, 0, 0, 0))
		return -EIO;
	msleep_interruptible(40);	/* windows driver does it too */
	if(signal_pending(current))
		return -EINTR;
	if (do_command(cam, CPIA_COMMAND_GetCameraStatus, 0, 0, 0, 0))
		return -EIO;
	if (cam->params.status.systemState == HI_POWER_STATE) {
		DBG("camera now in HIGH power state\n");
		return 0;
	}
	printstatus(cam);
	return -EIO;
}