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
struct slic_rspqueue {int num_pages; int /*<<< orphan*/ * rspbuf; scalar_t__ pageindex; scalar_t__ offset; scalar_t__* paddr; int /*<<< orphan*/ ** vaddr; } ;
struct adapter {int /*<<< orphan*/  pcidev; struct slic_rspqueue rspqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void slic_rspqueue_free(struct adapter *adapter)
{
	int i;
	struct slic_rspqueue *rspq = &adapter->rspqueue;

	for (i = 0; i < rspq->num_pages; i++) {
		if (rspq->vaddr[i]) {
			pci_free_consistent(adapter->pcidev, PAGE_SIZE,
					    rspq->vaddr[i], rspq->paddr[i]);
		}
		rspq->vaddr[i] = NULL;
		rspq->paddr[i] = 0;
	}
	rspq->offset = 0;
	rspq->pageindex = 0;
	rspq->rspbuf = NULL;
}