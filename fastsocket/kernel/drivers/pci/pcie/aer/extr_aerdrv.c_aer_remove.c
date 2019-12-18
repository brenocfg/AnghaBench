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
struct pcie_device {int /*<<< orphan*/  irq; } ;
struct aer_rpc {scalar_t__ prod_idx; scalar_t__ cons_idx; int /*<<< orphan*/  wait_release; scalar_t__ isr; } ;

/* Variables and functions */
 int /*<<< orphan*/  aer_disable_rootport (struct aer_rpc*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct pcie_device*) ; 
 struct aer_rpc* get_service_data (struct pcie_device*) ; 
 int /*<<< orphan*/  kfree (struct aer_rpc*) ; 
 int /*<<< orphan*/  set_service_data (struct pcie_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void aer_remove(struct pcie_device *dev)
{
	struct aer_rpc *rpc = get_service_data(dev);

	if (rpc) {
		/* If register interrupt service, it must be free. */
		if (rpc->isr)
			free_irq(dev->irq, dev);

		wait_event(rpc->wait_release, rpc->prod_idx == rpc->cons_idx);

		aer_disable_rootport(rpc);
		kfree(rpc);
		set_service_data(dev, NULL);
	}
}