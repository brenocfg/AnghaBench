#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;
typedef  struct TYPE_16__   TYPE_12__ ;
typedef  struct TYPE_15__   TYPE_11__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ cradled; scalar_t__ button; scalar_t__ bottomlight; scalar_t__ toplight; scalar_t__ qx3_detected; } ;
struct TYPE_16__ {int targetFR; int targetQ; int /*<<< orphan*/  frTargeting; } ;
struct TYPE_15__ {int /*<<< orphan*/  decimation; int /*<<< orphan*/  mode; } ;
struct TYPE_14__ {int /*<<< orphan*/  yuvOrder; int /*<<< orphan*/  subSample; } ;
struct TYPE_26__ {int yThreshold; int uvThreshold; } ;
struct TYPE_25__ {size_t baserate; size_t divisor; } ;
struct TYPE_24__ {int hysteresis; int threshMax; int smallStep; int largeStep; int decimationHysteresis; int frDiffStepThresh; int qDiffStepThresh; int decimationThreshMod; } ;
struct TYPE_23__ {int gain1; int gain2; int gain4; int gain8; } ;
struct TYPE_22__ {int /*<<< orphan*/  brightness; int /*<<< orphan*/  saturation; int /*<<< orphan*/  contrast; } ;
struct TYPE_21__ {int disabled; int /*<<< orphan*/  allowableOverExposure; int /*<<< orphan*/  coarseJump; scalar_t__ flickerMode; } ;
struct TYPE_20__ {int gain1; int gain2; int gain4; int gain8; } ;
struct TYPE_19__ {int balanceMode; int redGain; int greenGain; int blueGain; } ;
struct TYPE_18__ {int gainMode; int expMode; int compMode; int centreWeight; int coarseExpLo; int /*<<< orphan*/  blueComp; int /*<<< orphan*/  green2Comp; int /*<<< orphan*/  green1Comp; int /*<<< orphan*/  redComp; scalar_t__ coarseExpHi; scalar_t__ fineExp; scalar_t__ gain; } ;
struct cam_params {TYPE_13__ qx3; TYPE_12__ compressionTarget; TYPE_11__ compression; TYPE_10__ format; TYPE_9__ yuvThreshold; TYPE_8__ sensorFps; TYPE_7__ compressionParams; TYPE_6__ vlOffset; TYPE_5__ colourParams; TYPE_4__ flickerControl; TYPE_3__ apcor; TYPE_2__ colourBalance; TYPE_1__ exposure; } ;
struct sd {size_t mainsFreq; struct cam_params params; } ;
struct gspca_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRIGHTNESS_DEF ; 
 int /*<<< orphan*/  COMP_BLUE ; 
 int /*<<< orphan*/  COMP_GREEN1 ; 
 int /*<<< orphan*/  COMP_GREEN2 ; 
 int /*<<< orphan*/  COMP_RED ; 
 int /*<<< orphan*/  COMP_TARGET_DEF ; 
 int /*<<< orphan*/  CONTRAST_DEF ; 
 int /*<<< orphan*/  CPIA_COMPRESSION_AUTO ; 
 int /*<<< orphan*/  NO_DECIMATION ; 
 int /*<<< orphan*/  SATURATION_DEF ; 
 int /*<<< orphan*/  SUBSAMPLE_420 ; 
 int /*<<< orphan*/  YUVORDER_YUYV ; 
 int /*<<< orphan*/  find_over_exposure (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ *** flicker_jumps ; 

__attribute__((used)) static void reset_camera_params(struct gspca_dev *gspca_dev)
{
	struct sd *sd = (struct sd *) gspca_dev;
	struct cam_params *params = &sd->params;

	/* The following parameter values are the defaults from
	 * "Software Developer's Guide for CPiA Cameras".  Any changes
	 * to the defaults are noted in comments. */
	params->colourParams.brightness = BRIGHTNESS_DEF;
	params->colourParams.contrast = CONTRAST_DEF;
	params->colourParams.saturation = SATURATION_DEF;
	params->exposure.gainMode = 4;
	params->exposure.expMode = 2;		/* AEC */
	params->exposure.compMode = 1;
	params->exposure.centreWeight = 1;
	params->exposure.gain = 0;
	params->exposure.fineExp = 0;
	params->exposure.coarseExpLo = 185;
	params->exposure.coarseExpHi = 0;
	params->exposure.redComp = COMP_RED;
	params->exposure.green1Comp = COMP_GREEN1;
	params->exposure.green2Comp = COMP_GREEN2;
	params->exposure.blueComp = COMP_BLUE;
	params->colourBalance.balanceMode = 2;	/* ACB */
	params->colourBalance.redGain = 32;
	params->colourBalance.greenGain = 6;
	params->colourBalance.blueGain = 92;
	params->apcor.gain1 = 0x18;
	params->apcor.gain2 = 0x16;
	params->apcor.gain4 = 0x24;
	params->apcor.gain8 = 0x34;
	params->flickerControl.flickerMode = 0;
	params->flickerControl.disabled = 1;

	params->flickerControl.coarseJump =
		flicker_jumps[sd->mainsFreq]
			     [params->sensorFps.baserate]
			     [params->sensorFps.divisor];
	params->flickerControl.allowableOverExposure =
		find_over_exposure(params->colourParams.brightness);
	params->vlOffset.gain1 = 20;
	params->vlOffset.gain2 = 24;
	params->vlOffset.gain4 = 26;
	params->vlOffset.gain8 = 26;
	params->compressionParams.hysteresis = 3;
	params->compressionParams.threshMax = 11;
	params->compressionParams.smallStep = 1;
	params->compressionParams.largeStep = 3;
	params->compressionParams.decimationHysteresis = 2;
	params->compressionParams.frDiffStepThresh = 5;
	params->compressionParams.qDiffStepThresh = 3;
	params->compressionParams.decimationThreshMod = 2;
	/* End of default values from Software Developer's Guide */

	/* Set Sensor FPS to 15fps. This seems better than 30fps
	 * for indoor lighting. */
	params->sensorFps.divisor = 1;
	params->sensorFps.baserate = 1;

	params->yuvThreshold.yThreshold = 6; /* From windows driver */
	params->yuvThreshold.uvThreshold = 6; /* From windows driver */

	params->format.subSample = SUBSAMPLE_420;
	params->format.yuvOrder = YUVORDER_YUYV;

	params->compression.mode = CPIA_COMPRESSION_AUTO;
	params->compression.decimation = NO_DECIMATION;

	params->compressionTarget.frTargeting = COMP_TARGET_DEF;
	params->compressionTarget.targetFR = 15; /* From windows driver */
	params->compressionTarget.targetQ = 5; /* From windows driver */

	params->qx3.qx3_detected = 0;
	params->qx3.toplight = 0;
	params->qx3.bottomlight = 0;
	params->qx3.button = 0;
	params->qx3.cradled = 0;
}