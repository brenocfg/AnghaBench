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
struct net_device {int dummy; } ;
struct neighbour {int dead; int nud_state; int /*<<< orphan*/  lock; int /*<<< orphan*/  output; int /*<<< orphan*/  arp_queue; int /*<<< orphan*/  refcnt; struct neighbour* next; struct net_device* dev; } ;
struct neigh_table {int hash_mask; struct neighbour** hash_buckets; } ;

/* Variables and functions */
 int /*<<< orphan*/  NEIGH_PRINTK2 (char*,struct neighbour*) ; 
 int NUD_NOARP ; 
 int NUD_NONE ; 
 int NUD_VALID ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neigh_blackhole ; 
 int /*<<< orphan*/  neigh_cleanup_and_release (struct neighbour*) ; 
 int /*<<< orphan*/  neigh_del_timer (struct neighbour*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void neigh_flush_dev(struct neigh_table *tbl, struct net_device *dev)
{
	int i;

	for (i = 0; i <= tbl->hash_mask; i++) {
		struct neighbour *n, **np = &tbl->hash_buckets[i];

		while ((n = *np) != NULL) {
			if (dev && n->dev != dev) {
				np = &n->next;
				continue;
			}
			*np = n->next;
			write_lock(&n->lock);
			neigh_del_timer(n);
			n->dead = 1;

			if (atomic_read(&n->refcnt) != 1) {
				/* The most unpleasant situation.
				   We must destroy neighbour entry,
				   but someone still uses it.

				   The destroy will be delayed until
				   the last user releases us, but
				   we must kill timers etc. and move
				   it to safe state.
				 */
				skb_queue_purge(&n->arp_queue);
				n->output = neigh_blackhole;
				if (n->nud_state & NUD_VALID)
					n->nud_state = NUD_NOARP;
				else
					n->nud_state = NUD_NONE;
				NEIGH_PRINTK2("neigh %p is stray.\n", n);
			}
			write_unlock(&n->lock);
			neigh_cleanup_and_release(n);
		}
	}
}