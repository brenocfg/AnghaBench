#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  dma; } ;
typedef  TYPE_1__ Adapter ;

/* Variables and functions */
 int /*<<< orphan*/  ICB_DIAG_FULL ; 
 int /*<<< orphan*/  IRQF_DISABLED ; 
 int /*<<< orphan*/  free_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ request_dma (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int wd7000_adapter_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  wd7000_diagnostics (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wd7000_enable_dma (TYPE_1__*) ; 
 int /*<<< orphan*/  wd7000_enable_intr (TYPE_1__*) ; 
 int /*<<< orphan*/  wd7000_intr ; 

__attribute__((used)) static int wd7000_init(Adapter * host)
{
	if (wd7000_adapter_reset(host) == -1)
		return 0;


	if (request_irq(host->irq, wd7000_intr, IRQF_DISABLED, "wd7000", host)) {
		printk("wd7000_init: can't get IRQ %d.\n", host->irq);
		return (0);
	}
	if (request_dma(host->dma, "wd7000")) {
		printk("wd7000_init: can't get DMA channel %d.\n", host->dma);
		free_irq(host->irq, host);
		return (0);
	}
	wd7000_enable_dma(host);
	wd7000_enable_intr(host);

	if (!wd7000_diagnostics(host, ICB_DIAG_FULL)) {
		free_dma(host->dma);
		free_irq(host->irq, NULL);
		return (0);
	}

	return (1);
}