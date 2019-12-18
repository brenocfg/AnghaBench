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
struct TYPE_2__ {int (* set_wake ) (unsigned int,unsigned int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  S3C2412_PWRCFG ; 
 unsigned long S3C2412_PWRCFG_RTC_MASKIRQ ; 
 unsigned long __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (unsigned long,int /*<<< orphan*/ ) ; 
 TYPE_1__ s3c_irq_chip ; 
 int stub1 (unsigned int,unsigned int) ; 

__attribute__((used)) static int s3c2412_irq_rtc_wake(unsigned int irqno, unsigned int state)
{
	unsigned long pwrcfg;

	pwrcfg = __raw_readl(S3C2412_PWRCFG);
	if (state)
		pwrcfg &= ~S3C2412_PWRCFG_RTC_MASKIRQ;
	else
		pwrcfg |= S3C2412_PWRCFG_RTC_MASKIRQ;
	__raw_writel(pwrcfg, S3C2412_PWRCFG);

	return s3c_irq_chip.set_wake(irqno, state);
}