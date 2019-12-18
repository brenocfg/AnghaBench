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
struct ab3100_regulator {int fixed_voltage; int voltages_len; int* typ_voltages; int /*<<< orphan*/  regreg; int /*<<< orphan*/  ab3100; } ;

/* Variables and functions */
 int EINVAL ; 
 int ab3100_get_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ab3100_get_voltage_regulator(struct regulator_dev *reg)
{
	struct ab3100_regulator *abreg = reg->reg_data;
	u8 regval;
	int err;

	/* Return the voltage for fixed regulators immediately */
	if (abreg->fixed_voltage)
		return abreg->fixed_voltage;

	/*
	 * For variable types, read out setting and index into
	 * supplied voltage list.
	 */
	err = ab3100_get_register_interruptible(abreg->ab3100,
						abreg->regreg, &regval);
	if (err) {
		dev_warn(&reg->dev,
			 "failed to get regulator value in register %02x\n",
			 abreg->regreg);
		return err;
	}

	/* The 3 highest bits index voltages */
	regval &= 0xE0;
	regval >>= 5;

	if (regval > abreg->voltages_len) {
		dev_err(&reg->dev,
			"regulator register %02x contains an illegal voltage setting\n",
			abreg->regreg);
		return -EINVAL;
	}

	return abreg->typ_voltages[regval];
}