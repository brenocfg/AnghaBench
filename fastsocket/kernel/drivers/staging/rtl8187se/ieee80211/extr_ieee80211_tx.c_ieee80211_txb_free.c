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
struct ieee80211_txb {int nr_frags; scalar_t__* fragments; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_txb*) ; 
 scalar_t__ unlikely (int) ; 

void ieee80211_txb_free(struct ieee80211_txb *txb) {
	int i;
	if (unlikely(!txb))
		return;
	for (i = 0; i < txb->nr_frags; i++)
		if (txb->fragments[i])
			dev_kfree_skb_any(txb->fragments[i]);
	kfree(txb);
}