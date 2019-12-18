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
struct TYPE_3__ {int /*<<< orphan*/  power_mode; } ;
struct TYPE_4__ {TYPE_1__ camera_state; } ;
struct camera_data {TYPE_2__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPIA2_CMD_SET_SYSTEM_CTRL ; 
 int /*<<< orphan*/  LO_POWER_MODE ; 
 int /*<<< orphan*/  TRANSFER_WRITE ; 
 int /*<<< orphan*/  cpia2_do_command (struct camera_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int cpia2_set_low_power(struct camera_data *cam)
{
	cam->params.camera_state.power_mode = LO_POWER_MODE;
	cpia2_do_command(cam, CPIA2_CMD_SET_SYSTEM_CTRL, TRANSFER_WRITE, 0);
	return 0;
}