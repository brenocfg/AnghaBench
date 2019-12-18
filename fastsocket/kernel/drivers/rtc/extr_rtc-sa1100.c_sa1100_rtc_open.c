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
 int /*<<< orphan*/  IRQF_DISABLED ; 
 int /*<<< orphan*/  IRQ_OST1 ; 
 int /*<<< orphan*/  IRQ_RTC1Hz ; 
 int /*<<< orphan*/  IRQ_RTCAlrm ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct device*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct device*) ; 
 int /*<<< orphan*/  sa1100_rtc_interrupt ; 
 int /*<<< orphan*/  timer1_interrupt ; 

__attribute__((used)) static int sa1100_rtc_open(struct device *dev)
{
	int ret;

	ret = request_irq(IRQ_RTC1Hz, sa1100_rtc_interrupt, IRQF_DISABLED,
				"rtc 1Hz", dev);
	if (ret) {
		dev_err(dev, "IRQ %d already in use.\n", IRQ_RTC1Hz);
		goto fail_ui;
	}
	ret = request_irq(IRQ_RTCAlrm, sa1100_rtc_interrupt, IRQF_DISABLED,
				"rtc Alrm", dev);
	if (ret) {
		dev_err(dev, "IRQ %d already in use.\n", IRQ_RTCAlrm);
		goto fail_ai;
	}
	ret = request_irq(IRQ_OST1, timer1_interrupt, IRQF_DISABLED,
				"rtc timer", dev);
	if (ret) {
		dev_err(dev, "IRQ %d already in use.\n", IRQ_OST1);
		goto fail_pi;
	}
	return 0;

 fail_pi:
	free_irq(IRQ_RTCAlrm, dev);
 fail_ai:
	free_irq(IRQ_RTC1Hz, dev);
 fail_ui:
	return ret;
}