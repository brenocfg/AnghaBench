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
struct pci_dev {int dummy; } ;
struct cas {int /*<<< orphan*/ ** tx_tiny_bufs; int /*<<< orphan*/ * tx_tiny_dvma; struct pci_dev* pdev; } ;

/* Variables and functions */
 int N_TX_RINGS ; 
 int /*<<< orphan*/  TX_TINY_BUF_BLOCK ; 
 int /*<<< orphan*/  pci_free_consistent (struct pci_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cas_tx_tiny_free(struct cas *cp)
{
	struct pci_dev *pdev = cp->pdev;
	int i;

	for (i = 0; i < N_TX_RINGS; i++) {
		if (!cp->tx_tiny_bufs[i])
			continue;

		pci_free_consistent(pdev, TX_TINY_BUF_BLOCK,
				    cp->tx_tiny_bufs[i],
				    cp->tx_tiny_dvma[i]);
		cp->tx_tiny_bufs[i] = NULL;
	}
}