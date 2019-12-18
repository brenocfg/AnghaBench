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
struct sh_rtc {unsigned int periodic_freq; int /*<<< orphan*/  lock; scalar_t__ regbase; } ;
struct device {int dummy; } ;

/* Variables and functions */
 unsigned int PF_HP ; 
 unsigned int PF_KOU ; 
 scalar_t__ RCR2 ; 
 unsigned int RCR2_PEF ; 
 unsigned int RCR2_PESMASK ; 
 struct sh_rtc* dev_get_drvdata (struct device*) ; 
 unsigned int readb (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 

__attribute__((used)) static int sh_rtc_irq_set_state(struct device *dev, int enable)
{
	struct sh_rtc *rtc = dev_get_drvdata(dev);
	unsigned int tmp;

	spin_lock_irq(&rtc->lock);

	tmp = readb(rtc->regbase + RCR2);

	if (enable) {
		rtc->periodic_freq |= PF_KOU;
		tmp &= ~RCR2_PEF;	/* Clear PES bit */
		tmp |= (rtc->periodic_freq & ~PF_HP);	/* Set PES2-0 */
	} else {
		rtc->periodic_freq &= ~PF_KOU;
		tmp &= ~(RCR2_PESMASK | RCR2_PEF);
	}

	writeb(tmp, rtc->regbase + RCR2);

	spin_unlock_irq(&rtc->lock);

	return 0;
}