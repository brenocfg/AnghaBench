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
struct neighbour {unsigned long updated; unsigned long used; int dead; int /*<<< orphan*/  refcnt; struct neigh_table* tbl; int /*<<< orphan*/  timer; int /*<<< orphan*/  parms; int /*<<< orphan*/  output; int /*<<< orphan*/  nud_state; int /*<<< orphan*/  lock; int /*<<< orphan*/  arp_queue; } ;
struct neigh_table {int gc_thresh3; int gc_thresh2; int /*<<< orphan*/  entries; int /*<<< orphan*/  parms; int /*<<< orphan*/  kmem_cachep; scalar_t__ last_flush; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HZ ; 
 int /*<<< orphan*/  NEIGH_CACHE_STAT_INC (struct neigh_table*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUD_NONE ; 
 int /*<<< orphan*/  allocs ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 unsigned long jiffies ; 
 struct neighbour* kmem_cache_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  neigh_blackhole ; 
 int /*<<< orphan*/  neigh_forced_gc (struct neigh_table*) ; 
 int /*<<< orphan*/  neigh_parms_clone (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  neigh_timer_handler ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setup_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 scalar_t__ time_after (unsigned long,scalar_t__) ; 

__attribute__((used)) static struct neighbour *neigh_alloc(struct neigh_table *tbl)
{
	struct neighbour *n = NULL;
	unsigned long now = jiffies;
	int entries;

	entries = atomic_inc_return(&tbl->entries) - 1;
	if (entries >= tbl->gc_thresh3 ||
	    (entries >= tbl->gc_thresh2 &&
	     time_after(now, tbl->last_flush + 5 * HZ))) {
		if (!neigh_forced_gc(tbl) &&
		    entries >= tbl->gc_thresh3)
			goto out_entries;
	}

	n = kmem_cache_zalloc(tbl->kmem_cachep, GFP_ATOMIC);
	if (!n)
		goto out_entries;

	skb_queue_head_init(&n->arp_queue);
	rwlock_init(&n->lock);
	n->updated	  = n->used = now;
	n->nud_state	  = NUD_NONE;
	n->output	  = neigh_blackhole;
	n->parms	  = neigh_parms_clone(&tbl->parms);
	setup_timer(&n->timer, neigh_timer_handler, (unsigned long)n);

	NEIGH_CACHE_STAT_INC(tbl, allocs);
	n->tbl		  = tbl;
	atomic_set(&n->refcnt, 1);
	n->dead		  = 1;
out:
	return n;

out_entries:
	atomic_dec(&tbl->entries);
	goto out;
}