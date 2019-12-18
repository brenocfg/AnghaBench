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
struct skge_rx_desc {scalar_t__ control; } ;
struct skge_ring {struct skge_element* start; } ;
struct skge_port {struct skge_ring rx_ring; struct skge_hw* hw; } ;
struct skge_hw {int /*<<< orphan*/  pdev; } ;
struct skge_element {int /*<<< orphan*/ * skb; struct skge_rx_desc* desc; struct skge_element* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mapaddr ; 
 int /*<<< orphan*/  maplen ; 
 int /*<<< orphan*/  pci_unmap_addr (struct skge_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_len (struct skge_element*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void skge_rx_clean(struct skge_port *skge)
{
	struct skge_hw *hw = skge->hw;
	struct skge_ring *ring = &skge->rx_ring;
	struct skge_element *e;

	e = ring->start;
	do {
		struct skge_rx_desc *rd = e->desc;
		rd->control = 0;
		if (e->skb) {
			pci_unmap_single(hw->pdev,
					 pci_unmap_addr(e, mapaddr),
					 pci_unmap_len(e, maplen),
					 PCI_DMA_FROMDEVICE);
			dev_kfree_skb(e->skb);
			e->skb = NULL;
		}
	} while ((e = e->next) != ring->start);
}