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
struct ab3100_regulator {int regreg; int /*<<< orphan*/  ab3100; } ;

/* Variables and functions */
#define  AB3100_BUCK 136 
#define  AB3100_LDO_A 135 
#define  AB3100_LDO_C 134 
#define  AB3100_LDO_D 133 
#define  AB3100_LDO_E 132 
#define  AB3100_LDO_F 131 
#define  AB3100_LDO_G 130 
#define  AB3100_LDO_H 129 
#define  AB3100_LDO_K 128 
 int AB3100_REG_ON_MASK ; 
 int ab3100_get_register_interruptible (int /*<<< orphan*/ ,int,int*) ; 
 int ab3100_set_register_interruptible (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int ab3100_enable_regulator(struct regulator_dev *reg)
{
	struct ab3100_regulator *abreg = reg->reg_data;
	int err;
	u8 regval;

	err = ab3100_get_register_interruptible(abreg->ab3100, abreg->regreg,
						&regval);
	if (err) {
		dev_warn(&reg->dev, "failed to get regid %d value\n",
			 abreg->regreg);
		return err;
	}

	/* The regulator is already on, no reason to go further */
	if (regval & AB3100_REG_ON_MASK)
		return 0;

	regval |= AB3100_REG_ON_MASK;

	err = ab3100_set_register_interruptible(abreg->ab3100, abreg->regreg,
						regval);
	if (err) {
		dev_warn(&reg->dev, "failed to set regid %d value\n",
			 abreg->regreg);
		return err;
	}

	/* Per-regulator power on delay from spec */
	switch (abreg->regreg) {
	case AB3100_LDO_A: /* Fallthrough */
	case AB3100_LDO_C: /* Fallthrough */
	case AB3100_LDO_D: /* Fallthrough */
	case AB3100_LDO_E: /* Fallthrough */
	case AB3100_LDO_H: /* Fallthrough */
	case AB3100_LDO_K:
		udelay(200);
		break;
	case AB3100_LDO_F:
		udelay(600);
		break;
	case AB3100_LDO_G:
		udelay(400);
		break;
	case AB3100_BUCK:
		mdelay(1);
		break;
	default:
		break;
	}

	return 0;
}