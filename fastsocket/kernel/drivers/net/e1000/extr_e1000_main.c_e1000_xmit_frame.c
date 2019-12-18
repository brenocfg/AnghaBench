#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int u8 ;
struct sk_buff {scalar_t__ len; unsigned int data_len; scalar_t__ ip_summed; scalar_t__ protocol; } ;
struct net_device {int dummy; } ;
struct e1000_tx_ring {int last_tx_tso; unsigned int next_to_use; TYPE_2__* buffer_info; } ;
struct e1000_hw {int mac_type; scalar_t__ bus_type; } ;
struct e1000_adapter {int /*<<< orphan*/  fifo_stall_task; int /*<<< orphan*/  flags; scalar_t__ pcix_82544; struct e1000_tx_ring* tx_ring; struct e1000_hw hw; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;
struct TYPE_6__ {unsigned int gso_size; unsigned int nr_frags; TYPE_1__* frags; } ;
struct TYPE_5__ {scalar_t__ time_stamp; } ;
struct TYPE_4__ {unsigned int size; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 unsigned int E1000_MAX_DATA_PER_TXD ; 
 unsigned int E1000_MAX_TXD_PWR ; 
 unsigned int E1000_TX_FLAGS_CSUM ; 
 unsigned int E1000_TX_FLAGS_IPV4 ; 
 unsigned int E1000_TX_FLAGS_TSO ; 
 unsigned int E1000_TX_FLAGS_VLAN ; 
 unsigned int E1000_TX_FLAGS_VLAN_SHIFT ; 
 int /*<<< orphan*/  ETH_P_IP ; 
 int MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ TXD_USE_COUNT (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  __E1000_DOWN ; 
 int /*<<< orphan*/  __pskb_pull_tail (struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  drv ; 
#define  e1000_82544 128 
 int e1000_82547 ; 
 scalar_t__ e1000_82547_fifo_workaround (struct e1000_adapter*,struct sk_buff*) ; 
 scalar_t__ e1000_bus_type_pcix ; 
 int e1000_maybe_stop_tx (struct net_device*,struct e1000_tx_ring*,int) ; 
 int e1000_tso (struct e1000_adapter*,struct e1000_tx_ring*,struct sk_buff*) ; 
 int e1000_tx_csum (struct e1000_adapter*,struct e1000_tx_ring*,struct sk_buff*) ; 
 int e1000_tx_map (struct e1000_adapter*,struct e1000_tx_ring*,struct sk_buff*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  e1000_tx_queue (struct e1000_adapter*,struct e1000_tx_ring*,unsigned int,int) ; 
 int /*<<< orphan*/  e_err (int /*<<< orphan*/ ,char*) ; 
 int fls (unsigned int) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 struct e1000_adapter* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int) ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_tail_pointer (struct sk_buff*) ; 
 unsigned int skb_transport_offset (struct sk_buff*) ; 
 unsigned int tcp_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 unsigned int vlan_tx_tag_get (struct sk_buff*) ; 
 int vlan_tx_tag_present (struct sk_buff*) ; 

__attribute__((used)) static netdev_tx_t e1000_xmit_frame(struct sk_buff *skb,
				    struct net_device *netdev)
{
	struct e1000_adapter *adapter = netdev_priv(netdev);
	struct e1000_hw *hw = &adapter->hw;
	struct e1000_tx_ring *tx_ring;
	unsigned int first, max_per_txd = E1000_MAX_DATA_PER_TXD;
	unsigned int max_txd_pwr = E1000_MAX_TXD_PWR;
	unsigned int tx_flags = 0;
	unsigned int len = skb_headlen(skb);
	unsigned int nr_frags;
	unsigned int mss;
	int count = 0;
	int tso;
	unsigned int f;

	/* This goes back to the question of how to logically map a tx queue
	 * to a flow.  Right now, performance is impacted slightly negatively
	 * if using multiple tx queues.  If the stack breaks away from a
	 * single qdisc implementation, we can look at this again. */
	tx_ring = adapter->tx_ring;

	if (unlikely(skb->len <= 0)) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	mss = skb_shinfo(skb)->gso_size;
	/* The controller does a simple calculation to
	 * make sure there is enough room in the FIFO before
	 * initiating the DMA for each buffer.  The calc is:
	 * 4 = ceil(buffer len/mss).  To make sure we don't
	 * overrun the FIFO, adjust the max buffer len if mss
	 * drops. */
	if (mss) {
		u8 hdr_len;
		max_per_txd = min(mss << 2, max_per_txd);
		max_txd_pwr = fls(max_per_txd) - 1;

		hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
		if (skb->data_len && hdr_len == len) {
			switch (hw->mac_type) {
				unsigned int pull_size;
			case e1000_82544:
				/* Make sure we have room to chop off 4 bytes,
				 * and that the end alignment will work out to
				 * this hardware's requirements
				 * NOTE: this is a TSO only workaround
				 * if end byte alignment not correct move us
				 * into the next dword */
				if ((unsigned long)(skb_tail_pointer(skb) - 1) & 4)
					break;
				/* fall through */
				pull_size = min((unsigned int)4, skb->data_len);
				if (!__pskb_pull_tail(skb, pull_size)) {
					e_err(drv, "__pskb_pull_tail "
					      "failed.\n");
					dev_kfree_skb_any(skb);
					return NETDEV_TX_OK;
				}
				len = skb_headlen(skb);
				break;
			default:
				/* do nothing */
				break;
			}
		}
	}

	/* reserve a descriptor for the offload context */
	if ((mss) || (skb->ip_summed == CHECKSUM_PARTIAL))
		count++;
	count++;

	/* Controller Erratum workaround */
	if (!skb->data_len && tx_ring->last_tx_tso && !skb_is_gso(skb))
		count++;

	count += TXD_USE_COUNT(len, max_txd_pwr);

	if (adapter->pcix_82544)
		count++;

	/* work-around for errata 10 and it applies to all controllers
	 * in PCI-X mode, so add one more descriptor to the count
	 */
	if (unlikely((hw->bus_type == e1000_bus_type_pcix) &&
			(len > 2015)))
		count++;

	nr_frags = skb_shinfo(skb)->nr_frags;
	for (f = 0; f < nr_frags; f++)
		count += TXD_USE_COUNT(skb_shinfo(skb)->frags[f].size,
				       max_txd_pwr);
	if (adapter->pcix_82544)
		count += nr_frags;

	/* need: count + 2 desc gap to keep tail from touching
	 * head, otherwise try next time */
	if (unlikely(e1000_maybe_stop_tx(netdev, tx_ring, count + 2)))
		return NETDEV_TX_BUSY;

	if (unlikely((hw->mac_type == e1000_82547) &&
		     (e1000_82547_fifo_workaround(adapter, skb)))) {
		netif_stop_queue(netdev);
		if (!test_bit(__E1000_DOWN, &adapter->flags))
			schedule_delayed_work(&adapter->fifo_stall_task, 1);
		return NETDEV_TX_BUSY;
	}

	if (unlikely(vlan_tx_tag_present(skb))) {
		tx_flags |= E1000_TX_FLAGS_VLAN;
		tx_flags |= (vlan_tx_tag_get(skb) << E1000_TX_FLAGS_VLAN_SHIFT);
	}

	first = tx_ring->next_to_use;

	tso = e1000_tso(adapter, tx_ring, skb);
	if (tso < 0) {
		dev_kfree_skb_any(skb);
		return NETDEV_TX_OK;
	}

	if (likely(tso)) {
		if (likely(hw->mac_type != e1000_82544))
			tx_ring->last_tx_tso = true;
		tx_flags |= E1000_TX_FLAGS_TSO;
	} else if (likely(e1000_tx_csum(adapter, tx_ring, skb)))
		tx_flags |= E1000_TX_FLAGS_CSUM;

	if (likely(skb->protocol == htons(ETH_P_IP)))
		tx_flags |= E1000_TX_FLAGS_IPV4;

	count = e1000_tx_map(adapter, tx_ring, skb, first, max_per_txd,
	                     nr_frags, mss);

	if (count) {
		e1000_tx_queue(adapter, tx_ring, tx_flags, count);
		/* Make sure there is space in the ring for the next send. */
		e1000_maybe_stop_tx(netdev, tx_ring, MAX_SKB_FRAGS + 2);

	} else {
		dev_kfree_skb_any(skb);
		tx_ring->buffer_info[first].time_stamp = 0;
		tx_ring->next_to_use = first;
	}

	return NETDEV_TX_OK;
}