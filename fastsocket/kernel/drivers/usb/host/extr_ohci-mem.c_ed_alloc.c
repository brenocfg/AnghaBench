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
struct ohci_hcd {int /*<<< orphan*/  ed_cache; } ;
struct ed {int /*<<< orphan*/  dma; int /*<<< orphan*/  td_list; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct ed* dma_pool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct ed*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct ed *
ed_alloc (struct ohci_hcd *hc, gfp_t mem_flags)
{
	dma_addr_t	dma;
	struct ed	*ed;

	ed = dma_pool_alloc (hc->ed_cache, mem_flags, &dma);
	if (ed) {
		memset (ed, 0, sizeof (*ed));
		INIT_LIST_HEAD (&ed->td_list);
		ed->dma = dma;
	}
	return ed;
}