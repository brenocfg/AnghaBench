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
struct dma_prog_region {int n_pages; scalar_t__ bus_addr; int /*<<< orphan*/ * dev; int /*<<< orphan*/ * kvirt; } ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,scalar_t__) ; 

void dma_prog_region_free(struct dma_prog_region *prog)
{
	if (prog->kvirt) {
		pci_free_consistent(prog->dev, prog->n_pages << PAGE_SHIFT,
				    prog->kvirt, prog->bus_addr);
	}

	prog->kvirt = NULL;
	prog->dev = NULL;
	prog->n_pages = 0;
	prog->bus_addr = 0;
}