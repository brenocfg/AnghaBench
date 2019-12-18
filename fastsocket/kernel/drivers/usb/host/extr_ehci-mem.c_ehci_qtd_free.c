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
struct ehci_qtd {int /*<<< orphan*/  qtd_dma; } ;
struct ehci_hcd {int /*<<< orphan*/  qtd_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,struct ehci_qtd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ehci_qtd_free (struct ehci_hcd *ehci, struct ehci_qtd *qtd)
{
	dma_pool_free (ehci->qtd_pool, qtd, qtd->qtd_dma);
}