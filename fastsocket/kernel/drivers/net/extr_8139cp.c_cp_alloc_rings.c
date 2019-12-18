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
struct cp_private {int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/  ring_dma; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_RING_BYTES ; 
 size_t CP_RX_RING_SIZE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cp_init_rings (struct cp_private*) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cp_alloc_rings (struct cp_private *cp)
{
	void *mem;

	mem = dma_alloc_coherent(&cp->pdev->dev, CP_RING_BYTES,
				 &cp->ring_dma, GFP_KERNEL);
	if (!mem)
		return -ENOMEM;

	cp->rx_ring = mem;
	cp->tx_ring = &cp->rx_ring[CP_RX_RING_SIZE];

	return cp_init_rings(cp);
}