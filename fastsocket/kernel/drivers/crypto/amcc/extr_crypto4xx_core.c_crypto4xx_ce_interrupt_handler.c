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
struct device {int dummy; } ;
struct crypto4xx_core_device {int /*<<< orphan*/  tasklet; TYPE_1__* dev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {scalar_t__ ce_base; } ;

/* Variables and functions */
 scalar_t__ CRYPTO4XX_INT_CLR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  PPC4XX_INTERRUPT_CLR ; 
 struct crypto4xx_core_device* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static irqreturn_t crypto4xx_ce_interrupt_handler(int irq, void *data)
{
	struct device *dev = (struct device *)data;
	struct crypto4xx_core_device *core_dev = dev_get_drvdata(dev);

	if (core_dev->dev->ce_base == 0)
		return 0;

	writel(PPC4XX_INTERRUPT_CLR,
	       core_dev->dev->ce_base + CRYPTO4XX_INT_CLR);
	tasklet_schedule(&core_dev->tasklet);

	return IRQ_HANDLED;
}