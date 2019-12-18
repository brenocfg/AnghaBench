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
struct TYPE_4__ {int /*<<< orphan*/  dev; TYPE_1__* machinfo; } ;
struct TYPE_3__ {int (* read_devdata ) (int /*<<< orphan*/ ) ;int charge_acin_high; int charge_acin_low; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHARPSL_ACIN_VOLT ; 
 int /*<<< orphan*/  SHARPSL_CHECK_BATTERY_WAIT_TIME_ACIN ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int get_select_val (int*) ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 TYPE_2__ sharpsl_pm ; 
 int stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sharpsl_ac_check(void)
{
	int temp, i, buff[5];

	for (i=0; i<5; i++) {
		buff[i] = sharpsl_pm.machinfo->read_devdata(SHARPSL_ACIN_VOLT);
		mdelay(SHARPSL_CHECK_BATTERY_WAIT_TIME_ACIN);
	}

	temp = get_select_val(buff);
	dev_dbg(sharpsl_pm.dev, "AC Voltage: %d\n",temp);

	if ((temp > sharpsl_pm.machinfo->charge_acin_high) || (temp < sharpsl_pm.machinfo->charge_acin_low)) {
		dev_err(sharpsl_pm.dev, "Error: AC check failed.\n");
		return -1;
	}

	return 0;
}