#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct octeon_ethernet {scalar_t__ fau; int /*<<< orphan*/ * tx_free_list; int /*<<< orphan*/  (* poll ) (TYPE_2__*) ;} ;
typedef  int /*<<< orphan*/  int32_t ;
struct TYPE_7__ {TYPE_1__* netdev_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* ndo_get_stats ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int CVMX_PIP_NUM_INPUT_PORTS ; 
 int HZ ; 
 int /*<<< orphan*/  MAX_SKB_TO_FREE ; 
 TYPE_2__** cvm_oct_device ; 
 int /*<<< orphan*/  cvm_oct_free_tx_skbs (struct octeon_ethernet*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cvm_oct_poll_timer ; 
 int /*<<< orphan*/  cvmx_fau_atomic_add32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cvmx_fau_fetch_and_add32 (scalar_t__,int /*<<< orphan*/ ) ; 
 int cvmx_pko_get_num_queues (int) ; 
 int /*<<< orphan*/  down_trylock (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mdio_sem ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct octeon_ethernet* netdev_priv (TYPE_2__*) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cvm_do_timer(unsigned long arg)
{
	int32_t skb_to_free, undo;
	int queues_per_port;
	int qos;
	struct octeon_ethernet *priv;
	static int port;

	if (port >= CVMX_PIP_NUM_INPUT_PORTS) {
		/*
		 * All ports have been polled. Start the next
		 * iteration through the ports in one second.
		 */
		port = 0;
		mod_timer(&cvm_oct_poll_timer, jiffies + HZ);
		return;
	}
	if (!cvm_oct_device[port])
		goto out;

	priv = netdev_priv(cvm_oct_device[port]);
	if (priv->poll) {
		/* skip polling if we don't get the lock */
		if (!down_trylock(&mdio_sem)) {
			priv->poll(cvm_oct_device[port]);
			up(&mdio_sem);
		}
	}

	queues_per_port = cvmx_pko_get_num_queues(port);
	/* Drain any pending packets in the free list */
	for (qos = 0; qos < queues_per_port; qos++) {
		if (skb_queue_len(&priv->tx_free_list[qos]) == 0)
			continue;
		skb_to_free = cvmx_fau_fetch_and_add32(priv->fau + qos * 4,
						       MAX_SKB_TO_FREE);
		undo = skb_to_free > 0 ?
			MAX_SKB_TO_FREE : skb_to_free + MAX_SKB_TO_FREE;
		if (undo > 0)
			cvmx_fau_atomic_add32(priv->fau+qos*4, -undo);
		skb_to_free = -skb_to_free > MAX_SKB_TO_FREE ?
			MAX_SKB_TO_FREE : -skb_to_free;
		cvm_oct_free_tx_skbs(priv, skb_to_free, qos, 1);
	}
	cvm_oct_device[port]->netdev_ops->ndo_get_stats(cvm_oct_device[port]);

out:
	port++;
	/* Poll the next port in a 50th of a second.
	   This spreads the polling of ports out a little bit */
	mod_timer(&cvm_oct_poll_timer, jiffies + HZ / 50);
}