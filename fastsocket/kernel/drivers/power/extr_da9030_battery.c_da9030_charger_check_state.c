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
struct TYPE_4__ {scalar_t__ vbat_charge_start; scalar_t__ vbat_charge_stop; scalar_t__ vbat_charge_restart; scalar_t__ vbat_low; scalar_t__ vcharge_max; scalar_t__ vcharge_min; scalar_t__ tbat_high; scalar_t__ tbat_low; } ;
struct TYPE_3__ {scalar_t__ vbat_res; scalar_t__ vchmax_res; scalar_t__ vchmin_res; scalar_t__ tbat_res; } ;
struct da9030_charger {TYPE_2__ thresholds; TYPE_1__ adc; int /*<<< orphan*/  master; scalar_t__ chdet; int /*<<< orphan*/  is_on; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA9030_VBATMON ; 
 int /*<<< orphan*/  da9030_charger_update_state (struct da9030_charger*) ; 
 int /*<<< orphan*/  da9030_set_charge (struct da9030_charger*,int) ; 
 int /*<<< orphan*/  da903x_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void da9030_charger_check_state(struct da9030_charger *charger)
{
	da9030_charger_update_state(charger);

	/* we wake or boot with external power on */
	if (!charger->is_on) {
		if ((charger->chdet) &&
		    (charger->adc.vbat_res <
		     charger->thresholds.vbat_charge_start)) {
			da9030_set_charge(charger, 1);
		}
	} else {
		/* Charger has been pulled out */
		if (!charger->chdet) {
			da9030_set_charge(charger, 0);
			return;
		}

		if (charger->adc.vbat_res >=
		    charger->thresholds.vbat_charge_stop) {
			da9030_set_charge(charger, 0);
			da903x_write(charger->master, DA9030_VBATMON,
				       charger->thresholds.vbat_charge_restart);
		} else if (charger->adc.vbat_res >
			   charger->thresholds.vbat_low) {
			/* we are charging and passed LOW_THRESH,
			   so upate DA9030 VBAT threshold
			 */
			da903x_write(charger->master, DA9030_VBATMON,
				     charger->thresholds.vbat_low);
		}
		if (charger->adc.vchmax_res > charger->thresholds.vcharge_max ||
		    charger->adc.vchmin_res < charger->thresholds.vcharge_min ||
		    /* Tempreture readings are negative */
		    charger->adc.tbat_res < charger->thresholds.tbat_high ||
		    charger->adc.tbat_res > charger->thresholds.tbat_low) {
			/* disable charger */
			da9030_set_charge(charger, 0);
		}
	}
}