#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tx_queue {scalar_t__ tx_used_desc; scalar_t__ tx_curr_desc; scalar_t__ index; scalar_t__ tx_desc_area_size; int /*<<< orphan*/  tx_desc_dma; int /*<<< orphan*/  tx_desc_area; int /*<<< orphan*/  tx_ring_size; } ;
struct mv643xx_eth_private {scalar_t__ tx_desc_sram_size; TYPE_2__* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  parent; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txq_disable (struct tx_queue*) ; 
 int /*<<< orphan*/  txq_reclaim (struct tx_queue*,int /*<<< orphan*/ ,int) ; 
 struct mv643xx_eth_private* txq_to_mp (struct tx_queue*) ; 

__attribute__((used)) static void txq_deinit(struct tx_queue *txq)
{
	struct mv643xx_eth_private *mp = txq_to_mp(txq);

	txq_disable(txq);
	txq_reclaim(txq, txq->tx_ring_size, 1);

	BUG_ON(txq->tx_used_desc != txq->tx_curr_desc);

	if (txq->index == 0 &&
	    txq->tx_desc_area_size <= mp->tx_desc_sram_size)
		iounmap(txq->tx_desc_area);
	else
		dma_free_coherent(mp->dev->dev.parent, txq->tx_desc_area_size,
				  txq->tx_desc_area, txq->tx_desc_dma);
}