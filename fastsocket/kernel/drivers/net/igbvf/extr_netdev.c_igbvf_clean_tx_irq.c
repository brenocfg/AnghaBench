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
struct TYPE_4__ {int status; } ;
union e1000_adv_tx_desc {TYPE_1__ wb; } ;
struct sk_buff {unsigned int len; } ;
struct net_device {int dummy; } ;
struct igbvf_ring {unsigned int next_to_clean; unsigned int count; struct igbvf_buffer* buffer_info; struct igbvf_adapter* adapter; } ;
struct igbvf_buffer {union e1000_adv_tx_desc* next_to_watch; struct sk_buff* skb; } ;
struct TYPE_5__ {unsigned int tx_bytes; unsigned int tx_packets; } ;
struct igbvf_adapter {TYPE_2__ net_stats; int /*<<< orphan*/  restart_queue; int /*<<< orphan*/  state; struct net_device* netdev; } ;
struct TYPE_6__ {scalar_t__ gso_segs; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_TXD_STAT_DD ; 
 union e1000_adv_tx_desc* IGBVF_TX_DESC_ADV (struct igbvf_ring,unsigned int) ; 
 scalar_t__ IGBVF_TX_QUEUE_WAKE ; 
 int /*<<< orphan*/  __IGBVF_DOWN ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 scalar_t__ igbvf_desc_unused (struct igbvf_ring*) ; 
 int /*<<< orphan*/  igbvf_put_txbuf (struct igbvf_adapter*,struct igbvf_buffer*) ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  read_barrier_depends () ; 
 unsigned int skb_headlen (struct sk_buff*) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool igbvf_clean_tx_irq(struct igbvf_ring *tx_ring)
{
	struct igbvf_adapter *adapter = tx_ring->adapter;
	struct net_device *netdev = adapter->netdev;
	struct igbvf_buffer *buffer_info;
	struct sk_buff *skb;
	union e1000_adv_tx_desc *tx_desc, *eop_desc;
	unsigned int total_bytes = 0, total_packets = 0;
	unsigned int i, count = 0;
	bool cleaned = false;

	i = tx_ring->next_to_clean;
	buffer_info = &tx_ring->buffer_info[i];
	eop_desc = buffer_info->next_to_watch;

	do {
		/* if next_to_watch is not set then there is no work pending */
		if (!eop_desc)
			break;

		/* prevent any other reads prior to eop_desc */
		read_barrier_depends();

		/* if DD is not set pending work has not been completed */
		if (!(eop_desc->wb.status & cpu_to_le32(E1000_TXD_STAT_DD)))
			break;

		/* clear next_to_watch to prevent false hangs */
		buffer_info->next_to_watch = NULL;

		for (cleaned = false; !cleaned; count++) {
			tx_desc = IGBVF_TX_DESC_ADV(*tx_ring, i);
			cleaned = (tx_desc == eop_desc);
			skb = buffer_info->skb;

			if (skb) {
				unsigned int segs, bytecount;

				/* gso_segs is currently only valid for tcp */
				segs = skb_shinfo(skb)->gso_segs ?: 1;
				/* multiply data chunks by size of headers */
				bytecount = ((segs - 1) * skb_headlen(skb)) +
				            skb->len;
				total_packets += segs;
				total_bytes += bytecount;
			}

			igbvf_put_txbuf(adapter, buffer_info);
			tx_desc->wb.status = 0;

			i++;
			if (i == tx_ring->count)
				i = 0;

			buffer_info = &tx_ring->buffer_info[i];
		}

		eop_desc = buffer_info->next_to_watch;
	} while (count < tx_ring->count);

	tx_ring->next_to_clean = i;

	if (unlikely(count &&
	             netif_carrier_ok(netdev) &&
	             igbvf_desc_unused(tx_ring) >= IGBVF_TX_QUEUE_WAKE)) {
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean.
		 */
		smp_mb();
		if (netif_queue_stopped(netdev) &&
		    !(test_bit(__IGBVF_DOWN, &adapter->state))) {
			netif_wake_queue(netdev);
			++adapter->restart_queue;
		}
	}

	adapter->net_stats.tx_bytes += total_bytes;
	adapter->net_stats.tx_packets += total_packets;
	return count < tx_ring->count;
}