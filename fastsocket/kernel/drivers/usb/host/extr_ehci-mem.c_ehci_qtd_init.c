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
struct ehci_qtd {int /*<<< orphan*/  qtd_list; void* hw_alt_next; void* hw_next; int /*<<< orphan*/  hw_token; int /*<<< orphan*/  qtd_dma; } ;
struct ehci_hcd {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 void* EHCI_LIST_END (struct ehci_hcd*) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QTD_STS_HALT ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ehci_qtd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void ehci_qtd_init(struct ehci_hcd *ehci, struct ehci_qtd *qtd,
				  dma_addr_t dma)
{
	memset (qtd, 0, sizeof *qtd);
	qtd->qtd_dma = dma;
	qtd->hw_token = cpu_to_le32 (QTD_STS_HALT);
	qtd->hw_next = EHCI_LIST_END(ehci);
	qtd->hw_alt_next = EHCI_LIST_END(ehci);
	INIT_LIST_HEAD (&qtd->qtd_list);
}