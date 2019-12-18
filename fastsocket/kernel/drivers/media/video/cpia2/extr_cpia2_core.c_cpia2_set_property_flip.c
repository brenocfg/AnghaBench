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
struct TYPE_3__ {unsigned char user_effects; } ;
struct TYPE_4__ {TYPE_1__ vp_params; } ;
struct camera_data {TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPIA2_CMD_GET_USER_EFFECTS ; 
 int /*<<< orphan*/  CPIA2_CMD_SET_USER_EFFECTS ; 
 unsigned char CPIA2_VP_USER_EFFECTS_FLIP ; 
 int /*<<< orphan*/  TRANSFER_READ ; 
 int /*<<< orphan*/  TRANSFER_WRITE ; 
 int /*<<< orphan*/  cpia2_do_command (struct camera_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 

void cpia2_set_property_flip(struct camera_data *cam, int prop_val)
{
	unsigned char cam_reg;

	cpia2_do_command(cam, CPIA2_CMD_GET_USER_EFFECTS, TRANSFER_READ, 0);
	cam_reg = cam->params.vp_params.user_effects;

	if (prop_val)
	{
		cam_reg |= CPIA2_VP_USER_EFFECTS_FLIP;
	}
	else
	{
		cam_reg &= ~CPIA2_VP_USER_EFFECTS_FLIP;
	}
	cpia2_do_command(cam, CPIA2_CMD_SET_USER_EFFECTS, TRANSFER_WRITE,
			 cam_reg);
}