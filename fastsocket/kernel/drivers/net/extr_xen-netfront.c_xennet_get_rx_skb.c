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
struct sk_buff {int dummy; } ;
struct netfront_info {struct sk_buff** rx_skbs; } ;
typedef  int /*<<< orphan*/  RING_IDX ;

/* Variables and functions */
 int xennet_rxidx (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *xennet_get_rx_skb(struct netfront_info *np,
					 RING_IDX ri)
{
	int i = xennet_rxidx(ri);
	struct sk_buff *skb = np->rx_skbs[i];
	np->rx_skbs[i] = NULL;
	return skb;
}