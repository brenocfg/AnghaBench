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
struct pxa_rtc {int /*<<< orphan*/  irq_1Hz; int /*<<< orphan*/  irq_Alrm; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int RTSR_HZE ; 
 int RTSR_PIALE ; 
 int RTSR_RDALE1 ; 
 struct pxa_rtc* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct device*) ; 
 int /*<<< orphan*/  rtsr_clear_bits (struct pxa_rtc*,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pxa_rtc_release(struct device *dev)
{
	struct pxa_rtc *pxa_rtc = dev_get_drvdata(dev);

	spin_lock_irq(&pxa_rtc->lock);
	rtsr_clear_bits(pxa_rtc, RTSR_PIALE | RTSR_RDALE1 | RTSR_HZE);
	spin_unlock_irq(&pxa_rtc->lock);

	free_irq(pxa_rtc->irq_Alrm, dev);
	free_irq(pxa_rtc->irq_1Hz, dev);
}