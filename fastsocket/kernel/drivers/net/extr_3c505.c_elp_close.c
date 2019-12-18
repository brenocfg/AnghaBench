#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct net_device {int /*<<< orphan*/  dma; int /*<<< orphan*/  irq; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {scalar_t__ dma_buffer; } ;
typedef  TYPE_1__ elp_device ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BUFFER_SIZE ; 
 int elp_debug ; 
 int /*<<< orphan*/  elp_get_stats (struct net_device*) ; 
 int /*<<< orphan*/  free_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_order (int /*<<< orphan*/ ) ; 
 TYPE_1__* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  outb_control (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int elp_close(struct net_device *dev)
{
	elp_device *adapter = netdev_priv(dev);

	if (elp_debug >= 3)
		pr_debug("%s: request to close device\n", dev->name);

	netif_stop_queue(dev);

	/* Someone may request the device statistic information even when
	 * the interface is closed. The following will update the statistics
	 * structure in the driver, so we'll be able to give current statistics.
	 */
	(void) elp_get_stats(dev);

	/*
	 * disable interrupts on the board
	 */
	outb_control(0, dev);

	/*
	 * release the IRQ
	 */
	free_irq(dev->irq, dev);

	free_dma(dev->dma);
	free_pages((unsigned long) adapter->dma_buffer, get_order(DMA_BUFFER_SIZE));

	return 0;
}