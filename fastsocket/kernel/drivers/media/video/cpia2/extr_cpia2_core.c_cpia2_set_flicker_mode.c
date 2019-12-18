#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned char cam_register; int flicker_mode_req; int mains_frequency; } ;
struct TYPE_6__ {unsigned char exposure_modes; } ;
struct TYPE_5__ {scalar_t__ device_type; } ;
struct TYPE_8__ {TYPE_3__ flicker_control; TYPE_2__ vp_params; TYPE_1__ pnp_id; } ;
struct camera_data {TYPE_4__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPIA2_CMD_GET_FLICKER_MODES ; 
 int /*<<< orphan*/  CPIA2_CMD_GET_VP_EXP_MODES ; 
 int /*<<< orphan*/  CPIA2_CMD_REHASH_VP4 ; 
 int /*<<< orphan*/  CPIA2_CMD_SET_FLICKER_MODES ; 
 int /*<<< orphan*/  CPIA2_CMD_SET_VP_EXP_MODES ; 
 unsigned char CPIA2_VP_EXPOSURE_MODES_INHIBIT_FLICKER ; 
 unsigned char CPIA2_VP_FLICKER_MODES_50HZ ; 
 unsigned char CPIA2_VP_FLICKER_MODES_NEVER_FLICKER ; 
 scalar_t__ DEVICE_STV_672 ; 
 int EINVAL ; 
#define  FLICKER_50 130 
#define  FLICKER_60 129 
#define  NEVER_FLICKER 128 
 int /*<<< orphan*/  TRANSFER_READ ; 
 int /*<<< orphan*/  TRANSFER_WRITE ; 
 int cpia2_do_command (struct camera_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int cpia2_set_flicker_mode(struct camera_data *cam, int mode)
{
	unsigned char cam_reg;
	int err = 0;

	if(cam->params.pnp_id.device_type != DEVICE_STV_672)
		return -EINVAL;

	/* Set the appropriate bits in FLICKER_MODES, preserving the rest */
	if((err = cpia2_do_command(cam, CPIA2_CMD_GET_FLICKER_MODES,
				   TRANSFER_READ, 0)))
		return err;
	cam_reg = cam->params.flicker_control.cam_register;

	switch(mode) {
	case NEVER_FLICKER:
		cam_reg |= CPIA2_VP_FLICKER_MODES_NEVER_FLICKER;
		cam_reg &= ~CPIA2_VP_FLICKER_MODES_50HZ;
		break;
	case FLICKER_60:
		cam_reg &= ~CPIA2_VP_FLICKER_MODES_NEVER_FLICKER;
		cam_reg &= ~CPIA2_VP_FLICKER_MODES_50HZ;
		break;
	case FLICKER_50:
		cam_reg &= ~CPIA2_VP_FLICKER_MODES_NEVER_FLICKER;
		cam_reg |= CPIA2_VP_FLICKER_MODES_50HZ;
		break;
	default:
		return -EINVAL;
	}

	if((err = cpia2_do_command(cam, CPIA2_CMD_SET_FLICKER_MODES,
				   TRANSFER_WRITE, cam_reg)))
		return err;

	/* Set the appropriate bits in EXP_MODES, preserving the rest */
	if((err = cpia2_do_command(cam, CPIA2_CMD_GET_VP_EXP_MODES,
				   TRANSFER_READ, 0)))
		return err;
	cam_reg = cam->params.vp_params.exposure_modes;

	if (mode == NEVER_FLICKER) {
		cam_reg |= CPIA2_VP_EXPOSURE_MODES_INHIBIT_FLICKER;
	} else {
		cam_reg &= ~CPIA2_VP_EXPOSURE_MODES_INHIBIT_FLICKER;
	}

	if((err = cpia2_do_command(cam, CPIA2_CMD_SET_VP_EXP_MODES,
				   TRANSFER_WRITE, cam_reg)))
		return err;

	if((err = cpia2_do_command(cam, CPIA2_CMD_REHASH_VP4,
				   TRANSFER_WRITE, 1)))
		return err;

	switch(mode) {
	case NEVER_FLICKER:
		cam->params.flicker_control.flicker_mode_req = mode;
		break;
	case FLICKER_60:
		cam->params.flicker_control.flicker_mode_req = mode;
		cam->params.flicker_control.mains_frequency = 60;
		break;
	case FLICKER_50:
		cam->params.flicker_control.flicker_mode_req = mode;
		cam->params.flicker_control.mains_frequency = 50;
		break;
	default:
		err = -EINVAL;
	}

	return err;
}