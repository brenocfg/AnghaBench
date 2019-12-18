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
typedef  int u64 ;
struct device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  RTCL1HREG ; 
 int /*<<< orphan*/  RTCL1LREG ; 
 int RTC_FREQUENCY ; 
 int /*<<< orphan*/  do_div (int,int) ; 
 int /*<<< orphan*/  is_power_of_2 (int) ; 
 int periodic_count ; 
 int /*<<< orphan*/  rtc1_write (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vr41xx_rtc_irq_set_freq(struct device *dev, int freq)
{
	u64 count;

	if (!is_power_of_2(freq))
		return -EINVAL;
	count = RTC_FREQUENCY;
	do_div(count, freq);

	spin_lock_irq(&rtc_lock);

	periodic_count = count;
	rtc1_write(RTCL1LREG, periodic_count);
	rtc1_write(RTCL1HREG, periodic_count >> 16);

	spin_unlock_irq(&rtc_lock);

	return 0;
}