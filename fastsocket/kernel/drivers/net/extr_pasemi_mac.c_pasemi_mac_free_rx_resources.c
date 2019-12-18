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
typedef  int /*<<< orphan*/  u64 ;
struct pasemi_mac {int /*<<< orphan*/ * rx; TYPE_1__* dma_pdev; } ;
struct TYPE_4__ {int /*<<< orphan*/  chan; int /*<<< orphan*/  ring_info; int /*<<< orphan*/  buf_dma; int /*<<< orphan*/  buffers; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int RX_RING_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pasemi_dma_free_chan (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pasemi_mac_free_rx_buffers (struct pasemi_mac*) ; 
 TYPE_2__* rx_ring (struct pasemi_mac*) ; 

__attribute__((used)) static void pasemi_mac_free_rx_resources(struct pasemi_mac *mac)
{
	pasemi_mac_free_rx_buffers(mac);

	dma_free_coherent(&mac->dma_pdev->dev, RX_RING_SIZE * sizeof(u64),
			  rx_ring(mac)->buffers, rx_ring(mac)->buf_dma);

	kfree(rx_ring(mac)->ring_info);
	pasemi_dma_free_chan(&rx_ring(mac)->chan);
	mac->rx = NULL;
}