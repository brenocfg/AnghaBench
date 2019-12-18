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
struct nic {int /*<<< orphan*/ * mem; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  pdev; } ;
struct mem {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void e100_free(struct nic *nic)
{
	if (nic->mem) {
		pci_free_consistent(nic->pdev, sizeof(struct mem),
			nic->mem, nic->dma_addr);
		nic->mem = NULL;
	}
}