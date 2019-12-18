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
struct neighbour {scalar_t__ nud_state; int /*<<< orphan*/  arp_queue; int /*<<< orphan*/  lock; TYPE_1__* ops; int /*<<< orphan*/  updated; int /*<<< orphan*/  tbl; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* error_report ) (struct neighbour*,struct sk_buff*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NEIGH_CACHE_STAT_INC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEIGH_PRINTK2 (char*,struct neighbour*) ; 
 scalar_t__ NUD_FAILED ; 
 struct sk_buff* __skb_dequeue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  res_failed ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct neighbour*,struct sk_buff*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void neigh_invalidate(struct neighbour *neigh)
{
	struct sk_buff *skb;

	NEIGH_CACHE_STAT_INC(neigh->tbl, res_failed);
	NEIGH_PRINTK2("neigh %p is failed.\n", neigh);
	neigh->updated = jiffies;

	/* It is very thin place. report_unreachable is very complicated
	   routine. Particularly, it can hit the same neighbour entry!

	   So that, we try to be accurate and avoid dead loop. --ANK
	 */
	while (neigh->nud_state == NUD_FAILED &&
	       (skb = __skb_dequeue(&neigh->arp_queue)) != NULL) {
		write_unlock(&neigh->lock);
		neigh->ops->error_report(neigh, skb);
		write_lock(&neigh->lock);
	}
	skb_queue_purge(&neigh->arp_queue);
}