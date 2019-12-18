#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  rss; } ;
struct TYPE_7__ {TYPE_2__ hi_dword; } ;
struct TYPE_8__ {TYPE_3__ lower; } ;
union ixgbe_adv_rx_desc {TYPE_4__ wb; } ;
struct sk_buff {int /*<<< orphan*/  rxhash; } ;
struct ixgbe_ring {TYPE_1__* netdev; } ;
struct TYPE_5__ {int features; } ;

/* Variables and functions */
 int NETIF_F_RXHASH ; 
 int /*<<< orphan*/  le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ixgbe_rx_hash(struct ixgbe_ring *ring,
				 union ixgbe_adv_rx_desc *rx_desc,
				 struct sk_buff *skb)
{
	if (ring->netdev->features & NETIF_F_RXHASH)
		skb->rxhash = le32_to_cpu(rx_desc->wb.lower.hi_dword.rss);
}