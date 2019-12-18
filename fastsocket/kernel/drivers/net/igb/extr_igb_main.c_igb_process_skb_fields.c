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
typedef  union e1000_adv_rx_desc {int dummy; } e1000_adv_rx_desc ;
struct sk_buff {int /*<<< orphan*/  protocol; } ;
struct igb_ring {int /*<<< orphan*/  netdev; int /*<<< orphan*/  queue_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  igb_ptp_rx_hwtstamp (struct igb_ring*,union e1000_adv_rx_desc*,struct sk_buff*) ; 
 int /*<<< orphan*/  igb_rx_checksum (struct igb_ring*,union e1000_adv_rx_desc*,struct sk_buff*) ; 
 int /*<<< orphan*/  igb_rx_hash (struct igb_ring*,union e1000_adv_rx_desc*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_record_rx_queue (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void igb_process_skb_fields(struct igb_ring *rx_ring,
				   union e1000_adv_rx_desc *rx_desc,
				   struct sk_buff *skb)
{
	igb_rx_hash(rx_ring, rx_desc, skb);

	igb_rx_checksum(rx_ring, rx_desc, skb);

	igb_ptp_rx_hwtstamp(rx_ring, rx_desc, skb);

	skb_record_rx_queue(skb, rx_ring->queue_index);

	skb->protocol = eth_type_trans(skb, rx_ring->netdev);
}