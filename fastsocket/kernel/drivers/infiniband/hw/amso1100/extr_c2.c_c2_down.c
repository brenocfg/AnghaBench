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
struct net_device {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int /*<<< orphan*/  start; } ;
struct TYPE_3__ {int /*<<< orphan*/  start; } ;
struct c2_port {int /*<<< orphan*/  dma; int /*<<< orphan*/  mem; int /*<<< orphan*/  mem_size; TYPE_2__ tx_ring; TYPE_1__ rx_ring; struct c2_dev* c2dev; } ;
struct c2_dev {int /*<<< orphan*/  pcidev; scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ C2_IDIS ; 
 scalar_t__ C2_NIMR0 ; 
 int /*<<< orphan*/  c2_reset (struct c2_port*) ; 
 int /*<<< orphan*/  c2_rx_clean (struct c2_port*) ; 
 int /*<<< orphan*/  c2_tx_clean (struct c2_port*) ; 
 int /*<<< orphan*/  c2_tx_interrupt (struct net_device*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct c2_port* netdev_priv (struct net_device*) ; 
 scalar_t__ netif_msg_ifdown (struct c2_port*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  pci_free_consistent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int c2_down(struct net_device *netdev)
{
	struct c2_port *c2_port = netdev_priv(netdev);
	struct c2_dev *c2dev = c2_port->c2dev;

	if (netif_msg_ifdown(c2_port))
		pr_debug("%s: disabling interface\n",
			netdev->name);

	/* Wait for all the queued packets to get sent */
	c2_tx_interrupt(netdev);

	/* Disable network packets */
	netif_stop_queue(netdev);

	/* Disable IRQs by clearing the interrupt mask */
	writel(1, c2dev->regs + C2_IDIS);
	writel(0, c2dev->regs + C2_NIMR0);

	/* missing: Stop transmitter */

	/* missing: Stop receiver */

	/* Reset the adapter, ensures the driver is in sync with the RXP */
	c2_reset(c2_port);

	/* missing: Turn off LEDs here */

	/* Free all buffers in the host descriptor rings */
	c2_tx_clean(c2_port);
	c2_rx_clean(c2_port);

	/* Free the host descriptor rings */
	kfree(c2_port->rx_ring.start);
	kfree(c2_port->tx_ring.start);
	pci_free_consistent(c2dev->pcidev, c2_port->mem_size, c2_port->mem,
			    c2_port->dma);

	return 0;
}