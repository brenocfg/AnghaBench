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
typedef  size_t u32 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct be_queue_info {size_t head; scalar_t__ len; int /*<<< orphan*/  used; } ;
struct be_tx_obj {struct sk_buff** sent_skb_list; struct be_queue_info q; } ;
struct be_adapter {struct be_tx_obj* tx_obj; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_2__ {int gso_segs; } ;

/* Variables and functions */
 scalar_t__ BE_MAX_TX_FRAG_COUNT ; 
 int /*<<< orphan*/  BUG_ON (struct sk_buff*) ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  atomic_add (size_t,int /*<<< orphan*/ *) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  be_tx_stats_update (struct be_tx_obj*,size_t,size_t,int,int) ; 
 int /*<<< orphan*/  be_txq_notify (struct be_adapter*,struct be_tx_obj*,size_t) ; 
 struct sk_buff* be_xmit_workarounds (struct be_adapter*,struct sk_buff*,int*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 size_t make_tx_wrbs (struct be_adapter*,struct be_queue_info*,struct sk_buff*,size_t,int,int) ; 
 struct be_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_subqueue (struct net_device*,size_t) ; 
 size_t skb_get_queue_mapping (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 size_t wrb_cnt_for_skb (struct be_adapter*,struct sk_buff*,int*) ; 

__attribute__((used)) static netdev_tx_t be_xmit(struct sk_buff *skb, struct net_device *netdev)
{
	struct be_adapter *adapter = netdev_priv(netdev);
	struct be_tx_obj *txo = &adapter->tx_obj[skb_get_queue_mapping(skb)];
	struct be_queue_info *txq = &txo->q;
	bool dummy_wrb, stopped = false;
	u32 wrb_cnt = 0, copied = 0;
	bool skip_hw_vlan = false;
	u32 start = txq->head;

	skb = be_xmit_workarounds(adapter, skb, &skip_hw_vlan);
	if (!skb)
		return NETDEV_TX_OK;

	wrb_cnt = wrb_cnt_for_skb(adapter, skb, &dummy_wrb);

	copied = make_tx_wrbs(adapter, txq, skb, wrb_cnt, dummy_wrb,
			      skip_hw_vlan);
	if (copied) {
		int gso_segs = skb_shinfo(skb)->gso_segs;

		/* record the sent skb in the sent_skb table */
		BUG_ON(txo->sent_skb_list[start]);
		txo->sent_skb_list[start] = skb;

		/* Ensure txq has space for the next skb; Else stop the queue
		 * *BEFORE* ringing the tx doorbell, so that we serialze the
		 * tx compls of the current transmit which'll wake up the queue
		 */
		atomic_add(wrb_cnt, &txq->used);
		if ((BE_MAX_TX_FRAG_COUNT + atomic_read(&txq->used)) >=
								txq->len) {
			netif_stop_subqueue(netdev, skb_get_queue_mapping(skb));
			stopped = true;
		}

		be_txq_notify(adapter, txo, wrb_cnt);

		be_tx_stats_update(txo, wrb_cnt, copied, gso_segs, stopped);
	} else {
		txq->head = start;
		dev_kfree_skb_any(skb);
	}
	return NETDEV_TX_OK;
}