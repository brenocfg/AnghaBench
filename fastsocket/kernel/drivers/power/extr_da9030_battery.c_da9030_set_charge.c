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
typedef  int uint8_t ;
struct da9030_charger {int charge_milliamp; int charge_millivolt; int is_on; int /*<<< orphan*/  psy; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9030_CHARGE_CONTROL ; 
 int DA9030_CHRG_CHARGER_ENABLE ; 
 int /*<<< orphan*/  da903x_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  power_supply_changed (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void da9030_set_charge(struct da9030_charger *charger, int on)
{
	uint8_t val;

	if (on) {
		val = DA9030_CHRG_CHARGER_ENABLE;
		val |= (charger->charge_milliamp / 100) << 3;
		val |= (charger->charge_millivolt - 4000) / 50;
		charger->is_on = 1;
	} else {
		val = 0;
		charger->is_on = 0;
	}

	da903x_write(charger->master, DA9030_CHARGE_CONTROL, val);

	power_supply_changed(&charger->psy);
}