#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct net_device {int dummy; } ;
struct au1k_private {int /*<<< orphan*/  timer; int /*<<< orphan*/ * irlap; } ;

/* Variables and functions */
 int /*<<< orphan*/  AU1000_IRDA_RX_INT ; 
 int /*<<< orphan*/  AU1000_IRDA_TX_INT ; 
 int /*<<< orphan*/  IR_CONFIG_1 ; 
 int /*<<< orphan*/  IR_CONFIG_2 ; 
 int /*<<< orphan*/  IR_INTERFACE_CONFIG ; 
 int /*<<< orphan*/  au_sync () ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  irlap_close (int /*<<< orphan*/ *) ; 
 struct au1k_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int read_ir_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int au1k_irda_stop(struct net_device *dev)
{
	struct au1k_private *aup = netdev_priv(dev);

	/* disable interrupts */
	writel(read_ir_reg(IR_CONFIG_2) & ~(1<<8), IR_CONFIG_2);
	writel(0, IR_CONFIG_1); 
	writel(0, IR_INTERFACE_CONFIG); /* disable clock */
	au_sync();

	if (aup->irlap) {
		irlap_close(aup->irlap);
		aup->irlap = NULL;
	}

	netif_stop_queue(dev);
	del_timer(&aup->timer);

	/* disable the interrupt */
	free_irq(AU1000_IRDA_TX_INT, dev);
	free_irq(AU1000_IRDA_RX_INT, dev);
	return 0;
}