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
struct TYPE_2__ {int /*<<< orphan*/  skb; } ;
struct stir_cb {int /*<<< orphan*/ * irlap; TYPE_1__ rx_buff; int /*<<< orphan*/  rx_urb; int /*<<< orphan*/  io_buf; int /*<<< orphan*/  fifo_status; int /*<<< orphan*/  thread; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  irlap_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kthread_stop (int /*<<< orphan*/ ) ; 
 struct stir_cb* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_kill_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int stir_net_close(struct net_device *netdev)
{
	struct stir_cb *stir = netdev_priv(netdev);

	/* Stop transmit processing */
	netif_stop_queue(netdev);

	/* Kill transmit thread */
	kthread_stop(stir->thread);
	kfree(stir->fifo_status);

	/* Mop up receive urb's */
	usb_kill_urb(stir->rx_urb);
	
	kfree(stir->io_buf);
	usb_free_urb(stir->rx_urb);
	kfree_skb(stir->rx_buff.skb);

	/* Stop and remove instance of IrLAP */
	if (stir->irlap)
		irlap_close(stir->irlap);

	stir->irlap = NULL;

	return 0;
}