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
struct platform_device {int dummy; } ;
struct pcap_rtc {int /*<<< orphan*/  pcap; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  enable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcap_to_irq (int /*<<< orphan*/ ,int) ; 
 struct pcap_rtc* platform_get_drvdata (struct platform_device*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

__attribute__((used)) static int pcap_rtc_irq_enable(struct device *dev, int pirq, unsigned int en)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct pcap_rtc *pcap_rtc = platform_get_drvdata(pdev);

	if (en)
		enable_irq(pcap_to_irq(pcap_rtc->pcap, pirq));
	else
		disable_irq(pcap_to_irq(pcap_rtc->pcap, pirq));

	return 0;
}