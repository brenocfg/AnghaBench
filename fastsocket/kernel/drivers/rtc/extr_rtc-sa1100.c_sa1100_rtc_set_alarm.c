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
struct rtc_wkalrm {scalar_t__ enabled; int /*<<< orphan*/  time; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RTSR ; 
 int /*<<< orphan*/  RTSR_ALE ; 
 int rtc_update_alarm (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sa1100_rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sa1100_rtc_set_alarm(struct device *dev, struct rtc_wkalrm *alrm)
{
	int ret;

	spin_lock_irq(&sa1100_rtc_lock);
	ret = rtc_update_alarm(&alrm->time);
	if (ret == 0) {
		if (alrm->enabled)
			RTSR |= RTSR_ALE;
		else
			RTSR &= ~RTSR_ALE;
	}
	spin_unlock_irq(&sa1100_rtc_lock);

	return ret;
}