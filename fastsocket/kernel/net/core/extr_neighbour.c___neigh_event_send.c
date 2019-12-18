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
struct neighbour {int nud_state; unsigned long updated; int /*<<< orphan*/  lock; int /*<<< orphan*/  arp_queue; int /*<<< orphan*/  tbl; TYPE_1__* parms; int /*<<< orphan*/  probes; } ;
struct TYPE_2__ {unsigned long delay_probe_time; scalar_t__ queue_len; int /*<<< orphan*/  ucast_probes; scalar_t__ app_probes; scalar_t__ mcast_probes; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEIGH_CACHE_STAT_INC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEIGH_PRINTK2 (char*,struct neighbour*) ; 
 int NUD_CONNECTED ; 
 int NUD_DELAY ; 
 int NUD_FAILED ; 
 int NUD_INCOMPLETE ; 
 int NUD_PROBE ; 
 int NUD_STALE ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  neigh_add_timer (struct neighbour*,unsigned long) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unres_discards ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

int __neigh_event_send(struct neighbour *neigh, struct sk_buff *skb)
{
	int rc;
	unsigned long now;

	write_lock_bh(&neigh->lock);

	rc = 0;
	if (neigh->nud_state & (NUD_CONNECTED | NUD_DELAY | NUD_PROBE))
		goto out_unlock_bh;

	now = jiffies;

	if (!(neigh->nud_state & (NUD_STALE | NUD_INCOMPLETE))) {
		if (neigh->parms->mcast_probes + neigh->parms->app_probes) {
			atomic_set(&neigh->probes, neigh->parms->ucast_probes);
			neigh->nud_state     = NUD_INCOMPLETE;
			neigh->updated = jiffies;
			neigh_add_timer(neigh, now + 1);
		} else {
			neigh->nud_state = NUD_FAILED;
			neigh->updated = jiffies;
			write_unlock_bh(&neigh->lock);

			kfree_skb(skb);
			return 1;
		}
	} else if (neigh->nud_state & NUD_STALE) {
		NEIGH_PRINTK2("neigh %p is delayed.\n", neigh);
		neigh->nud_state = NUD_DELAY;
		neigh->updated = jiffies;
		neigh_add_timer(neigh,
				jiffies + neigh->parms->delay_probe_time);
	}

	if (neigh->nud_state == NUD_INCOMPLETE) {
		if (skb) {
			if (skb_queue_len(&neigh->arp_queue) >=
			    neigh->parms->queue_len) {
				struct sk_buff *buff;
				buff = __skb_dequeue(&neigh->arp_queue);
				kfree_skb(buff);
				NEIGH_CACHE_STAT_INC(neigh->tbl, unres_discards);
			}
			__skb_queue_tail(&neigh->arp_queue, skb);
		}
		rc = 1;
	}
out_unlock_bh:
	write_unlock_bh(&neigh->lock);
	return rc;
}