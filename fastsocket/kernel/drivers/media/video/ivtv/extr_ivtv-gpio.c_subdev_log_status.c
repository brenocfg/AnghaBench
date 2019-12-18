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
struct v4l2_subdev {int /*<<< orphan*/  name; } ;
struct ivtv {int /*<<< orphan*/  hdl_gpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_INFO (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IVTV_REG_GPIO_DIR ; 
 int /*<<< orphan*/  IVTV_REG_GPIO_IN ; 
 int /*<<< orphan*/  IVTV_REG_GPIO_OUT ; 
 int /*<<< orphan*/  read_reg (int /*<<< orphan*/ ) ; 
 struct ivtv* sd_to_ivtv (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_log_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int subdev_log_status(struct v4l2_subdev *sd)
{
	struct ivtv *itv = sd_to_ivtv(sd);

	IVTV_INFO("GPIO status: DIR=0x%04x OUT=0x%04x IN=0x%04x\n",
			read_reg(IVTV_REG_GPIO_DIR), read_reg(IVTV_REG_GPIO_OUT),
			read_reg(IVTV_REG_GPIO_IN));
	v4l2_ctrl_handler_log_status(&itv->hdl_gpio, sd->name);
	return 0;
}