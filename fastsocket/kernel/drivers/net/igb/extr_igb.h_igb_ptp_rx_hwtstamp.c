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
struct sk_buff {int dummy; } ;
struct igb_ring {int /*<<< orphan*/  last_rx_timestamp; int /*<<< orphan*/  q_vector; } ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_RXDADV_STAT_TS ; 
 int /*<<< orphan*/  E1000_RXDADV_STAT_TSIP ; 
 int /*<<< orphan*/  igb_ptp_rx_rgtstamp (int /*<<< orphan*/ ,struct sk_buff*) ; 
 scalar_t__ igb_test_staterr (union e1000_adv_rx_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 

__attribute__((used)) static inline void igb_ptp_rx_hwtstamp(struct igb_ring *rx_ring,
				       union e1000_adv_rx_desc *rx_desc,
				       struct sk_buff *skb)
{
	if (igb_test_staterr(rx_desc, E1000_RXDADV_STAT_TS) &&
	    !igb_test_staterr(rx_desc, E1000_RXDADV_STAT_TSIP))
		igb_ptp_rx_rgtstamp(rx_ring->q_vector, skb);

	/* Update the last_rx_timestamp timer in order to enable watchdog check
	 * for error case of latched timestamp on a dropped packet.
	 */
	rx_ring->last_rx_timestamp = jiffies;
}