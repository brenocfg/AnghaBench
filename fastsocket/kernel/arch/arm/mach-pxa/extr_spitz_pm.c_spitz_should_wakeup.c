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
struct TYPE_4__ {int /*<<< orphan*/  dev; int /*<<< orphan*/  charge_mode; TYPE_1__* machinfo; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int (* read_devdata ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* charge ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CHRG_OFF ; 
 int GPIO_bit (int /*<<< orphan*/ ) ; 
 int PEDR ; 
 int PKSR ; 
 int PWER_RTC ; 
 int /*<<< orphan*/  SHARPSL_DO_OFFLINE_CHRG ; 
 int /*<<< orphan*/  SHARPSL_LED_OFF ; 
 int /*<<< orphan*/  SHARPSL_STATUS_ACIN ; 
 int /*<<< orphan*/  SPITZ_GPIO_KEY_INT ; 
 int /*<<< orphan*/  SPITZ_GPIO_SYNC ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 TYPE_2__ sharpsl_pm ; 
 int /*<<< orphan*/  sharpsl_pm_led (int /*<<< orphan*/ ) ; 
 int spitz_last_ac_status ; 
 int stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int spitz_should_wakeup(unsigned int resume_on_alarm)
{
	int is_resume = 0;
	int acin = sharpsl_pm.machinfo->read_devdata(SHARPSL_STATUS_ACIN);

	if (spitz_last_ac_status != acin) {
		if (acin) {
			/* charge on */
			sharpsl_pm.flags |= SHARPSL_DO_OFFLINE_CHRG;
			dev_dbg(sharpsl_pm.dev, "AC Inserted\n");
		} else {
			/* charge off */
			dev_dbg(sharpsl_pm.dev, "AC Removed\n");
			sharpsl_pm_led(SHARPSL_LED_OFF);
			sharpsl_pm.machinfo->charge(0);
			sharpsl_pm.charge_mode = CHRG_OFF;
		}
		spitz_last_ac_status = acin;
		/* Return to suspend as this must be what we were woken for */
		return 0;
	}

	if (PEDR & GPIO_bit(SPITZ_GPIO_KEY_INT))
		is_resume |= GPIO_bit(SPITZ_GPIO_KEY_INT);

	if (PKSR & GPIO_bit(SPITZ_GPIO_SYNC))
		is_resume |= GPIO_bit(SPITZ_GPIO_SYNC);

	if (resume_on_alarm && (PEDR & PWER_RTC))
		is_resume |= PWER_RTC;

	dev_dbg(sharpsl_pm.dev, "is_resume: %x\n",is_resume);
	return is_resume;
}