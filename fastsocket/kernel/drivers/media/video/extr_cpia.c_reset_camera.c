#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ systemState; int fatalError; int vpStatus; } ;
struct TYPE_10__ {int vendor; int product; } ;
struct TYPE_9__ {int qx3_detected; } ;
struct TYPE_8__ {int gainMode; } ;
struct TYPE_7__ {int firmwareVersion; int firmwareRevision; } ;
struct TYPE_12__ {TYPE_5__ status; TYPE_4__ pnpID; TYPE_3__ qx3; TYPE_2__ exposure; TYPE_1__ version; } ;
struct cam_data {TYPE_6__ params; } ;

/* Variables and functions */
 int COM_FLAG ; 
 int /*<<< orphan*/  CPIA_COMMAND_DiscardFrame ; 
 int /*<<< orphan*/  CPIA_COMMAND_GetCameraStatus ; 
 int /*<<< orphan*/  CPIA_COMMAND_GetVPVersion ; 
 int /*<<< orphan*/  CPIA_COMMAND_ModifyCameraStatus ; 
 int CPIA_FLAG ; 
 int /*<<< orphan*/  DBG (char*,int) ; 
 int EIO ; 
 int ENODEV ; 
 int /*<<< orphan*/  FATALERROR ; 
 int /*<<< orphan*/  STREAMSTATE ; 
 int /*<<< orphan*/  STREAM_NOT_READY ; 
 scalar_t__ WARM_BOOT_STATE ; 
 scalar_t__ do_command (struct cam_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_version_information (struct cam_data*) ; 
 int goto_high_power (struct cam_data*) ; 
 scalar_t__ goto_low_power (struct cam_data*) ; 
 int set_camera_state (struct cam_data*) ; 

__attribute__((used)) static int reset_camera(struct cam_data *cam)
{
	int err;
	/* Start the camera in low power mode */
	if (goto_low_power(cam)) {
		if (cam->params.status.systemState != WARM_BOOT_STATE)
			return -ENODEV;

		/* FIXME: this is just dirty trial and error */
		err = goto_high_power(cam);
		if(err)
			return err;
		do_command(cam, CPIA_COMMAND_DiscardFrame, 0, 0, 0, 0);
		if (goto_low_power(cam))
			return -ENODEV;
	}

	/* procedure described in developer's guide p3-28 */

	/* Check the firmware version. */
	cam->params.version.firmwareVersion = 0;
	get_version_information(cam);
	if (cam->params.version.firmwareVersion != 1)
		return -ENODEV;

	/* A bug in firmware 1-02 limits gainMode to 2 */
	if(cam->params.version.firmwareRevision <= 2 &&
	   cam->params.exposure.gainMode > 2) {
		cam->params.exposure.gainMode = 2;
	}

	/* set QX3 detected flag */
	cam->params.qx3.qx3_detected = (cam->params.pnpID.vendor == 0x0813 &&
					cam->params.pnpID.product == 0x0001);

	/* The fatal error checking should be done after
	 * the camera powers up (developer's guide p 3-38) */

	/* Set streamState before transition to high power to avoid bug
	 * in firmware 1-02 */
	do_command(cam, CPIA_COMMAND_ModifyCameraStatus, STREAMSTATE, 0,
		   STREAM_NOT_READY, 0);

	/* GotoHiPower */
	err = goto_high_power(cam);
	if (err)
		return err;

	/* Check the camera status */
	if (do_command(cam, CPIA_COMMAND_GetCameraStatus, 0, 0, 0, 0))
		return -EIO;

	if (cam->params.status.fatalError) {
		DBG("fatal_error:              %#04x\n",
		    cam->params.status.fatalError);
		DBG("vp_status:                %#04x\n",
		    cam->params.status.vpStatus);
		if (cam->params.status.fatalError & ~(COM_FLAG|CPIA_FLAG)) {
			/* Fatal error in camera */
			return -EIO;
		} else if (cam->params.status.fatalError & (COM_FLAG|CPIA_FLAG)) {
			/* Firmware 1-02 may do this for parallel port cameras,
			 * just clear the flags (developer's guide p 3-38) */
			do_command(cam, CPIA_COMMAND_ModifyCameraStatus,
				   FATALERROR, ~(COM_FLAG|CPIA_FLAG), 0, 0);
		}
	}

	/* Check the camera status again */
	if (cam->params.status.fatalError) {
		if (cam->params.status.fatalError)
			return -EIO;
	}

	/* VPVersion can't be retrieved before the camera is in HiPower,
	 * so get it here instead of in get_version_information. */
	do_command(cam, CPIA_COMMAND_GetVPVersion, 0, 0, 0, 0);

	/* set camera to a known state */
	return set_camera_state(cam);
}