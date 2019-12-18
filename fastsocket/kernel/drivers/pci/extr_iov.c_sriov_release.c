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
struct pci_dev {TYPE_1__* sriov; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; struct pci_dev* dev; int /*<<< orphan*/  nr_virtfn; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pci_dev_put (struct pci_dev*) ; 

__attribute__((used)) static void sriov_release(struct pci_dev *dev)
{
	BUG_ON(dev->sriov->nr_virtfn);

	if (dev != dev->sriov->dev)
		pci_dev_put(dev->sriov->dev);

	mutex_destroy(&dev->sriov->lock);

	kfree(dev->sriov);
	dev->sriov = NULL;
}