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
struct jme_ring {unsigned long dmaalloc; int /*<<< orphan*/ * bufinf; scalar_t__ dma; int /*<<< orphan*/ * desc; int /*<<< orphan*/ * alloc; int /*<<< orphan*/  nr_free; int /*<<< orphan*/  next_to_clean; scalar_t__ next_to_use; } ;
struct jme_buffer_info {int dummy; } ;
struct jme_adapter {int tx_ring_size; TYPE_1__* pdev; struct jme_ring* txring; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ALIGN (unsigned long,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  RING_DESC_ALIGN ; 
 int TX_RING_ALLOC_SIZE (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * dma_alloc_coherent (int /*<<< orphan*/ *,int,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
jme_setup_tx_resources(struct jme_adapter *jme)
{
	struct jme_ring *txring = &(jme->txring[0]);

	txring->alloc = dma_alloc_coherent(&(jme->pdev->dev),
				   TX_RING_ALLOC_SIZE(jme->tx_ring_size),
				   &(txring->dmaalloc),
				   GFP_ATOMIC);

	if (!txring->alloc)
		goto err_set_null;

	/*
	 * 16 Bytes align
	 */
	txring->desc		= (void *)ALIGN((unsigned long)(txring->alloc),
						RING_DESC_ALIGN);
	txring->dma		= ALIGN(txring->dmaalloc, RING_DESC_ALIGN);
	txring->next_to_use	= 0;
	atomic_set(&txring->next_to_clean, 0);
	atomic_set(&txring->nr_free, jme->tx_ring_size);

	txring->bufinf		= kmalloc(sizeof(struct jme_buffer_info) *
					jme->tx_ring_size, GFP_ATOMIC);
	if (unlikely(!(txring->bufinf)))
		goto err_free_txring;

	/*
	 * Initialize Transmit Descriptors
	 */
	memset(txring->alloc, 0, TX_RING_ALLOC_SIZE(jme->tx_ring_size));
	memset(txring->bufinf, 0,
		sizeof(struct jme_buffer_info) * jme->tx_ring_size);

	return 0;

err_free_txring:
	dma_free_coherent(&(jme->pdev->dev),
			  TX_RING_ALLOC_SIZE(jme->tx_ring_size),
			  txring->alloc,
			  txring->dmaalloc);

err_set_null:
	txring->desc = NULL;
	txring->dmaalloc = 0;
	txring->dma = 0;
	txring->bufinf = NULL;

	return -ENOMEM;
}