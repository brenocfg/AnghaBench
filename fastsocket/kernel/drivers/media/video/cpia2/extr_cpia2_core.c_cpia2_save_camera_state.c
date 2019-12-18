#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct camera_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPIA2_CMD_GET_USER_EFFECTS ; 
 int /*<<< orphan*/  CPIA2_CMD_GET_VC_MP_GPIO_DATA ; 
 int /*<<< orphan*/  CPIA2_CMD_GET_VC_MP_GPIO_DIRECTION ; 
 int /*<<< orphan*/  TRANSFER_READ ; 
 int /*<<< orphan*/  cpia2_do_command (struct camera_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_color_params (struct camera_data*) ; 

void cpia2_save_camera_state(struct camera_data *cam)
{
	get_color_params(cam);
	cpia2_do_command(cam, CPIA2_CMD_GET_USER_EFFECTS, TRANSFER_READ, 0);
	cpia2_do_command(cam, CPIA2_CMD_GET_VC_MP_GPIO_DIRECTION, TRANSFER_READ,
			 0);
	cpia2_do_command(cam, CPIA2_CMD_GET_VC_MP_GPIO_DATA, TRANSFER_READ, 0);
	/* Don't get framerate or target_kb. Trust the values we already have */
}