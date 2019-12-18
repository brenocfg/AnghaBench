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
struct TYPE_5__ {int coarseExpLo; int coarseExpHi; int expMode; } ;
struct TYPE_4__ {scalar_t__ flickerMode; int coarseJump; int disabled; } ;
struct TYPE_6__ {TYPE_2__ exposure; TYPE_1__ flickerControl; } ;
struct cam_data {int* raw_image; int cmd_queue; int /*<<< orphan*/  param_lock; int /*<<< orphan*/  exposure_status; TYPE_3__ params; } ;

/* Variables and functions */
 int COMMAND_SETEXPOSURE ; 
 int /*<<< orphan*/  EXPOSURE_NORMAL ; 
 int /*<<< orphan*/  FIRMWARE_VERSION (int,int) ; 
 int ROUND_UP_EXP_FOR_FLICKER ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_flicker (TYPE_3__*,int*,int) ; 

__attribute__((used)) static void restart_flicker(struct cam_data *cam)
{
	int cam_exposure, old_exp;
	if(!FIRMWARE_VERSION(1,2))
		return;
	mutex_lock(&cam->param_lock);
	if(cam->params.flickerControl.flickerMode == 0 ||
	   cam->raw_image[39] == 0) {
		mutex_unlock(&cam->param_lock);
		return;
	}
	cam_exposure = cam->raw_image[39]*2;
	old_exp = cam->params.exposure.coarseExpLo +
		  cam->params.exposure.coarseExpHi*256;
	/*
	  see how far away camera exposure is from a valid
	  flicker exposure value
	*/
	cam_exposure %= cam->params.flickerControl.coarseJump;
	if(!cam->params.flickerControl.disabled &&
	   cam_exposure <= cam->params.flickerControl.coarseJump - 3) {
		/* Flicker control auto-disabled */
		cam->params.flickerControl.disabled = 1;
	}

	if(cam->params.flickerControl.disabled &&
	   cam->params.flickerControl.flickerMode &&
	   old_exp > cam->params.flickerControl.coarseJump +
		     ROUND_UP_EXP_FOR_FLICKER) {
		/* exposure is now high enough to switch
		   flicker control back on */
		set_flicker(&cam->params, &cam->cmd_queue, 1);
		if((cam->cmd_queue & COMMAND_SETEXPOSURE) &&
		   cam->params.exposure.expMode == 2)
			cam->exposure_status = EXPOSURE_NORMAL;

	}
	mutex_unlock(&cam->param_lock);
}