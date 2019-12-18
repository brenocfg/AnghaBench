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
struct TYPE_6__ {unsigned int tx_bytes; unsigned int tx_packets; } ;
struct net_device {TYPE_3__ stats; } ;
struct e1000_tx_ring {unsigned int next_to_clean; unsigned int count; struct e1000_buffer* buffer_info; int /*<<< orphan*/  next_to_use; scalar_t__ tdt; scalar_t__ tdh; } ;
struct TYPE_4__ {int /*<<< orphan*/  status; } ;
struct TYPE_5__ {int data; TYPE_1__ fields; } ;
struct e1000_tx_desc {TYPE_2__ upper; } ;
struct e1000_hw {scalar_t__ hw_addr; } ;
struct e1000_buffer {unsigned int next_to_watch; scalar_t__ time_stamp; scalar_t__ bytecount; scalar_t__ segs; } ;
struct e1000_adapter {int detect_tx_hung; int tx_timeout_factor; unsigned int total_tx_bytes; unsigned int total_tx_packets; struct e1000_tx_ring* tx_ring; int /*<<< orphan*/  restart_queue; int /*<<< orphan*/  flags; struct net_device* netdev; struct e1000_hw hw; } ;

/* Variables and functions */
 scalar_t__ E1000_DESC_UNUSED (struct e1000_tx_ring*) ; 
 int E1000_STATUS_TXOFF ; 
 int /*<<< orphan*/  E1000_TXD_STAT_DD ; 
 struct e1000_tx_desc* E1000_TX_DESC (struct e1000_tx_ring,unsigned int) ; 
 int HZ ; 
 int /*<<< orphan*/  STATUS ; 
 scalar_t__ TX_WAKE_THRESHOLD ; 
 int /*<<< orphan*/  __E1000_DOWN ; 
 int cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  e1000_dump (struct e1000_adapter*) ; 
 int /*<<< orphan*/  e1000_unmap_and_free_tx_resource (struct e1000_adapter*,struct e1000_buffer*) ; 
 int /*<<< orphan*/  e_err (int /*<<< orphan*/ ,char*,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,scalar_t__,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int er32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ netif_carrier_ok (struct net_device*) ; 
 scalar_t__ netif_queue_stopped (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  rmb () ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool e1000_clean_tx_irq(struct e1000_adapter *adapter,
			       struct e1000_tx_ring *tx_ring)
{
	struct e1000_hw *hw = &adapter->hw;
	struct net_device *netdev = adapter->netdev;
	struct e1000_tx_desc *tx_desc, *eop_desc;
	struct e1000_buffer *buffer_info;
	unsigned int i, eop;
	unsigned int count = 0;
	unsigned int total_tx_bytes=0, total_tx_packets=0;

	i = tx_ring->next_to_clean;
	eop = tx_ring->buffer_info[i].next_to_watch;
	eop_desc = E1000_TX_DESC(*tx_ring, eop);

	while ((eop_desc->upper.data & cpu_to_le32(E1000_TXD_STAT_DD)) &&
	       (count < tx_ring->count)) {
		bool cleaned = false;
		rmb();	/* read buffer_info after eop_desc */
		for ( ; !cleaned; count++) {
			tx_desc = E1000_TX_DESC(*tx_ring, i);
			buffer_info = &tx_ring->buffer_info[i];
			cleaned = (i == eop);

			if (cleaned) {
				total_tx_packets += buffer_info->segs;
				total_tx_bytes += buffer_info->bytecount;
			}
			e1000_unmap_and_free_tx_resource(adapter, buffer_info);
			tx_desc->upper.data = 0;

			if (unlikely(++i == tx_ring->count)) i = 0;
		}

		eop = tx_ring->buffer_info[i].next_to_watch;
		eop_desc = E1000_TX_DESC(*tx_ring, eop);
	}

	tx_ring->next_to_clean = i;

#define TX_WAKE_THRESHOLD 32
	if (unlikely(count && netif_carrier_ok(netdev) &&
		     E1000_DESC_UNUSED(tx_ring) >= TX_WAKE_THRESHOLD)) {
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean.
		 */
		smp_mb();

		if (netif_queue_stopped(netdev) &&
		    !(test_bit(__E1000_DOWN, &adapter->flags))) {
			netif_wake_queue(netdev);
			++adapter->restart_queue;
		}
	}

	if (adapter->detect_tx_hung) {
		/* Detect a transmit hang in hardware, this serializes the
		 * check with the clearing of time_stamp and movement of i */
		adapter->detect_tx_hung = false;
		if (tx_ring->buffer_info[eop].time_stamp &&
		    time_after(jiffies, tx_ring->buffer_info[eop].time_stamp +
		               (adapter->tx_timeout_factor * HZ)) &&
		    !(er32(STATUS) & E1000_STATUS_TXOFF)) {

			/* detected Tx unit hang */
			e_err(drv, "Detected Tx Unit Hang\n"
			      "  Tx Queue             <%lu>\n"
			      "  TDH                  <%x>\n"
			      "  TDT                  <%x>\n"
			      "  next_to_use          <%x>\n"
			      "  next_to_clean        <%x>\n"
			      "buffer_info[next_to_clean]\n"
			      "  time_stamp           <%lx>\n"
			      "  next_to_watch        <%x>\n"
			      "  jiffies              <%lx>\n"
			      "  next_to_watch.status <%x>\n",
				(unsigned long)((tx_ring - adapter->tx_ring) /
					sizeof(struct e1000_tx_ring)),
				readl(hw->hw_addr + tx_ring->tdh),
				readl(hw->hw_addr + tx_ring->tdt),
				tx_ring->next_to_use,
				tx_ring->next_to_clean,
				tx_ring->buffer_info[eop].time_stamp,
				eop,
				jiffies,
				eop_desc->upper.fields.status);
			e1000_dump(adapter);
			netif_stop_queue(netdev);
		}
	}
	adapter->total_tx_bytes += total_tx_bytes;
	adapter->total_tx_packets += total_tx_packets;
	netdev->stats.tx_bytes += total_tx_bytes;
	netdev->stats.tx_packets += total_tx_packets;
	return count < tx_ring->count;
}