#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct twl4030_platform_data {int /*<<< orphan*/  vaux4; int /*<<< orphan*/  vaux3; int /*<<< orphan*/  vaux1; int /*<<< orphan*/  vsim; int /*<<< orphan*/  vmmc2; int /*<<< orphan*/  vpll2; int /*<<< orphan*/  vaux2; int /*<<< orphan*/  vdac; int /*<<< orphan*/  vmmc1; scalar_t__ irq_base; int /*<<< orphan*/ * usb; int /*<<< orphan*/ * madc; int /*<<< orphan*/ * keypad; int /*<<< orphan*/ * gpio; int /*<<< orphan*/ * bci; } ;
struct TYPE_2__ {int valid_modes_mask; int valid_ops_mask; } ;
struct regulator_init_data {TYPE_1__ constraints; } ;
struct regulator_consumer_supply {char* supply; struct device* dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct device*) ; 
 int PTR_ERR (struct device*) ; 
 int REGULATOR_CHANGE_MODE ; 
 int REGULATOR_CHANGE_STATUS ; 
 int REGULATOR_MODE_NORMAL ; 
 int REGULATOR_MODE_STANDBY ; 
 unsigned long TPS_SUBSET ; 
 int /*<<< orphan*/  TWL4030_REG_VAUX1 ; 
 int /*<<< orphan*/  TWL4030_REG_VAUX2 ; 
 int /*<<< orphan*/  TWL4030_REG_VAUX2_4030 ; 
 int /*<<< orphan*/  TWL4030_REG_VAUX3 ; 
 int /*<<< orphan*/  TWL4030_REG_VAUX4 ; 
 int /*<<< orphan*/  TWL4030_REG_VDAC ; 
 int /*<<< orphan*/  TWL4030_REG_VMMC1 ; 
 int /*<<< orphan*/  TWL4030_REG_VMMC2 ; 
 int /*<<< orphan*/  TWL4030_REG_VPLL2 ; 
 int /*<<< orphan*/  TWL4030_REG_VSIM ; 
 int /*<<< orphan*/  TWL4030_REG_VUSB1V5 ; 
 int /*<<< orphan*/  TWL4030_REG_VUSB1V8 ; 
 int /*<<< orphan*/  TWL4030_REG_VUSB3V1 ; 
 unsigned long TWL4030_VAUX2 ; 
 struct device* add_child (int,char*,int /*<<< orphan*/ *,int,int,scalar_t__,scalar_t__) ; 
 struct device* add_regulator (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct device* add_regulator_linked (int /*<<< orphan*/ ,struct regulator_init_data*,struct regulator_consumer_supply*,int) ; 
 scalar_t__ twl_has_bci () ; 
 scalar_t__ twl_has_gpio () ; 
 scalar_t__ twl_has_keypad () ; 
 scalar_t__ twl_has_madc () ; 
 scalar_t__ twl_has_pwrbutton () ; 
 scalar_t__ twl_has_regulator () ; 
 scalar_t__ twl_has_rtc () ; 
 scalar_t__ twl_has_usb () ; 
 scalar_t__ twl_has_watchdog () ; 

__attribute__((used)) static int
add_children(struct twl4030_platform_data *pdata, unsigned long features)
{
	struct device	*child;

	if (twl_has_bci() && pdata->bci && !(features & TPS_SUBSET)) {
		child = add_child(3, "twl4030_bci",
				pdata->bci, sizeof(*pdata->bci),
				false,
				/* irq0 = CHG_PRES, irq1 = BCI */
				pdata->irq_base + 8 + 1, pdata->irq_base + 2);
		if (IS_ERR(child))
			return PTR_ERR(child);
	}

	if (twl_has_gpio() && pdata->gpio) {
		child = add_child(1, "twl4030_gpio",
				pdata->gpio, sizeof(*pdata->gpio),
				false, pdata->irq_base + 0, 0);
		if (IS_ERR(child))
			return PTR_ERR(child);
	}

	if (twl_has_keypad() && pdata->keypad) {
		child = add_child(2, "twl4030_keypad",
				pdata->keypad, sizeof(*pdata->keypad),
				true, pdata->irq_base + 1, 0);
		if (IS_ERR(child))
			return PTR_ERR(child);
	}

	if (twl_has_madc() && pdata->madc) {
		child = add_child(2, "twl4030_madc",
				pdata->madc, sizeof(*pdata->madc),
				true, pdata->irq_base + 3, 0);
		if (IS_ERR(child))
			return PTR_ERR(child);
	}

	if (twl_has_rtc()) {
		/*
		 * REVISIT platform_data here currently might expose the
		 * "msecure" line ... but for now we just expect board
		 * setup to tell the chip "it's always ok to SET_TIME".
		 * Eventually, Linux might become more aware of such
		 * HW security concerns, and "least privilege".
		 */
		child = add_child(3, "twl4030_rtc",
				NULL, 0,
				true, pdata->irq_base + 8 + 3, 0);
		if (IS_ERR(child))
			return PTR_ERR(child);
	}

	if (twl_has_usb() && pdata->usb) {

		static struct regulator_consumer_supply usb1v5 = {
			.supply =	"usb1v5",
		};
		static struct regulator_consumer_supply usb1v8 = {
			.supply =	"usb1v8",
		};
		static struct regulator_consumer_supply usb3v1 = {
			.supply =	"usb3v1",
		};

	/* First add the regulators so that they can be used by transceiver */
		if (twl_has_regulator()) {
			/* this is a template that gets copied */
			struct regulator_init_data usb_fixed = {
				.constraints.valid_modes_mask =
					REGULATOR_MODE_NORMAL
					| REGULATOR_MODE_STANDBY,
				.constraints.valid_ops_mask =
					REGULATOR_CHANGE_MODE
					| REGULATOR_CHANGE_STATUS,
			};

			child = add_regulator_linked(TWL4030_REG_VUSB1V5,
						      &usb_fixed, &usb1v5, 1);
			if (IS_ERR(child))
				return PTR_ERR(child);

			child = add_regulator_linked(TWL4030_REG_VUSB1V8,
						      &usb_fixed, &usb1v8, 1);
			if (IS_ERR(child))
				return PTR_ERR(child);

			child = add_regulator_linked(TWL4030_REG_VUSB3V1,
						      &usb_fixed, &usb3v1, 1);
			if (IS_ERR(child))
				return PTR_ERR(child);

		}

		child = add_child(0, "twl4030_usb",
				pdata->usb, sizeof(*pdata->usb),
				true,
				/* irq0 = USB_PRES, irq1 = USB */
				pdata->irq_base + 8 + 2, pdata->irq_base + 4);

		if (IS_ERR(child))
			return PTR_ERR(child);

		/* we need to connect regulators to this transceiver */
		if (twl_has_regulator() && child) {
			usb1v5.dev = child;
			usb1v8.dev = child;
			usb3v1.dev = child;
		}
	}

	if (twl_has_watchdog()) {
		child = add_child(0, "twl4030_wdt", NULL, 0, false, 0, 0);
		if (IS_ERR(child))
			return PTR_ERR(child);
	}

	if (twl_has_pwrbutton()) {
		child = add_child(1, "twl4030_pwrbutton",
				NULL, 0, true, pdata->irq_base + 8 + 0, 0);
		if (IS_ERR(child))
			return PTR_ERR(child);
	}

	if (twl_has_regulator()) {
		/*
		child = add_regulator(TWL4030_REG_VPLL1, pdata->vpll1);
		if (IS_ERR(child))
			return PTR_ERR(child);
		*/

		child = add_regulator(TWL4030_REG_VMMC1, pdata->vmmc1);
		if (IS_ERR(child))
			return PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VDAC, pdata->vdac);
		if (IS_ERR(child))
			return PTR_ERR(child);

		child = add_regulator((features & TWL4030_VAUX2)
					? TWL4030_REG_VAUX2_4030
					: TWL4030_REG_VAUX2,
				pdata->vaux2);
		if (IS_ERR(child))
			return PTR_ERR(child);
	}

	/* maybe add LDOs that are omitted on cost-reduced parts */
	if (twl_has_regulator() && !(features & TPS_SUBSET)) {
		child = add_regulator(TWL4030_REG_VPLL2, pdata->vpll2);
		if (IS_ERR(child))
			return PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VMMC2, pdata->vmmc2);
		if (IS_ERR(child))
			return PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VSIM, pdata->vsim);
		if (IS_ERR(child))
			return PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VAUX1, pdata->vaux1);
		if (IS_ERR(child))
			return PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VAUX3, pdata->vaux3);
		if (IS_ERR(child))
			return PTR_ERR(child);

		child = add_regulator(TWL4030_REG_VAUX4, pdata->vaux4);
		if (IS_ERR(child))
			return PTR_ERR(child);
	}

	return 0;
}