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
struct net_local {scalar_t__ out_idx; scalar_t__ sk_count; int /*<<< orphan*/ * skbs; } ;

/* Variables and functions */
 scalar_t__ MAX_SKB_BUFFERS ; 
 int /*<<< orphan*/  dev_kfree_skb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
flush_tx_buffers(struct net_local *nl)
{

	while (nl->sk_count) {
		dev_kfree_skb(nl->skbs[nl->out_idx++]);		/* free skb */
		if (nl->out_idx >= MAX_SKB_BUFFERS)
			nl->out_idx = 0;	/* wrap around */
		nl->sk_count--;
	}
}