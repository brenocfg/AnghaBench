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
struct pvscsi_adapter {int req_pages; int cmp_pages; int msg_pages; int /*<<< orphan*/  msgRingPA; scalar_t__ msg_ring; int /*<<< orphan*/  dev; int /*<<< orphan*/  cmpRingPA; scalar_t__ cmp_ring; int /*<<< orphan*/  reqRingPA; scalar_t__ req_ring; int /*<<< orphan*/  ringStatePA; scalar_t__ rings_state; scalar_t__ cmd_map; scalar_t__ mmioBase; scalar_t__ workqueue; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  destroy_workqueue (scalar_t__) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_iounmap (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pci_release_regions (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pvscsi_free_sgls (struct pvscsi_adapter*) ; 
 int /*<<< orphan*/  pvscsi_shutdown_intr (struct pvscsi_adapter*) ; 

__attribute__((used)) static void pvscsi_release_resources(struct pvscsi_adapter *adapter)
{
	pvscsi_shutdown_intr(adapter);

	if (adapter->workqueue)
		destroy_workqueue(adapter->workqueue);

	if (adapter->mmioBase)
		pci_iounmap(adapter->dev, adapter->mmioBase);

	pci_release_regions(adapter->dev);

	if (adapter->cmd_map) {
		pvscsi_free_sgls(adapter);
		kfree(adapter->cmd_map);
	}

	if (adapter->rings_state)
		pci_free_consistent(adapter->dev, PAGE_SIZE,
				    adapter->rings_state, adapter->ringStatePA);

	if (adapter->req_ring)
		pci_free_consistent(adapter->dev,
				    adapter->req_pages * PAGE_SIZE,
				    adapter->req_ring, adapter->reqRingPA);

	if (adapter->cmp_ring)
		pci_free_consistent(adapter->dev,
				    adapter->cmp_pages * PAGE_SIZE,
				    adapter->cmp_ring, adapter->cmpRingPA);

	if (adapter->msg_ring)
		pci_free_consistent(adapter->dev,
				    adapter->msg_pages * PAGE_SIZE,
				    adapter->msg_ring, adapter->msgRingPA);
}