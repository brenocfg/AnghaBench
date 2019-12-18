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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int CMOS_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMOS_WRITE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int RTC_AIE ; 
 int /*<<< orphan*/  RTC_CONTROL ; 
 int /*<<< orphan*/  RTC_INTR_FLAGS ; 
 int RTC_IRQF ; 
 int RTC_IRQMASK ; 
 int /*<<< orphan*/  hpet_mask_rtc_irq_bit (int) ; 
 scalar_t__ is_hpet_enabled () ; 
 scalar_t__ is_intr (int) ; 
 int /*<<< orphan*/  rtc_lock ; 
 int /*<<< orphan*/  rtc_update_irq (void*,int,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t cmos_interrupt(int irq, void *p)
{
	u8		irqstat;
	u8		rtc_control;

	spin_lock(&rtc_lock);

	/* When the HPET interrupt handler calls us, the interrupt
	 * status is passed as arg1 instead of the irq number.  But
	 * always clear irq status, even when HPET is in the way.
	 *
	 * Note that HPET and RTC are almost certainly out of phase,
	 * giving different IRQ status ...
	 */
	irqstat = CMOS_READ(RTC_INTR_FLAGS);
	rtc_control = CMOS_READ(RTC_CONTROL);
	if (is_hpet_enabled())
		irqstat = (unsigned long)irq & 0xF0;
	irqstat &= (rtc_control & RTC_IRQMASK) | RTC_IRQF;

	/* All Linux RTC alarms should be treated as if they were oneshot.
	 * Similar code may be needed in system wakeup paths, in case the
	 * alarm woke the system.
	 */
	if (irqstat & RTC_AIE) {
		rtc_control &= ~RTC_AIE;
		CMOS_WRITE(rtc_control, RTC_CONTROL);
		hpet_mask_rtc_irq_bit(RTC_AIE);

		CMOS_READ(RTC_INTR_FLAGS);
	}
	spin_unlock(&rtc_lock);

	if (is_intr(irqstat)) {
		rtc_update_irq(p, 1, irqstat);
		return IRQ_HANDLED;
	} else
		return IRQ_NONE;
}