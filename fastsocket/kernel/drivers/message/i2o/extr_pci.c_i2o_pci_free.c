#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ virt; } ;
struct TYPE_4__ {scalar_t__ virt; } ;
struct i2o_controller {TYPE_3__* pdev; TYPE_2__ base; TYPE_1__ in_queue; scalar_t__ raptor; int /*<<< orphan*/  status; int /*<<< orphan*/  hrt; int /*<<< orphan*/  dlct; int /*<<< orphan*/  lct; int /*<<< orphan*/  status_block; int /*<<< orphan*/  out_queue; } ;
struct device {int dummy; } ;
struct TYPE_6__ {struct device dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  i2o_dma_free (struct device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_release_regions (TYPE_3__*) ; 

__attribute__((used)) static void i2o_pci_free(struct i2o_controller *c)
{
	struct device *dev;

	dev = &c->pdev->dev;

	i2o_dma_free(dev, &c->out_queue);
	i2o_dma_free(dev, &c->status_block);
	kfree(c->lct);
	i2o_dma_free(dev, &c->dlct);
	i2o_dma_free(dev, &c->hrt);
	i2o_dma_free(dev, &c->status);

	if (c->raptor && c->in_queue.virt)
		iounmap(c->in_queue.virt);

	if (c->base.virt)
		iounmap(c->base.virt);

	pci_release_regions(c->pdev);
}