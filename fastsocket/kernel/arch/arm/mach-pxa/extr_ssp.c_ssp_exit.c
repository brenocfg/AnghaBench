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
struct ssp_device {int /*<<< orphan*/  clk; } ;
struct ssp_dev {scalar_t__ irq; struct ssp_device* ssp; } ;

/* Variables and functions */
 scalar_t__ NO_IRQ ; 
 int /*<<< orphan*/  clk_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,struct ssp_dev*) ; 
 int /*<<< orphan*/  ssp_disable (struct ssp_dev*) ; 
 int /*<<< orphan*/  ssp_free (struct ssp_device*) ; 

void ssp_exit(struct ssp_dev *dev)
{
	struct ssp_device *ssp = dev->ssp;

	ssp_disable(dev);
	if (dev->irq != NO_IRQ)
		free_irq(dev->irq, dev);
	clk_disable(ssp->clk);
	ssp_free(ssp);
}