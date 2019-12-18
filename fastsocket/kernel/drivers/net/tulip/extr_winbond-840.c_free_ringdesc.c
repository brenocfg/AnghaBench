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
struct w840_tx_desc {int dummy; } ;
struct w840_rx_desc {int dummy; } ;
struct netdev_private {int /*<<< orphan*/  ring_dma_addr; int /*<<< orphan*/  rx_ring; int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int RX_RING_SIZE ; 
 int TX_RING_SIZE ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_ringdesc(struct netdev_private *np)
{
	pci_free_consistent(np->pci_dev,
			sizeof(struct w840_rx_desc)*RX_RING_SIZE +
			sizeof(struct w840_tx_desc)*TX_RING_SIZE,
			np->rx_ring, np->ring_dma_addr);

}