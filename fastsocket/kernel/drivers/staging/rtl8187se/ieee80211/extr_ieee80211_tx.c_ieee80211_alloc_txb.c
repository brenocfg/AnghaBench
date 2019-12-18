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
typedef  int /*<<< orphan*/  u8 ;
struct ieee80211_txb {int nr_frags; int frag_size; int /*<<< orphan*/ * fragments; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_alloc_skb (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ieee80211_txb*) ; 
 struct ieee80211_txb* kmalloc (int,int) ; 
 int /*<<< orphan*/  memset (struct ieee80211_txb*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

struct ieee80211_txb *ieee80211_alloc_txb(int nr_frags, int txb_size,
					  int gfp_mask)
{
	struct ieee80211_txb *txb;
	int i;
	txb = kmalloc(
		sizeof(struct ieee80211_txb) + (sizeof(u8*) * nr_frags),
		gfp_mask);
	if (!txb)
		return NULL;

	memset(txb, 0, sizeof(struct ieee80211_txb));
	txb->nr_frags = nr_frags;
	txb->frag_size = txb_size;

	for (i = 0; i < nr_frags; i++) {
		txb->fragments[i] = dev_alloc_skb(txb_size);
		if (unlikely(!txb->fragments[i])) {
			i--;
			break;
		}
	}
	if (unlikely(i != nr_frags)) {
		while (i >= 0)
			dev_kfree_skb_any(txb->fragments[i--]);
		kfree(txb);
		return NULL;
	}
	return txb;
}