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
struct il_rx_queue {int /*<<< orphan*/  bd_dma; void* bd; scalar_t__ need_update; scalar_t__ free_count; scalar_t__ write_actual; scalar_t__ write; scalar_t__ read; int /*<<< orphan*/  rx_used; TYPE_1__* pool; void* rb_stts; int /*<<< orphan*/  rb_stts_dma; int /*<<< orphan*/  rx_free; int /*<<< orphan*/  lock; } ;
struct il_rb_status {int dummy; } ;
struct il_priv {TYPE_2__* pci_dev; struct il_rx_queue rxq; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int RX_FREE_BUFFERS ; 
 int RX_QUEUE_SIZE ; 
 void* dma_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (struct device*,int,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int
il_rx_queue_alloc(struct il_priv *il)
{
	struct il_rx_queue *rxq = &il->rxq;
	struct device *dev = &il->pci_dev->dev;
	int i;

	spin_lock_init(&rxq->lock);
	INIT_LIST_HEAD(&rxq->rx_free);
	INIT_LIST_HEAD(&rxq->rx_used);

	/* Alloc the circular buffer of Read Buffer Descriptors (RBDs) */
	rxq->bd = dma_alloc_coherent(dev, 4 * RX_QUEUE_SIZE, &rxq->bd_dma,
				     GFP_KERNEL);
	if (!rxq->bd)
		goto err_bd;

	rxq->rb_stts = dma_alloc_coherent(dev, sizeof(struct il_rb_status),
					  &rxq->rb_stts_dma, GFP_KERNEL);
	if (!rxq->rb_stts)
		goto err_rb;

	/* Fill the rx_used queue with _all_ of the Rx buffers */
	for (i = 0; i < RX_FREE_BUFFERS + RX_QUEUE_SIZE; i++)
		list_add_tail(&rxq->pool[i].list, &rxq->rx_used);

	/* Set us so that we have processed and used all buffers, but have
	 * not restocked the Rx queue with fresh buffers */
	rxq->read = rxq->write = 0;
	rxq->write_actual = 0;
	rxq->free_count = 0;
	rxq->need_update = 0;
	return 0;

err_rb:
	dma_free_coherent(&il->pci_dev->dev, 4 * RX_QUEUE_SIZE, rxq->bd,
			  rxq->bd_dma);
err_bd:
	return -ENOMEM;
}