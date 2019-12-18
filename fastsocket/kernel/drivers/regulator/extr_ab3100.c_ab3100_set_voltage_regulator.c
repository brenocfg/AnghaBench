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
 int ab3100_get_best_voltage_index (struct regulator_dev*,int,int) ; 
 int ab3100_get_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int ab3100_set_register_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ab3100_set_voltage_regulator(struct regulator_dev *reg,
					int min_uV, int max_uV)
{
	struct ab3100_regulator *abreg = reg->reg_data;
	u8 regval;
	int err;
	int bestindex;

	bestindex = ab3100_get_best_voltage_index(reg, min_uV, max_uV);
	if (bestindex < 0)
		return bestindex;

	err = ab3100_get_register_interruptible(abreg->ab3100,
						abreg->regreg, &regval);
	if (err) {
		dev_warn(&reg->dev,
			 "failed to get regulator register %02x\n",
			 abreg->regreg);
		return err;
	}

	/* The highest three bits control the variable regulators */
	regval &= ~0xE0;
	regval |= (bestindex << 5);

	err = ab3100_set_register_interruptible(abreg->ab3100,
						abreg->regreg, regval);
	if (err)
		dev_warn(&reg->dev, "failed to set regulator register %02x\n",
			abreg->regreg);

	return err;
}