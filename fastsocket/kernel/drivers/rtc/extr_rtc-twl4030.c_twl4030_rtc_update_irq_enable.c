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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_RTC_INTERRUPTS_REG_IT_TIMER_M ; 
 int mask_rtc_irq_bit (int /*<<< orphan*/ ) ; 
 int set_rtc_irq_bit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int twl4030_rtc_update_irq_enable(struct device *dev, unsigned enabled)
{
	int ret;

	if (enabled)
		ret = set_rtc_irq_bit(BIT_RTC_INTERRUPTS_REG_IT_TIMER_M);
	else
		ret = mask_rtc_irq_bit(BIT_RTC_INTERRUPTS_REG_IT_TIMER_M);

	return ret;
}