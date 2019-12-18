#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  blueGain; int /*<<< orphan*/  greenGain; int /*<<< orphan*/  redGain; } ;
struct TYPE_4__ {int /*<<< orphan*/  blueComp; int /*<<< orphan*/  green2Comp; int /*<<< orphan*/  green1Comp; int /*<<< orphan*/  redComp; int /*<<< orphan*/  coarseExpHi; int /*<<< orphan*/  coarseExpLo; int /*<<< orphan*/  fineExp; int /*<<< orphan*/  gain; } ;
struct TYPE_6__ {TYPE_2__ colourBalance; TYPE_1__ exposure; } ;
struct cam_data {int cmd_queue; TYPE_3__ params; } ;

/* Variables and functions */
 int COMMAND_SETCOLOURBALANCE ; 
 int COMMAND_SETEXPOSURE ; 
 int /*<<< orphan*/  CPIA_COMMAND_GetColourBalance ; 
 int /*<<< orphan*/  CPIA_COMMAND_GetExposure ; 
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  do_command (struct cam_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void save_camera_state(struct cam_data *cam)
{
	if(!(cam->cmd_queue & COMMAND_SETCOLOURBALANCE))
		do_command(cam, CPIA_COMMAND_GetColourBalance, 0, 0, 0, 0);
	if(!(cam->cmd_queue & COMMAND_SETEXPOSURE))
		do_command(cam, CPIA_COMMAND_GetExposure, 0, 0, 0, 0);

	DBG("%d/%d/%d/%d/%d/%d/%d/%d\n",
	     cam->params.exposure.gain,
	     cam->params.exposure.fineExp,
	     cam->params.exposure.coarseExpLo,
	     cam->params.exposure.coarseExpHi,
	     cam->params.exposure.redComp,
	     cam->params.exposure.green1Comp,
	     cam->params.exposure.green2Comp,
	     cam->params.exposure.blueComp);
	DBG("%d/%d/%d\n",
	     cam->params.colourBalance.redGain,
	     cam->params.colourBalance.greenGain,
	     cam->params.colourBalance.blueGain);
}