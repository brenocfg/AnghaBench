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
typedef  int u32 ;
struct atmel_abdac {TYPE_1__* pdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int DAC_BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INT_CLR ; 
 int /*<<< orphan*/  INT_STATUS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  UNDERRUN ; 
 int dac_readl (struct atmel_abdac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dac_writel (struct atmel_abdac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static irqreturn_t abdac_interrupt(int irq, void *dev_id)
{
	struct atmel_abdac *dac = dev_id;
	u32 status;

	status = dac_readl(dac, INT_STATUS);
	if (status & DAC_BIT(UNDERRUN)) {
		dev_err(&dac->pdev->dev, "underrun detected\n");
		dac_writel(dac, INT_CLR, DAC_BIT(UNDERRUN));
	} else {
		dev_err(&dac->pdev->dev, "spurious interrupt (status=0x%x)\n",
			status);
		dac_writel(dac, INT_CLR, status);
	}

	return IRQ_HANDLED;
}