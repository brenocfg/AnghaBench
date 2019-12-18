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
typedef  int u8 ;
struct TYPE_11__ {int coarseExpHi; int coarseExpLo; scalar_t__ gain; int gainMode; } ;
struct TYPE_10__ {int divisor; size_t baserate; } ;
struct TYPE_9__ {int coarseJump; int /*<<< orphan*/  disabled; } ;
struct TYPE_8__ {int brightness; } ;
struct TYPE_12__ {TYPE_5__ exposure; TYPE_4__ sensorFps; TYPE_3__ flickerControl; TYPE_2__ colourParams; } ;
struct cam_data {scalar_t__ exposure_status; int exposure_count; int fps; size_t mainsFreq; int /*<<< orphan*/  param_lock; int /*<<< orphan*/  cmd_queue; TYPE_6__ params; int /*<<< orphan*/  lowlevel_data; TYPE_1__* ops; } ;
struct TYPE_7__ {int (* transferCmd ) (int /*<<< orphan*/ ,int*,int*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND_SETEXPOSURE ; 
 int /*<<< orphan*/  COMMAND_SETFLICKERCTRL ; 
 int /*<<< orphan*/  COMMAND_SETSENSORFPS ; 
 int CPIA_COMMAND_ReadVPRegs ; 
 int DARK_TIME ; 
 scalar_t__ EXPOSURE_DARK ; 
 scalar_t__ EXPOSURE_LIGHT ; 
 void* EXPOSURE_NORMAL ; 
 scalar_t__ EXPOSURE_VERY_DARK ; 
 scalar_t__ EXPOSURE_VERY_LIGHT ; 
 int EXP_ACC_DARK ; 
 int EXP_ACC_LIGHT ; 
 scalar_t__ FIRMWARE_VERSION (int,int) ; 
 int HIGH_COMP_102 ; 
 int LIGHT_TIME ; 
 int /*<<< orphan*/  LOG (char*,...) ; 
 int LOW_EXP ; 
 int MAX_COMP ; 
 int MAX_EXP ; 
 int MAX_EXP_102 ; 
 int /*<<< orphan*/  TC ; 
 int VERY_LOW_EXP ; 
 void**** flicker_jumps ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static void monitor_exposure(struct cam_data *cam)
{
	u8 exp_acc, bcomp, gain, coarseL, cmd[8], data[8];
	int retval, light_exp, dark_exp, very_dark_exp;
	int old_exposure, new_exposure, framerate;

	/* get necessary stats and register settings from camera */
	/* do_command can't handle this, so do it ourselves */
	cmd[0] = CPIA_COMMAND_ReadVPRegs>>8;
	cmd[1] = CPIA_COMMAND_ReadVPRegs&0xff;
	cmd[2] = 30;
	cmd[3] = 4;
	cmd[4] = 9;
	cmd[5] = 8;
	cmd[6] = 8;
	cmd[7] = 0;
	retval = cam->ops->transferCmd(cam->lowlevel_data, cmd, data);
	if (retval) {
		LOG("ReadVPRegs(30,4,9,8) - failed, retval=%d\n",
		    retval);
		return;
	}
	exp_acc = data[0];
	bcomp = data[1];
	gain = data[2];
	coarseL = data[3];

	mutex_lock(&cam->param_lock);
	light_exp = cam->params.colourParams.brightness +
		    TC - 50 + EXP_ACC_LIGHT;
	if(light_exp > 255)
		light_exp = 255;
	dark_exp = cam->params.colourParams.brightness +
		   TC - 50 - EXP_ACC_DARK;
	if(dark_exp < 0)
		dark_exp = 0;
	very_dark_exp = dark_exp/2;

	old_exposure = cam->params.exposure.coarseExpHi * 256 +
		       cam->params.exposure.coarseExpLo;

	if(!cam->params.flickerControl.disabled) {
		/* Flicker control on */
		int max_comp = FIRMWARE_VERSION(1,2) ? MAX_COMP : HIGH_COMP_102;
		bcomp += 128;	/* decode */
		if(bcomp >= max_comp && exp_acc < dark_exp) {
			/* dark */
			if(exp_acc < very_dark_exp) {
				/* very dark */
				if(cam->exposure_status == EXPOSURE_VERY_DARK)
					++cam->exposure_count;
				else {
					cam->exposure_status = EXPOSURE_VERY_DARK;
					cam->exposure_count = 1;
				}
			} else {
				/* just dark */
				if(cam->exposure_status == EXPOSURE_DARK)
					++cam->exposure_count;
				else {
					cam->exposure_status = EXPOSURE_DARK;
					cam->exposure_count = 1;
				}
			}
		} else if(old_exposure <= LOW_EXP || exp_acc > light_exp) {
			/* light */
			if(old_exposure <= VERY_LOW_EXP) {
				/* very light */
				if(cam->exposure_status == EXPOSURE_VERY_LIGHT)
					++cam->exposure_count;
				else {
					cam->exposure_status = EXPOSURE_VERY_LIGHT;
					cam->exposure_count = 1;
				}
			} else {
				/* just light */
				if(cam->exposure_status == EXPOSURE_LIGHT)
					++cam->exposure_count;
				else {
					cam->exposure_status = EXPOSURE_LIGHT;
					cam->exposure_count = 1;
				}
			}
		} else {
			/* not dark or light */
			cam->exposure_status = EXPOSURE_NORMAL;
		}
	} else {
		/* Flicker control off */
		if(old_exposure >= MAX_EXP && exp_acc < dark_exp) {
			/* dark */
			if(exp_acc < very_dark_exp) {
				/* very dark */
				if(cam->exposure_status == EXPOSURE_VERY_DARK)
					++cam->exposure_count;
				else {
					cam->exposure_status = EXPOSURE_VERY_DARK;
					cam->exposure_count = 1;
				}
			} else {
				/* just dark */
				if(cam->exposure_status == EXPOSURE_DARK)
					++cam->exposure_count;
				else {
					cam->exposure_status = EXPOSURE_DARK;
					cam->exposure_count = 1;
				}
			}
		} else if(old_exposure <= LOW_EXP || exp_acc > light_exp) {
			/* light */
			if(old_exposure <= VERY_LOW_EXP) {
				/* very light */
				if(cam->exposure_status == EXPOSURE_VERY_LIGHT)
					++cam->exposure_count;
				else {
					cam->exposure_status = EXPOSURE_VERY_LIGHT;
					cam->exposure_count = 1;
				}
			} else {
				/* just light */
				if(cam->exposure_status == EXPOSURE_LIGHT)
					++cam->exposure_count;
				else {
					cam->exposure_status = EXPOSURE_LIGHT;
					cam->exposure_count = 1;
				}
			}
		} else {
			/* not dark or light */
			cam->exposure_status = EXPOSURE_NORMAL;
		}
	}

	framerate = cam->fps;
	if(framerate > 30 || framerate < 1)
		framerate = 1;

	if(!cam->params.flickerControl.disabled) {
		/* Flicker control on */
		if((cam->exposure_status == EXPOSURE_VERY_DARK ||
		    cam->exposure_status == EXPOSURE_DARK) &&
		   cam->exposure_count >= DARK_TIME*framerate &&
		   cam->params.sensorFps.divisor < 3) {

			/* dark for too long */
			++cam->params.sensorFps.divisor;
			cam->cmd_queue |= COMMAND_SETSENSORFPS;

			cam->params.flickerControl.coarseJump =
				flicker_jumps[cam->mainsFreq]
					     [cam->params.sensorFps.baserate]
					     [cam->params.sensorFps.divisor];
			cam->cmd_queue |= COMMAND_SETFLICKERCTRL;

			new_exposure = cam->params.flickerControl.coarseJump-1;
			while(new_exposure < old_exposure/2)
				new_exposure += cam->params.flickerControl.coarseJump;
			cam->params.exposure.coarseExpLo = new_exposure & 0xff;
			cam->params.exposure.coarseExpHi = new_exposure >> 8;
			cam->cmd_queue |= COMMAND_SETEXPOSURE;
			cam->exposure_status = EXPOSURE_NORMAL;
			LOG("Automatically decreasing sensor_fps\n");

		} else if((cam->exposure_status == EXPOSURE_VERY_LIGHT ||
		    cam->exposure_status == EXPOSURE_LIGHT) &&
		   cam->exposure_count >= LIGHT_TIME*framerate &&
		   cam->params.sensorFps.divisor > 0) {

			/* light for too long */
			int max_exp = FIRMWARE_VERSION(1,2) ? MAX_EXP_102 : MAX_EXP ;

			--cam->params.sensorFps.divisor;
			cam->cmd_queue |= COMMAND_SETSENSORFPS;

			cam->params.flickerControl.coarseJump =
				flicker_jumps[cam->mainsFreq]
					     [cam->params.sensorFps.baserate]
					     [cam->params.sensorFps.divisor];
			cam->cmd_queue |= COMMAND_SETFLICKERCTRL;

			new_exposure = cam->params.flickerControl.coarseJump-1;
			while(new_exposure < 2*old_exposure &&
			      new_exposure+
			      cam->params.flickerControl.coarseJump < max_exp)
				new_exposure += cam->params.flickerControl.coarseJump;
			cam->params.exposure.coarseExpLo = new_exposure & 0xff;
			cam->params.exposure.coarseExpHi = new_exposure >> 8;
			cam->cmd_queue |= COMMAND_SETEXPOSURE;
			cam->exposure_status = EXPOSURE_NORMAL;
			LOG("Automatically increasing sensor_fps\n");
		}
	} else {
		/* Flicker control off */
		if((cam->exposure_status == EXPOSURE_VERY_DARK ||
		    cam->exposure_status == EXPOSURE_DARK) &&
		   cam->exposure_count >= DARK_TIME*framerate &&
		   cam->params.sensorFps.divisor < 3) {

			/* dark for too long */
			++cam->params.sensorFps.divisor;
			cam->cmd_queue |= COMMAND_SETSENSORFPS;

			if(cam->params.exposure.gain > 0) {
				--cam->params.exposure.gain;
				cam->cmd_queue |= COMMAND_SETEXPOSURE;
			}
			cam->exposure_status = EXPOSURE_NORMAL;
			LOG("Automatically decreasing sensor_fps\n");

		} else if((cam->exposure_status == EXPOSURE_VERY_LIGHT ||
		    cam->exposure_status == EXPOSURE_LIGHT) &&
		   cam->exposure_count >= LIGHT_TIME*framerate &&
		   cam->params.sensorFps.divisor > 0) {

			/* light for too long */
			--cam->params.sensorFps.divisor;
			cam->cmd_queue |= COMMAND_SETSENSORFPS;

			if(cam->params.exposure.gain <
			   cam->params.exposure.gainMode-1) {
				++cam->params.exposure.gain;
				cam->cmd_queue |= COMMAND_SETEXPOSURE;
			}
			cam->exposure_status = EXPOSURE_NORMAL;
			LOG("Automatically increasing sensor_fps\n");
		}
	}
	mutex_unlock(&cam->param_lock);
}