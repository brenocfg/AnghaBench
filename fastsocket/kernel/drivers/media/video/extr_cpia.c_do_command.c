#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u16 ;
struct TYPE_16__ {int button; int cradled; int /*<<< orphan*/  qx3_detected; } ;
struct TYPE_15__ {int gain; int fineExp; int coarseExpLo; int coarseExpHi; int redComp; int green1Comp; int green2Comp; int blueComp; } ;
struct TYPE_14__ {int redGain; int greenGain; int blueGain; } ;
struct TYPE_13__ {int brightness; int contrast; int saturation; } ;
struct TYPE_12__ {int vpVersion; int vpRevision; int cameraHeadID; } ;
struct TYPE_11__ {int systemState; int grabState; int streamState; int fatalError; int cmdError; int debugFlags; int vpStatus; int errorCode; } ;
struct TYPE_19__ {int vendor; int product; int deviceRevision; } ;
struct TYPE_18__ {int firmwareVersion; int firmwareRevision; int vcVersion; int vcRevision; } ;
struct TYPE_20__ {TYPE_5__ qx3; TYPE_4__ exposure; TYPE_3__ colourBalance; TYPE_2__ colourParams; TYPE_1__ vpVersion; TYPE_10__ status; TYPE_8__ pnpID; TYPE_7__ version; } ;
struct cam_data {TYPE_9__ params; int /*<<< orphan*/  param_lock; int /*<<< orphan*/  lowlevel_data; TYPE_6__* ops; } ;
struct TYPE_17__ {int (* transferCmd ) (int /*<<< orphan*/ ,int*,int*) ;} ;

/* Variables and functions */
#define  CPIA_COMMAND_GetCPIAVersion 136 
#define  CPIA_COMMAND_GetCameraStatus 135 
#define  CPIA_COMMAND_GetColourBalance 134 
#define  CPIA_COMMAND_GetColourParams 133 
#define  CPIA_COMMAND_GetExposure 132 
#define  CPIA_COMMAND_GetPnPID 131 
#define  CPIA_COMMAND_GetVPVersion 130 
#define  CPIA_COMMAND_ReadMCPorts 129 
#define  CPIA_COMMAND_ReadVCRegs 128 
 int CPIA_COMMAND_WriteMCPort ; 
 int /*<<< orphan*/  DBG (char*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static int do_command(struct cam_data *cam, u16 command, u8 a, u8 b, u8 c, u8 d)
{
	int retval, datasize;
	u8 cmd[8], data[8];

	switch(command) {
	case CPIA_COMMAND_GetCPIAVersion:
	case CPIA_COMMAND_GetPnPID:
	case CPIA_COMMAND_GetCameraStatus:
	case CPIA_COMMAND_GetVPVersion:
		datasize=8;
		break;
	case CPIA_COMMAND_GetColourParams:
	case CPIA_COMMAND_GetColourBalance:
	case CPIA_COMMAND_GetExposure:
		mutex_lock(&cam->param_lock);
		datasize=8;
		break;
	case CPIA_COMMAND_ReadMCPorts:
	case CPIA_COMMAND_ReadVCRegs:
		datasize = 4;
		break;
	default:
		datasize=0;
		break;
	}

	cmd[0] = command>>8;
	cmd[1] = command&0xff;
	cmd[2] = a;
	cmd[3] = b;
	cmd[4] = c;
	cmd[5] = d;
	cmd[6] = datasize;
	cmd[7] = 0;

	retval = cam->ops->transferCmd(cam->lowlevel_data, cmd, data);
	if (retval) {
		DBG("%x - failed, retval=%d\n", command, retval);
		if (command == CPIA_COMMAND_GetColourParams ||
		    command == CPIA_COMMAND_GetColourBalance ||
		    command == CPIA_COMMAND_GetExposure)
			mutex_unlock(&cam->param_lock);
	} else {
		switch(command) {
		case CPIA_COMMAND_GetCPIAVersion:
			cam->params.version.firmwareVersion = data[0];
			cam->params.version.firmwareRevision = data[1];
			cam->params.version.vcVersion = data[2];
			cam->params.version.vcRevision = data[3];
			break;
		case CPIA_COMMAND_GetPnPID:
			cam->params.pnpID.vendor = data[0]+(((u16)data[1])<<8);
			cam->params.pnpID.product = data[2]+(((u16)data[3])<<8);
			cam->params.pnpID.deviceRevision =
				data[4]+(((u16)data[5])<<8);
			break;
		case CPIA_COMMAND_GetCameraStatus:
			cam->params.status.systemState = data[0];
			cam->params.status.grabState = data[1];
			cam->params.status.streamState = data[2];
			cam->params.status.fatalError = data[3];
			cam->params.status.cmdError = data[4];
			cam->params.status.debugFlags = data[5];
			cam->params.status.vpStatus = data[6];
			cam->params.status.errorCode = data[7];
			break;
		case CPIA_COMMAND_GetVPVersion:
			cam->params.vpVersion.vpVersion = data[0];
			cam->params.vpVersion.vpRevision = data[1];
			cam->params.vpVersion.cameraHeadID =
				data[2]+(((u16)data[3])<<8);
			break;
		case CPIA_COMMAND_GetColourParams:
			cam->params.colourParams.brightness = data[0];
			cam->params.colourParams.contrast = data[1];
			cam->params.colourParams.saturation = data[2];
			mutex_unlock(&cam->param_lock);
			break;
		case CPIA_COMMAND_GetColourBalance:
			cam->params.colourBalance.redGain = data[0];
			cam->params.colourBalance.greenGain = data[1];
			cam->params.colourBalance.blueGain = data[2];
			mutex_unlock(&cam->param_lock);
			break;
		case CPIA_COMMAND_GetExposure:
			cam->params.exposure.gain = data[0];
			cam->params.exposure.fineExp = data[1];
			cam->params.exposure.coarseExpLo = data[2];
			cam->params.exposure.coarseExpHi = data[3];
			cam->params.exposure.redComp = data[4];
			cam->params.exposure.green1Comp = data[5];
			cam->params.exposure.green2Comp = data[6];
			cam->params.exposure.blueComp = data[7];
			mutex_unlock(&cam->param_lock);
			break;

		case CPIA_COMMAND_ReadMCPorts:
			if (!cam->params.qx3.qx3_detected)
				break;
			/* test button press */
			cam->params.qx3.button = ((data[1] & 0x02) == 0);
			if (cam->params.qx3.button) {
				/* button pressed - unlock the latch */
				do_command(cam,CPIA_COMMAND_WriteMCPort,3,0xDF,0xDF,0);
				do_command(cam,CPIA_COMMAND_WriteMCPort,3,0xFF,0xFF,0);
			}

			/* test whether microscope is cradled */
			cam->params.qx3.cradled = ((data[2] & 0x40) == 0);
			break;

		default:
			break;
		}
	}
	return retval;
}