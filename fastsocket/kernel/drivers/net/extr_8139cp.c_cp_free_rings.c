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
struct cp_private {int /*<<< orphan*/ * tx_ring; int /*<<< orphan*/ * rx_ring; int /*<<< orphan*/  ring_dma; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_RING_BYTES ; 
 int /*<<< orphan*/  cp_clean_rings (struct cp_private*) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cp_free_rings (struct cp_private *cp)
{
	cp_clean_rings(cp);
	dma_free_coherent(&cp->pdev->dev, CP_RING_BYTES, cp->rx_ring,
			  cp->ring_dma);
	cp->rx_ring = NULL;
	cp->tx_ring = NULL;
}