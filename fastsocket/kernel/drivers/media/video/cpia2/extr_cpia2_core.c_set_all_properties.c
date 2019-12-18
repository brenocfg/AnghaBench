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
struct TYPE_6__ {int /*<<< orphan*/  gpio_data; int /*<<< orphan*/  gpio_direction; int /*<<< orphan*/  user_effects; } ;
struct TYPE_8__ {int /*<<< orphan*/  flicker_mode_req; } ;
struct TYPE_5__ {int /*<<< orphan*/  stream_mode; } ;
struct TYPE_7__ {TYPE_2__ vp_params; TYPE_4__ flicker_control; TYPE_1__ camera_state; } ;
struct camera_data {TYPE_3__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPIA2_CMD_SET_USER_EFFECTS ; 
 int /*<<< orphan*/  CPIA2_CMD_SET_VC_MP_GPIO_DATA ; 
 int /*<<< orphan*/  CPIA2_CMD_SET_VC_MP_GPIO_DIRECTION ; 
 int /*<<< orphan*/  TRANSFER_WRITE ; 
 int /*<<< orphan*/  cpia2_do_command (struct camera_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpia2_set_color_params (struct camera_data*) ; 
 int /*<<< orphan*/  cpia2_set_flicker_mode (struct camera_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpia2_usb_change_streaming_alternate (struct camera_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_lowlight_boost (struct camera_data*) ; 
 int /*<<< orphan*/  wake_system (struct camera_data*) ; 

__attribute__((used)) static int set_all_properties(struct camera_data *cam)
{
	/**
	 * Don't set target_kb here, it will be set later.
	 * framerate and user_mode were already set (set_default_user_mode).
	 **/

	cpia2_set_color_params(cam);

	cpia2_usb_change_streaming_alternate(cam,
					  cam->params.camera_state.stream_mode);

	cpia2_do_command(cam, CPIA2_CMD_SET_USER_EFFECTS, TRANSFER_WRITE,
			 cam->params.vp_params.user_effects);

	cpia2_set_flicker_mode(cam,
			       cam->params.flicker_control.flicker_mode_req);

	cpia2_do_command(cam,
			 CPIA2_CMD_SET_VC_MP_GPIO_DIRECTION,
			 TRANSFER_WRITE, cam->params.vp_params.gpio_direction);
	cpia2_do_command(cam, CPIA2_CMD_SET_VC_MP_GPIO_DATA, TRANSFER_WRITE,
			 cam->params.vp_params.gpio_data);

	wake_system(cam);

	set_lowlight_boost(cam);

	return 0;
}