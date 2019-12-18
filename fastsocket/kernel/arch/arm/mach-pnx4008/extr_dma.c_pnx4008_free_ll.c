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
typedef  int /*<<< orphan*/  u32 ;
struct pnx4008_dma_ll {struct pnx4008_dma_ll* next; int /*<<< orphan*/  next_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  pnx4008_free_ll_entry (struct pnx4008_dma_ll*,int /*<<< orphan*/ ) ; 

void pnx4008_free_ll(u32 ll_dma, struct pnx4008_dma_ll * ll)
{
	struct pnx4008_dma_ll *ptr;
	u32 dma;

	while (ll) {
		dma = ll->next_dma;
		ptr = ll->next;
		pnx4008_free_ll_entry(ll, ll_dma);

		ll_dma = dma;
		ll = ptr;
	}
}