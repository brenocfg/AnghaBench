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
typedef  int u8 ;
struct regulator_dev {int /*<<< orphan*/  dev; struct ab3100_regulator* reg_data; } ;
struct ab3100_regulator {int /*<<< orphan*/  regreg; int /*<<< orphan*/  ab3100; } ;

/* Variables and functions */
 int AB3100_REG_ON_MASK ; 
 int ab3100_get_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ab3100_is_enabled_regulator(struct regulator_dev *reg)
{
	struct ab3100_regulator *abreg = reg->reg_data;
	u8 regval;
	int err;

	err = ab3100_get_register_interruptible(abreg->ab3100, abreg->regreg,
						&regval);
	if (err) {
		dev_err(&reg->dev, "unable to get register 0x%x\n",
			abreg->regreg);
		return err;
	}

	return regval & AB3100_REG_ON_MASK;
}