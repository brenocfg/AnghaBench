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
struct rtc_device {int dummy; } ;
struct platform_device {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELAPSEDTIME_INT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  RTCINTREG ; 
 int /*<<< orphan*/  RTC_AF ; 
 struct rtc_device* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  rtc2_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtc_update_irq (struct rtc_device*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t elapsedtime_interrupt(int irq, void *dev_id)
{
	struct platform_device *pdev = (struct platform_device *)dev_id;
	struct rtc_device *rtc = platform_get_drvdata(pdev);

	rtc2_write(RTCINTREG, ELAPSEDTIME_INT);

	rtc_update_irq(rtc, 1, RTC_AF);

	return IRQ_HANDLED;
}