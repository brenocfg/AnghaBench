#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct netfront_info {TYPE_1__* tx_skbs; int /*<<< orphan*/  tx_skb_freelist; int /*<<< orphan*/ * grant_tx_ref; int /*<<< orphan*/  gref_tx_head; } ;
struct TYPE_3__ {struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  GNTMAP_readonly ; 
 int /*<<< orphan*/  GRANT_INVALID_REF ; 
 int NET_TX_RING_SIZE ; 
 int /*<<< orphan*/  add_id_to_freelist (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  dev_kfree_skb_irq (struct sk_buff*) ; 
 int /*<<< orphan*/  gnttab_end_foreign_access_ref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gnttab_release_grant_reference (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_entry_is_link (TYPE_1__*) ; 

__attribute__((used)) static void xennet_release_tx_bufs(struct netfront_info *np)
{
	struct sk_buff *skb;
	int i;

	for (i = 0; i < NET_TX_RING_SIZE; i++) {
		/* Skip over entries which are actually freelist references */
		if (skb_entry_is_link(&np->tx_skbs[i]))
			continue;

		skb = np->tx_skbs[i].skb;
		gnttab_end_foreign_access_ref(np->grant_tx_ref[i],
					      GNTMAP_readonly);
		gnttab_release_grant_reference(&np->gref_tx_head,
					       np->grant_tx_ref[i]);
		np->grant_tx_ref[i] = GRANT_INVALID_REF;
		add_id_to_freelist(&np->tx_skb_freelist, np->tx_skbs, i);
		dev_kfree_skb_irq(skb);
	}
}