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
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQF_TRIGGER_FALLING ; 
 int /*<<< orphan*/  IRQ_GPIOD (int) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,void*) ; 

__attribute__((used)) static int mx21ads_sdhc_init(struct device *dev, irq_handler_t detect_irq,
	void *data)
{
	int ret;

	ret = request_irq(IRQ_GPIOD(25), detect_irq,
		IRQF_TRIGGER_FALLING, "mmc-detect", data);
	if (ret)
		goto out;
	return 0;
out:
	return ret;
}