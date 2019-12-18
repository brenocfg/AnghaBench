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
struct twlreg_info {int /*<<< orphan*/  id; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEV_GRP_P1 ; 
 int EACCES ; 
 int EINVAL ; 
 unsigned int MSG_SINGULAR (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int P1_GRP ; 
 int P2_GRP ; 
 int P3_GRP ; 
#define  REGULATOR_MODE_NORMAL 129 
#define  REGULATOR_MODE_STANDBY 128 
 int /*<<< orphan*/  RES_STATE_ACTIVE ; 
 int /*<<< orphan*/  RES_STATE_SLEEP ; 
 int /*<<< orphan*/  TWL4030_MODULE_PM_MASTER ; 
 struct twlreg_info* rdev_get_drvdata (struct regulator_dev*) ; 
 int twl4030_i2c_write_u8 (int /*<<< orphan*/ ,unsigned int,int) ; 
 int twl4030reg_grp (struct regulator_dev*) ; 

__attribute__((used)) static int twl4030reg_set_mode(struct regulator_dev *rdev, unsigned mode)
{
	struct twlreg_info	*info = rdev_get_drvdata(rdev);
	unsigned		message;
	int			status;

	/* We can only set the mode through state machine commands... */
	switch (mode) {
	case REGULATOR_MODE_NORMAL:
		message = MSG_SINGULAR(DEV_GRP_P1, info->id, RES_STATE_ACTIVE);
		break;
	case REGULATOR_MODE_STANDBY:
		message = MSG_SINGULAR(DEV_GRP_P1, info->id, RES_STATE_SLEEP);
		break;
	default:
		return -EINVAL;
	}

	/* Ensure the resource is associated with some group */
	status = twl4030reg_grp(rdev);
	if (status < 0)
		return status;
	if (!(status & (P3_GRP | P2_GRP | P1_GRP)))
		return -EACCES;

	status = twl4030_i2c_write_u8(TWL4030_MODULE_PM_MASTER,
			message >> 8, 0x15 /* PB_WORD_MSB */ );
	if (status >= 0)
		return status;

	return twl4030_i2c_write_u8(TWL4030_MODULE_PM_MASTER,
			message, 0x16 /* PB_WORD_LSB */ );
}