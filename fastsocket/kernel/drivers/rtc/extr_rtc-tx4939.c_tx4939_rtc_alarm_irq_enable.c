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
struct tx4939rtc_plat_data {TYPE_1__* rtc; int /*<<< orphan*/  rtcreg; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq_lock; } ;

/* Variables and functions */
 int TX4939_RTCCTL_ALME ; 
 int TX4939_RTCCTL_COMMAND_NOP ; 
 struct tx4939rtc_plat_data* get_tx4939rtc_plat_data (struct device*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx4939_rtc_cmd (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int tx4939_rtc_alarm_irq_enable(struct device *dev, unsigned int enabled)
{
	struct tx4939rtc_plat_data *pdata = get_tx4939rtc_plat_data(dev);

	spin_lock_irq(&pdata->rtc->irq_lock);
	tx4939_rtc_cmd(pdata->rtcreg,
		       TX4939_RTCCTL_COMMAND_NOP |
		       (enabled ? TX4939_RTCCTL_ALME : 0));
	spin_unlock_irq(&pdata->rtc->irq_lock);
	return 0;
}