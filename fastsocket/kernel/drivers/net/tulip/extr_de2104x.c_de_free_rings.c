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
struct de_private {int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/  ring_dma; int /*<<< orphan*/  pdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DE_RING_BYTES ; 
 int /*<<< orphan*/  de_clean_rings (struct de_private*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void de_free_rings (struct de_private *de)
{
	de_clean_rings(de);
	pci_free_consistent(de->pdev, DE_RING_BYTES, de->rx_ring, de->ring_dma);
	de->rx_ring = NULL;
	de->tx_ring = NULL;
}