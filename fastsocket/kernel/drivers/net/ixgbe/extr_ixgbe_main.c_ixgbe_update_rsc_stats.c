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
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rsc_flush; int /*<<< orphan*/  rsc_count; } ;
struct ixgbe_ring {TYPE_1__ rx_stats; } ;
struct TYPE_4__ {scalar_t__ append_cnt; } ;

/* Variables and functions */
 TYPE_2__* IXGBE_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  ixgbe_set_rsc_gso_size (struct ixgbe_ring*,struct sk_buff*) ; 

__attribute__((used)) static void ixgbe_update_rsc_stats(struct ixgbe_ring *rx_ring,
				   struct sk_buff *skb)
{
	/* if append_cnt is 0 then frame is not RSC */
	if (!IXGBE_CB(skb)->append_cnt)
		return;

	rx_ring->rx_stats.rsc_count += IXGBE_CB(skb)->append_cnt;
	rx_ring->rx_stats.rsc_flush++;

	ixgbe_set_rsc_gso_size(rx_ring, skb);

	/* gso_size is computed using append_cnt so always clear it last */
	IXGBE_CB(skb)->append_cnt = 0;
}