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
struct ohci_hcd {int /*<<< orphan*/ * ed_cache; int /*<<< orphan*/ * td_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ohci_mem_cleanup (struct ohci_hcd *ohci)
{
	if (ohci->td_cache) {
		dma_pool_destroy (ohci->td_cache);
		ohci->td_cache = NULL;
	}
	if (ohci->ed_cache) {
		dma_pool_destroy (ohci->ed_cache);
		ohci->ed_cache = NULL;
	}
}