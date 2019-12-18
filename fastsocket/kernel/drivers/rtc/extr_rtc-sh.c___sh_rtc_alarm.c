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
struct sh_rtc {int /*<<< orphan*/  rtc_dev; scalar_t__ regbase; } ;

/* Variables and functions */
 scalar_t__ RCR1 ; 
 unsigned int RCR1_AF ; 
 unsigned int RCR1_AIE ; 
 int RTC_AF ; 
 int RTC_IRQF ; 
 unsigned int readb (scalar_t__) ; 
 int /*<<< orphan*/  rtc_update_irq (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  writeb (unsigned int,scalar_t__) ; 

__attribute__((used)) static int __sh_rtc_alarm(struct sh_rtc *rtc)
{
	unsigned int tmp, pending;

	tmp = readb(rtc->regbase + RCR1);
	pending = tmp & RCR1_AF;
	tmp &= ~(RCR1_AF | RCR1_AIE);
	writeb(tmp, rtc->regbase + RCR1);

	if (pending)
		rtc_update_irq(rtc->rtc_dev, 1, RTC_AF | RTC_IRQF);

	return pending;
}