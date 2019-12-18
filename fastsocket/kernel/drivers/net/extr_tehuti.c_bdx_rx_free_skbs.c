#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int /*<<< orphan*/  pktsz; } ;
struct rxf_fifo {TYPE_1__ m; } ;
struct rxdb {scalar_t__ nelem; } ;
struct rx_map {int /*<<< orphan*/  skb; scalar_t__ dma; } ;
struct bdx_priv {int /*<<< orphan*/  pdev; struct rxdb* rxdb; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ENTER ; 
 int /*<<< orphan*/  PCI_DMA_FROMDEVICE ; 
 struct rx_map* bdx_rxdb_addr_elem (struct rxdb*,scalar_t__) ; 
 scalar_t__ bdx_rxdb_alloc_elem (struct rxdb*) ; 
 scalar_t__ bdx_rxdb_available (struct rxdb*) ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_unmap_single (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bdx_rx_free_skbs(struct bdx_priv *priv, struct rxf_fifo *f)
{
	struct rx_map *dm;
	struct rxdb *db = priv->rxdb;
	u16 i;

	ENTER;
	DBG("total=%d free=%d busy=%d\n", db->nelem, bdx_rxdb_available(db),
	    db->nelem - bdx_rxdb_available(db));
	while (bdx_rxdb_available(db) > 0) {
		i = bdx_rxdb_alloc_elem(db);
		dm = bdx_rxdb_addr_elem(db, i);
		dm->dma = 0;
	}
	for (i = 0; i < db->nelem; i++) {
		dm = bdx_rxdb_addr_elem(db, i);
		if (dm->dma) {
			pci_unmap_single(priv->pdev,
					 dm->dma, f->m.pktsz,
					 PCI_DMA_FROMDEVICE);
			dev_kfree_skb(dm->skb);
		}
	}
}