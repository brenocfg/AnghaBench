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
struct TYPE_4__ {scalar_t__ charge_mode; int /*<<< orphan*/  dev; TYPE_1__* machinfo; } ;
struct TYPE_3__ {int (* read_devdata ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ CHRG_ON ; 
 int /*<<< orphan*/  SHARPSL_STATUS_ACIN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sharpsl_average_clear () ; 
 int /*<<< orphan*/  sharpsl_bat ; 
 int /*<<< orphan*/  sharpsl_charge_off () ; 
 int /*<<< orphan*/  sharpsl_charge_on () ; 
 TYPE_2__ sharpsl_pm ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sharpsl_ac_timer(unsigned long data)
{
	int acin = sharpsl_pm.machinfo->read_devdata(SHARPSL_STATUS_ACIN);

	dev_dbg(sharpsl_pm.dev, "AC Status: %d\n",acin);

	sharpsl_average_clear();
	if (acin && (sharpsl_pm.charge_mode != CHRG_ON))
		sharpsl_charge_on();
	else if (sharpsl_pm.charge_mode == CHRG_ON)
		sharpsl_charge_off();

	schedule_delayed_work(&sharpsl_bat, 0);
}