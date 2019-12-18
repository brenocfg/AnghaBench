#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct jme_ring {int next_to_use; int /*<<< orphan*/  nr_free; } ;
struct jme_adapter {int tx_ring_mask; struct jme_ring* txring; } ;
struct TYPE_2__ {int nr_frags; } ;

/* Variables and functions */
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
jme_alloc_txdesc(struct jme_adapter *jme,
			struct sk_buff *skb)
{
	struct jme_ring *txring = &(jme->txring[0]);
	int idx, nr_alloc, mask = jme->tx_ring_mask;

	idx = txring->next_to_use;
	nr_alloc = skb_shinfo(skb)->nr_frags + 2;

	if (unlikely(atomic_read(&txring->nr_free) < nr_alloc))
		return -1;

	atomic_sub(nr_alloc, &txring->nr_free);

	txring->next_to_use = (txring->next_to_use + nr_alloc) & mask;

	return idx;
}