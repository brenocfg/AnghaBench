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
typedef  int u8 ;
typedef  int irqreturn_t ;

/* Variables and functions */
 int BIT_RTC_STATUS_REG_ALARM_M ; 
 int IRQ_HANDLED ; 
 int IRQ_NONE ; 
 int /*<<< orphan*/  REG_RTC_STATUS_REG ; 
 unsigned long RTC_AF ; 
 unsigned long RTC_IRQF ; 
 unsigned long RTC_UF ; 
 int /*<<< orphan*/  TWL4030_INT_PWR_ISR1 ; 
 int /*<<< orphan*/  TWL4030_MODULE_INT ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  rtc_update_irq (void*,int,unsigned long) ; 
 int twl4030_i2c_read_u8 (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ) ; 
 int twl4030_rtc_read_u8 (int*,int /*<<< orphan*/ ) ; 
 int twl4030_rtc_write_u8 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t twl4030_rtc_interrupt(int irq, void *rtc)
{
	unsigned long events = 0;
	int ret = IRQ_NONE;
	int res;
	u8 rd_reg;

#ifdef CONFIG_LOCKDEP
	/* WORKAROUND for lockdep forcing IRQF_DISABLED on us, which
	 * we don't want and can't tolerate.  Although it might be
	 * friendlier not to borrow this thread context...
	 */
	local_irq_enable();
#endif

	res = twl4030_rtc_read_u8(&rd_reg, REG_RTC_STATUS_REG);
	if (res)
		goto out;
	/*
	 * Figure out source of interrupt: ALARM or TIMER in RTC_STATUS_REG.
	 * only one (ALARM or RTC) interrupt source may be enabled
	 * at time, we also could check our results
	 * by reading RTS_INTERRUPTS_REGISTER[IT_TIMER,IT_ALARM]
	 */
	if (rd_reg & BIT_RTC_STATUS_REG_ALARM_M)
		events |= RTC_IRQF | RTC_AF;
	else
		events |= RTC_IRQF | RTC_UF;

	res = twl4030_rtc_write_u8(rd_reg | BIT_RTC_STATUS_REG_ALARM_M,
				   REG_RTC_STATUS_REG);
	if (res)
		goto out;

	/* Clear on Read enabled. RTC_IT bit of TWL4030_INT_PWR_ISR1
	 * needs 2 reads to clear the interrupt. One read is done in
	 * do_twl4030_pwrirq(). Doing the second read, to clear
	 * the bit.
	 *
	 * FIXME the reason PWR_ISR1 needs an extra read is that
	 * RTC_IF retriggered until we cleared REG_ALARM_M above.
	 * But re-reading like this is a bad hack; by doing so we
	 * risk wrongly clearing status for some other IRQ (losing
	 * the interrupt).  Be smarter about handling RTC_UF ...
	 */
	res = twl4030_i2c_read_u8(TWL4030_MODULE_INT,
			&rd_reg, TWL4030_INT_PWR_ISR1);
	if (res)
		goto out;

	/* Notify RTC core on event */
	rtc_update_irq(rtc, 1, events);

	ret = IRQ_HANDLED;
out:
	return ret;
}