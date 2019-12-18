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
typedef  int u32 ;
struct pxa_rtc {int /*<<< orphan*/  lock; int /*<<< orphan*/  rtc; } ;
struct platform_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned long RTC_AF ; 
 unsigned long RTC_IRQF ; 
 unsigned long RTC_PF ; 
 unsigned long RTC_UF ; 
 int /*<<< orphan*/  RTSR ; 
 int RTSR_HZ ; 
 int RTSR_HZE ; 
 int RTSR_PIAL ; 
 int RTSR_PIALE ; 
 int RTSR_RDAL1 ; 
 int RTSR_RDALE1 ; 
 int RTSR_TRIG_MASK ; 
 struct pxa_rtc* platform_get_drvdata (struct platform_device*) ; 
 int rtc_readl (struct pxa_rtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,unsigned long) ; 
 int /*<<< orphan*/  rtc_writel (struct pxa_rtc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtsr_clear_bits (struct pxa_rtc*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct platform_device* to_platform_device (void*) ; 

__attribute__((used)) static irqreturn_t pxa_rtc_irq(int irq, void *dev_id)
{
	struct platform_device *pdev = to_platform_device(dev_id);
	struct pxa_rtc *pxa_rtc = platform_get_drvdata(pdev);
	u32 rtsr;
	unsigned long events = 0;

	spin_lock(&pxa_rtc->lock);

	/* clear interrupt sources */
	rtsr = rtc_readl(pxa_rtc, RTSR);
	rtc_writel(pxa_rtc, RTSR, rtsr);

	/* temporary disable rtc interrupts */
	rtsr_clear_bits(pxa_rtc, RTSR_RDALE1 | RTSR_PIALE | RTSR_HZE);

	/* clear alarm interrupt if it has occurred */
	if (rtsr & RTSR_RDAL1)
		rtsr &= ~RTSR_RDALE1;

	/* update irq data & counter */
	if (rtsr & RTSR_RDAL1)
		events |= RTC_AF | RTC_IRQF;
	if (rtsr & RTSR_HZ)
		events |= RTC_UF | RTC_IRQF;
	if (rtsr & RTSR_PIAL)
		events |= RTC_PF | RTC_IRQF;

	rtc_update_irq(pxa_rtc->rtc, 1, events);

	/* enable back rtc interrupts */
	rtc_writel(pxa_rtc, RTSR, rtsr & ~RTSR_TRIG_MASK);

	spin_unlock(&pxa_rtc->lock);
	return IRQ_HANDLED;
}