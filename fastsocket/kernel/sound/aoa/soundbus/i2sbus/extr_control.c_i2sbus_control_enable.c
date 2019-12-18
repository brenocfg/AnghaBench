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
struct pmf_args {int /*<<< orphan*/  count; } ;
struct macio_chip {int /*<<< orphan*/ * base; } ;
struct i2sbus_dev {int bus_number; scalar_t__ enable; } ;
struct i2sbus_control {struct macio_chip* macio; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  KEYLARGO_FCR1 ; 
 int /*<<< orphan*/  KL1_I2S0_ENABLE ; 
 int /*<<< orphan*/  KL1_I2S1_ENABLE ; 
 int /*<<< orphan*/  MACIO_BIS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pmf_call_one (scalar_t__,struct pmf_args*) ; 

int i2sbus_control_enable(struct i2sbus_control *c,
			  struct i2sbus_dev *i2sdev)
{
	struct pmf_args args = { .count = 0 };
	struct macio_chip *macio = c->macio;

	if (i2sdev->enable)
		return pmf_call_one(i2sdev->enable, &args);

	if (macio == NULL || macio->base == NULL)
		return -ENODEV;

	switch (i2sdev->bus_number) {
	case 0:
		/* these need to be locked or done through
		 * newly created feature calls! */
		MACIO_BIS(KEYLARGO_FCR1, KL1_I2S0_ENABLE);
		break;
	case 1:
		MACIO_BIS(KEYLARGO_FCR1, KL1_I2S1_ENABLE);
		break;
	default:
		return -ENODEV;
	}
	return 0;
}