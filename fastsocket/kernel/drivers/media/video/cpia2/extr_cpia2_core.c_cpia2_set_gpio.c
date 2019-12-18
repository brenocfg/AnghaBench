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
struct TYPE_3__ {int gpio_direction; unsigned char gpio_data; } ;
struct TYPE_4__ {TYPE_1__ vp_params; } ;
struct camera_data {TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPIA2_CMD_SET_VC_MP_GPIO_DATA ; 
 int /*<<< orphan*/  CPIA2_CMD_SET_VC_MP_GPIO_DIRECTION ; 
 int /*<<< orphan*/  CPIA2_VC_MP_DIR_OUTPUT ; 
 int cpia2_do_command (struct camera_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char) ; 

int cpia2_set_gpio(struct camera_data *cam, unsigned char setting)
{
	int ret;

	/* Set the microport direction (register 0x90, should be defined
	 * already) to 1 (user output), and set the microport data (0x91) to
	 * the value in the ioctl argument.
	 */

	ret = cpia2_do_command(cam,
			       CPIA2_CMD_SET_VC_MP_GPIO_DIRECTION,
			       CPIA2_VC_MP_DIR_OUTPUT,
			       255);
	if (ret < 0)
		return ret;
	cam->params.vp_params.gpio_direction = 255;

	ret = cpia2_do_command(cam,
			       CPIA2_CMD_SET_VC_MP_GPIO_DATA,
			       CPIA2_VC_MP_DIR_OUTPUT,
			       setting);
	if (ret < 0)
		return ret;
	cam->params.vp_params.gpio_data = setting;

	return 0;
}