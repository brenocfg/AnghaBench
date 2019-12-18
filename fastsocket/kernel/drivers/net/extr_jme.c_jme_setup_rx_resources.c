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
struct jme_ring {unsigned long dmaalloc; int /*<<< orphan*/ * bufinf; scalar_t__ dma; int /*<<< orphan*/ * desc; scalar_t__ alloc; int /*<<< orphan*/  next_to_clean; scalar_t__ next_to_use; } ;
struct jme_buffer_info {int dummy; } ;
struct jme_adapter {int rx_ring_size; TYPE_1__* pdev; struct jme_ring* rxring; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ALIGN (unsigned long,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  RING_DESC_ALIGN ; 
 int /*<<< orphan*/  RX_RING_ALLOC_SIZE (int) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,unsigned long) ; 
 int /*<<< orphan*/  jme_free_rx_resources (struct jme_adapter*) ; 
 int jme_make_new_rx_buf (struct jme_adapter*,int) ; 
 int /*<<< orphan*/  jme_set_clean_rxdesc (struct jme_adapter*,int) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
jme_setup_rx_resources(struct jme_adapter *jme)
{
	int i;
	struct jme_ring *rxring = &(jme->rxring[0]);

	rxring->alloc = dma_alloc_coherent(&(jme->pdev->dev),
				   RX_RING_ALLOC_SIZE(jme->rx_ring_size),
				   &(rxring->dmaalloc),
				   GFP_ATOMIC);
	if (!rxring->alloc)
		goto err_set_null;

	/*
	 * 16 Bytes align
	 */
	rxring->desc		= (void *)ALIGN((unsigned long)(rxring->alloc),
						RING_DESC_ALIGN);
	rxring->dma		= ALIGN(rxring->dmaalloc, RING_DESC_ALIGN);
	rxring->next_to_use	= 0;
	atomic_set(&rxring->next_to_clean, 0);

	rxring->bufinf		= kmalloc(sizeof(struct jme_buffer_info) *
					jme->rx_ring_size, GFP_ATOMIC);
	if (unlikely(!(rxring->bufinf)))
		goto err_free_rxring;

	/*
	 * Initiallize Receive Descriptors
	 */
	memset(rxring->bufinf, 0,
		sizeof(struct jme_buffer_info) * jme->rx_ring_size);
	for (i = 0 ; i < jme->rx_ring_size ; ++i) {
		if (unlikely(jme_make_new_rx_buf(jme, i))) {
			jme_free_rx_resources(jme);
			return -ENOMEM;
		}

		jme_set_clean_rxdesc(jme, i);
	}

	return 0;

err_free_rxring:
	dma_free_coherent(&(jme->pdev->dev),
			  RX_RING_ALLOC_SIZE(jme->rx_ring_size),
			  rxring->alloc,
			  rxring->dmaalloc);
err_set_null:
	rxring->desc = NULL;
	rxring->dmaalloc = 0;
	rxring->dma = 0;
	rxring->bufinf = NULL;

	return -ENOMEM;
}