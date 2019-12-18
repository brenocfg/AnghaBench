#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct skb_frag_struct {int dummy; } ;
struct sk_buff {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct net_device {int dummy; } ;
struct bnad_tx_unmap {scalar_t__ nvecs; int /*<<< orphan*/ * vectors; struct sk_buff* skb; } ;
struct bnad {TYPE_5__* pcidev; TYPE_1__* tx_info; } ;
struct TYPE_10__ {int /*<<< orphan*/  opcode; } ;
struct TYPE_9__ {scalar_t__ num_vectors; scalar_t__ reserved; } ;
struct TYPE_11__ {TYPE_3__ wi_ext; TYPE_2__ wi; } ;
struct bna_txq_entry {TYPE_6__* vector; TYPE_4__ hdr; } ;
struct bna_tcb {scalar_t__ q_depth; scalar_t__ producer_index; scalar_t__* hw_consumer_index; scalar_t__ consumer_index; int /*<<< orphan*/  flags; scalar_t__ sw_q; int /*<<< orphan*/  i_dbell; struct bnad_tx_unmap* unmap_q; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_14__ {scalar_t__ nr_frags; struct skb_frag_struct* frags; } ;
struct TYPE_13__ {void* length; int /*<<< orphan*/  host_addr; } ;
struct TYPE_12__ {int /*<<< orphan*/  dev; } ;
struct TYPE_8__ {struct bna_tcb** tcb; } ;

/* Variables and functions */
 scalar_t__ BFI_TX_MAX_DATA_PER_VECTOR ; 
 scalar_t__ BFI_TX_MAX_VECTORS_PER_PKT ; 
 scalar_t__ BFI_TX_MAX_VECTORS_PER_WI ; 
 int /*<<< orphan*/  BNAD_TXQ_FREE_SENT ; 
 int /*<<< orphan*/  BNAD_TXQ_TX_STARTED ; 
 int /*<<< orphan*/  BNAD_UPDATE_CTR (struct bnad*,int /*<<< orphan*/ ) ; 
 scalar_t__ BNA_QE_FREE_CNT (struct bna_tcb*,scalar_t__) ; 
 int /*<<< orphan*/  BNA_QE_INDX_INC (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  BNA_SET_DMA_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BNA_TXQ_WI_EXTENSION ; 
 scalar_t__ BNA_TXQ_WI_NEEDED (scalar_t__) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 scalar_t__ ETH_HLEN ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  __constant_htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bna_ib_ack (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bna_txq_prod_indx_doorbell (struct bna_tcb*) ; 
 int /*<<< orphan*/  bnad_tx_buff_unmap (struct bnad*,struct bnad_tx_unmap*,scalar_t__,scalar_t__) ; 
 scalar_t__ bnad_txcmpl_process (struct bnad*,struct bna_tcb*) ; 
 scalar_t__ bnad_txq_wi_prepare (struct bnad*,struct bna_tcb*,struct sk_buff*,struct bna_txq_entry*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_addr_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* htons (scalar_t__) ; 
 scalar_t__ likely (int) ; 
 struct bnad* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_queue_stop ; 
 int /*<<< orphan*/  netif_queue_wakeup ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  skb_frag_dma_map (int /*<<< orphan*/ *,struct skb_frag_struct const*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_frag_size (struct skb_frag_struct const*) ; 
 scalar_t__ skb_headlen (struct sk_buff*) ; 
 TYPE_7__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_mb__before_clear_bit () ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tx_skb_frag_zero ; 
 int /*<<< orphan*/  tx_skb_headlen_zero ; 
 int /*<<< orphan*/  tx_skb_len_mismatch ; 
 int /*<<< orphan*/  tx_skb_max_vectors ; 
 int /*<<< orphan*/  tx_skb_stopping ; 
 int /*<<< orphan*/  tx_skb_too_short ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static netdev_tx_t
bnad_start_xmit(struct sk_buff *skb, struct net_device *netdev)
{
	struct bnad *bnad = netdev_priv(netdev);
	u32 txq_id = 0;
	struct bna_tcb *tcb = NULL;
	struct bnad_tx_unmap *unmap_q, *unmap, *head_unmap;
	u32		prod, q_depth, vect_id;
	u32		wis, vectors, len;
	int		i;
	dma_addr_t		dma_addr;
	struct bna_txq_entry *txqent;

	len = skb_headlen(skb);

	/* Sanity checks for the skb */

	if (unlikely(skb->len <= ETH_HLEN)) {
		dev_kfree_skb(skb);
		BNAD_UPDATE_CTR(bnad, tx_skb_too_short);
		return NETDEV_TX_OK;
	}
	if (unlikely(len > BFI_TX_MAX_DATA_PER_VECTOR)) {
		dev_kfree_skb(skb);
		BNAD_UPDATE_CTR(bnad, tx_skb_headlen_zero);
		return NETDEV_TX_OK;
	}
	if (unlikely(len == 0)) {
		dev_kfree_skb(skb);
		BNAD_UPDATE_CTR(bnad, tx_skb_headlen_zero);
		return NETDEV_TX_OK;
	}

	tcb = bnad->tx_info[0].tcb[txq_id];
	q_depth = tcb->q_depth;
	prod = tcb->producer_index;

	unmap_q = tcb->unmap_q;

	/*
	 * Takes care of the Tx that is scheduled between clearing the flag
	 * and the netif_tx_stop_all_queues() call.
	 */
	if (unlikely(!test_bit(BNAD_TXQ_TX_STARTED, &tcb->flags))) {
		dev_kfree_skb(skb);
		BNAD_UPDATE_CTR(bnad, tx_skb_stopping);
		return NETDEV_TX_OK;
	}

	vectors = 1 + skb_shinfo(skb)->nr_frags;
	wis = BNA_TXQ_WI_NEEDED(vectors);	/* 4 vectors per work item */

	if (unlikely(vectors > BFI_TX_MAX_VECTORS_PER_PKT)) {
		dev_kfree_skb(skb);
		BNAD_UPDATE_CTR(bnad, tx_skb_max_vectors);
		return NETDEV_TX_OK;
	}

	/* Check for available TxQ resources */
	if (unlikely(wis > BNA_QE_FREE_CNT(tcb, q_depth))) {
		if ((*tcb->hw_consumer_index != tcb->consumer_index) &&
		    !test_and_set_bit(BNAD_TXQ_FREE_SENT, &tcb->flags)) {
			u32 sent;
			sent = bnad_txcmpl_process(bnad, tcb);
			if (likely(test_bit(BNAD_TXQ_TX_STARTED, &tcb->flags)))
				bna_ib_ack(tcb->i_dbell, sent);
			smp_mb__before_clear_bit();
			clear_bit(BNAD_TXQ_FREE_SENT, &tcb->flags);
		} else {
			netif_stop_queue(netdev);
			BNAD_UPDATE_CTR(bnad, netif_queue_stop);
		}

		smp_mb();
		/*
		 * Check again to deal with race condition between
		 * netif_stop_queue here, and netif_wake_queue in
		 * interrupt handler which is not inside netif tx lock.
		 */
		if (likely(wis > BNA_QE_FREE_CNT(tcb, q_depth))) {
			BNAD_UPDATE_CTR(bnad, netif_queue_stop);
			return NETDEV_TX_BUSY;
		} else {
			netif_wake_queue(netdev);
			BNAD_UPDATE_CTR(bnad, netif_queue_wakeup);
		}
	}

	txqent = &((struct bna_txq_entry *)tcb->sw_q)[prod];
	head_unmap = &unmap_q[prod];

	/* Program the opcode, flags, frame_len, num_vectors in WI */
	if (bnad_txq_wi_prepare(bnad, tcb, skb, txqent)) {
		dev_kfree_skb(skb);
		return NETDEV_TX_OK;
	}
	txqent->hdr.wi.reserved = 0;
	txqent->hdr.wi.num_vectors = vectors;

	head_unmap->skb = skb;
	head_unmap->nvecs = 0;

	/* Program the vectors */
	unmap = head_unmap;
	dma_addr = dma_map_single(&bnad->pcidev->dev, skb->data,
				  len, DMA_TO_DEVICE);
	BNA_SET_DMA_ADDR(dma_addr, &txqent->vector[0].host_addr);
	txqent->vector[0].length = htons(len);
	dma_unmap_addr_set(&unmap->vectors[0], dma_addr, dma_addr);
	head_unmap->nvecs++;

	for (i = 0, vect_id = 0; i < vectors - 1; i++) {
		const struct skb_frag_struct *frag = &skb_shinfo(skb)->frags[i];
		u16		size = skb_frag_size(frag);

		if (unlikely(size == 0)) {
			/* Undo the changes starting at tcb->producer_index */
			bnad_tx_buff_unmap(bnad, unmap_q, q_depth,
				tcb->producer_index);
			dev_kfree_skb(skb);
			BNAD_UPDATE_CTR(bnad, tx_skb_frag_zero);
			return NETDEV_TX_OK;
		}

		len += size;

		vect_id++;
		if (vect_id == BFI_TX_MAX_VECTORS_PER_WI) {
			vect_id = 0;
			BNA_QE_INDX_INC(prod, q_depth);
			txqent = &((struct bna_txq_entry *)tcb->sw_q)[prod];
			txqent->hdr.wi_ext.opcode =
				__constant_htons(BNA_TXQ_WI_EXTENSION);
			unmap = &unmap_q[prod];
		}

		dma_addr = skb_frag_dma_map(&bnad->pcidev->dev, frag,
					    0, size, DMA_TO_DEVICE);
		BNA_SET_DMA_ADDR(dma_addr, &txqent->vector[vect_id].host_addr);
		txqent->vector[vect_id].length = htons(size);
		dma_unmap_addr_set(&unmap->vectors[vect_id], dma_addr,
						dma_addr);
		head_unmap->nvecs++;
	}

	if (unlikely(len != skb->len)) {
		/* Undo the changes starting at tcb->producer_index */
		bnad_tx_buff_unmap(bnad, unmap_q, q_depth, tcb->producer_index);
		dev_kfree_skb(skb);
		BNAD_UPDATE_CTR(bnad, tx_skb_len_mismatch);
		return NETDEV_TX_OK;
	}

	BNA_QE_INDX_INC(prod, q_depth);
	tcb->producer_index = prod;

	smp_mb();

	if (unlikely(!test_bit(BNAD_TXQ_TX_STARTED, &tcb->flags)))
		return NETDEV_TX_OK;

	bna_txq_prod_indx_doorbell(tcb);
	smp_mb();

	return NETDEV_TX_OK;
}