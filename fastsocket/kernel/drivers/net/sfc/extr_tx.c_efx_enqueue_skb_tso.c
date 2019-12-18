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
struct tso_state {scalar_t__ header_len; scalar_t__ in_len; scalar_t__ packet_space; int dma_flags; scalar_t__ unmap_len; int /*<<< orphan*/  unmap_addr; int /*<<< orphan*/  protocol; } ;
struct sk_buff {scalar_t__ len; } ;
struct efx_tx_queue {scalar_t__ write_count; scalar_t__ insert_count; int /*<<< orphan*/  tso_bursts; struct efx_nic* efx; } ;
struct efx_nic {TYPE_1__* pci_dev; int /*<<< orphan*/  net_dev; } ;
struct TYPE_4__ {scalar_t__ gso_segs; scalar_t__ gso_size; int nr_frags; scalar_t__ frags; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  EFX_BUG_ON_PARANOID (int) ; 
 scalar_t__ EFX_TSO_MAX_SEGS ; 
 int EFX_TX_BUF_MAP_SINGLE ; 
 int NETDEV_TX_OK ; 
 scalar_t__ __pskb_trim (struct sk_buff*,scalar_t__) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_unmap_page (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_enqueue_unwind (struct efx_tx_queue*) ; 
 int /*<<< orphan*/  efx_nic_push_buffers (struct efx_tx_queue*) ; 
 int /*<<< orphan*/  efx_tso_check_protocol (struct sk_buff*) ; 
 int /*<<< orphan*/  efx_tx_maybe_stop_queue (struct efx_tx_queue*) ; 
 int /*<<< orphan*/  netif_err (struct efx_nic*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  tso_fill_packet_with_fragment (struct efx_tx_queue*,struct sk_buff*,struct tso_state*) ; 
 int tso_get_fragment (struct tso_state*,struct efx_nic*,scalar_t__) ; 
 int tso_get_head_fragment (struct tso_state*,struct efx_nic*,struct sk_buff*) ; 
 int /*<<< orphan*/  tso_start (struct tso_state*,struct sk_buff*) ; 
 scalar_t__ tso_start_new_packet (struct efx_tx_queue*,struct sk_buff*,struct tso_state*) ; 
 int /*<<< orphan*/  tx_err ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int efx_enqueue_skb_tso(struct efx_tx_queue *tx_queue,
			       struct sk_buff *skb)
{
	struct efx_nic *efx = tx_queue->efx;
	int frag_i, rc;
	struct tso_state state;

	/* Since the stack does not limit the number of segments per
	 * skb, we must do so.  Otherwise an attacker may be able to
	 * make the TCP produce skbs that will never fit in our TX
	 * queue, causing repeated resets.
	 */
	if (unlikely(skb_shinfo(skb)->gso_segs > EFX_TSO_MAX_SEGS)) {
		unsigned int excess =
			(skb_shinfo(skb)->gso_segs - EFX_TSO_MAX_SEGS) *
			skb_shinfo(skb)->gso_size;
		if (__pskb_trim(skb, skb->len - excess)) {
			dev_kfree_skb_any(skb);
			return NETDEV_TX_OK;
		}
	}

	/* Find the packet protocol and sanity-check it */
	state.protocol = efx_tso_check_protocol(skb);

	EFX_BUG_ON_PARANOID(tx_queue->write_count != tx_queue->insert_count);

	tso_start(&state, skb);

	/* Assume that skb header area contains exactly the headers, and
	 * all payload is in the frag list.
	 */
	if (skb_headlen(skb) == state.header_len) {
		/* Grab the first payload fragment. */
		EFX_BUG_ON_PARANOID(skb_shinfo(skb)->nr_frags < 1);
		frag_i = 0;
		rc = tso_get_fragment(&state, efx,
				      skb_shinfo(skb)->frags + frag_i);
		if (rc)
			goto mem_err;
	} else {
		rc = tso_get_head_fragment(&state, efx, skb);
		if (rc)
			goto mem_err;
		frag_i = -1;
	}

	if (tso_start_new_packet(tx_queue, skb, &state) < 0)
		goto mem_err;

	while (1) {
		tso_fill_packet_with_fragment(tx_queue, skb, &state);

		/* Move onto the next fragment? */
		if (state.in_len == 0) {
			if (++frag_i >= skb_shinfo(skb)->nr_frags)
				/* End of payload reached. */
				break;
			rc = tso_get_fragment(&state, efx,
					      skb_shinfo(skb)->frags + frag_i);
			if (rc)
				goto mem_err;
		}

		/* Start at new packet? */
		if (state.packet_space == 0 &&
		    tso_start_new_packet(tx_queue, skb, &state) < 0)
			goto mem_err;
	}

	/* Pass off to hardware */
	efx_nic_push_buffers(tx_queue);

	efx_tx_maybe_stop_queue(tx_queue);

	tx_queue->tso_bursts++;
	return NETDEV_TX_OK;

 mem_err:
	netif_err(efx, tx_err, efx->net_dev,
		  "Out of memory for TSO headers, or DMA mapping error\n");
	dev_kfree_skb_any(skb);

	/* Free the DMA mapping we were in the process of writing out */
	if (state.unmap_len) {
		if (state.dma_flags & EFX_TX_BUF_MAP_SINGLE)
			dma_unmap_single(&efx->pci_dev->dev, state.unmap_addr,
					 state.unmap_len, DMA_TO_DEVICE);
		else
			dma_unmap_page(&efx->pci_dev->dev, state.unmap_addr,
				       state.unmap_len, DMA_TO_DEVICE);
	}

	efx_enqueue_unwind(tx_queue);
	return NETDEV_TX_OK;
}