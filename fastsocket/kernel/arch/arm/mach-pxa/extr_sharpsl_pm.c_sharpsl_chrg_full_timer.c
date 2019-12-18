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
struct TYPE_4__ {int full_count; scalar_t__ charge_mode; int /*<<< orphan*/  dev; scalar_t__ charge_start_time; TYPE_1__* machinfo; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* read_devdata ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ CHRG_DONE ; 
 scalar_t__ CHRG_ON ; 
 scalar_t__ SHARPSL_CHARGE_FINISH_TIME ; 
 int /*<<< orphan*/  SHARPSL_STATUS_ACIN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sharpsl_charge_off () ; 
 TYPE_2__ sharpsl_pm ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  toggle_charger ; 

__attribute__((used)) static void sharpsl_chrg_full_timer(unsigned long data)
{
	dev_dbg(sharpsl_pm.dev, "Charge Full at time: %lx\n", jiffies);

	sharpsl_pm.full_count++;

	if (!sharpsl_pm.machinfo->read_devdata(SHARPSL_STATUS_ACIN)) {
		dev_dbg(sharpsl_pm.dev, "Charge Full: AC removed - stop charging!\n");
		if (sharpsl_pm.charge_mode == CHRG_ON)
			sharpsl_charge_off();
	} else if (sharpsl_pm.full_count < 2) {
		dev_dbg(sharpsl_pm.dev, "Charge Full: Count too low\n");
		schedule_delayed_work(&toggle_charger, 0);
	} else if (time_after(jiffies, sharpsl_pm.charge_start_time + SHARPSL_CHARGE_FINISH_TIME)) {
		dev_dbg(sharpsl_pm.dev, "Charge Full: Interrupt generated too slowly - retry.\n");
		schedule_delayed_work(&toggle_charger, 0);
	} else {
		sharpsl_charge_off();
		sharpsl_pm.charge_mode = CHRG_DONE;
		dev_dbg(sharpsl_pm.dev, "Charge Full: Charging Finished\n");
	}
}