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
struct sk_buff {int dummy; } ;
struct efx_tx_queue {int /*<<< orphan*/  queue; struct efx_nic* efx; } ;
struct efx_nic {int /*<<< orphan*/  net_dev; struct efx_loopback_state* loopback_selftest; } ;
struct efx_loopback_state {int packet_count; int /*<<< orphan*/  payload; struct sk_buff** skbs; } ;
struct TYPE_2__ {int /*<<< orphan*/  saddr; } ;
struct efx_loopback_payload {TYPE_1__ ip; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int ENOMEM ; 
 int EPIPE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INADDR_LOOPBACK ; 
 int /*<<< orphan*/  LOOPBACK_MODE (struct efx_nic*) ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  efx_enqueue_skb (struct efx_tx_queue*,struct sk_buff*) ; 
 int /*<<< orphan*/  htonl (int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (struct efx_loopback_payload*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_lock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_unlock_bh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_get (struct sk_buff*) ; 
 scalar_t__ skb_put (struct sk_buff*,int) ; 
 int /*<<< orphan*/  smp_wmb () ; 

__attribute__((used)) static int efx_begin_loopback(struct efx_tx_queue *tx_queue)
{
	struct efx_nic *efx = tx_queue->efx;
	struct efx_loopback_state *state = efx->loopback_selftest;
	struct efx_loopback_payload *payload;
	struct sk_buff *skb;
	int i;
	netdev_tx_t rc;

	/* Transmit N copies of buffer */
	for (i = 0; i < state->packet_count; i++) {
		/* Allocate an skb, holding an extra reference for
		 * transmit completion counting */
		skb = alloc_skb(sizeof(state->payload), GFP_KERNEL);
		if (!skb)
			return -ENOMEM;
		state->skbs[i] = skb;
		skb_get(skb);

		/* Copy the payload in, incrementing the source address to
		 * exercise the rss vectors */
		payload = ((struct efx_loopback_payload *)
			   skb_put(skb, sizeof(state->payload)));
		memcpy(payload, &state->payload, sizeof(state->payload));
		payload->ip.saddr = htonl(INADDR_LOOPBACK | (i << 2));

		/* Ensure everything we've written is visible to the
		 * interrupt handler. */
		smp_wmb();

		netif_tx_lock_bh(efx->net_dev);
		rc = efx_enqueue_skb(tx_queue, skb);
		netif_tx_unlock_bh(efx->net_dev);

		if (rc != NETDEV_TX_OK) {
			netif_err(efx, drv, efx->net_dev,
				  "TX queue %d could not transmit packet %d of "
				  "%d in %s loopback test\n", tx_queue->queue,
				  i + 1, state->packet_count,
				  LOOPBACK_MODE(efx));

			/* Defer cleaning up the other skbs for the caller */
			kfree_skb(skb);
			return -EPIPE;
		}
	}

	return 0;
}