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
typedef  size_t uint ;
struct sk_buff {scalar_t__ cb; } ;
struct ieee80211_tx_info {int dummy; } ;
struct dma_pub {int dummy; } ;
struct dma_info {size_t txin; size_t txout; struct sk_buff** txp; } ;
typedef  int /*<<< orphan*/  callback_fnc ;

/* Variables and functions */
 size_t nexttxd (struct dma_info*,size_t) ; 

void dma_walk_packets(struct dma_pub *dmah, void (*callback_fnc)
		      (void *pkt, void *arg_a), void *arg_a)
{
	struct dma_info *di = (struct dma_info *) dmah;
	uint i =   di->txin;
	uint end = di->txout;
	struct sk_buff *skb;
	struct ieee80211_tx_info *tx_info;

	while (i != end) {
		skb = di->txp[i];
		if (skb != NULL) {
			tx_info = (struct ieee80211_tx_info *)skb->cb;
			(callback_fnc)(tx_info, arg_a);
		}
		i = nexttxd(di, i);
	}
}