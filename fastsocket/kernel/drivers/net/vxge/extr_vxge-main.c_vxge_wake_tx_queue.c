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
struct vxge_fifo {int driver_id; scalar_t__ tx_steering_type; scalar_t__ queue_state; struct net_device* ndev; } ;
struct sk_buff {int dummy; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ TX_MULTIQ_STEERING ; 
 scalar_t__ VPATH_QUEUE_START ; 
 scalar_t__ VPATH_QUEUE_STOP ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int) ; 
 scalar_t__ netif_tx_queue_stopped (struct netdev_queue*) ; 
 int /*<<< orphan*/  netif_tx_wake_queue (struct netdev_queue*) ; 

void vxge_wake_tx_queue(struct vxge_fifo *fifo, struct sk_buff *skb)
{
	struct net_device *dev = fifo->ndev;

	int vpath_no = fifo->driver_id;
	struct netdev_queue *txq = NULL;
	if (fifo->tx_steering_type == TX_MULTIQ_STEERING) {
		txq = netdev_get_tx_queue(dev, vpath_no);
		if (netif_tx_queue_stopped(txq))
			netif_tx_wake_queue(txq);
	} else {
		txq = netdev_get_tx_queue(dev, 0);
		if (fifo->queue_state == VPATH_QUEUE_STOP)
			if (netif_tx_queue_stopped(txq)) {
				fifo->queue_state = VPATH_QUEUE_START;
				netif_tx_wake_queue(txq);
			}
	}
}