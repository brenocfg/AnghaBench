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
struct stripe {int /*<<< orphan*/  key; int /*<<< orphan*/  cnt; struct list_head* lists; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DEL_LIST (struct list_head*) ; 
 int LIST_LRU ; 
 int /*<<< orphan*/  WRITE ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int stripe_lock (struct stripe*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stripe_ref (struct stripe*) ; 

__attribute__((used)) static int stripe_get(struct stripe *stripe)
{
	int r;
	struct list_head *lh = stripe->lists + LIST_LRU;

	/* Delete stripe from LRU (inactive) list if on. */
	DEL_LIST(lh);
	BUG_ON(stripe_ref(stripe) < 0);

	/* Lock stripe on first reference */
	r = (atomic_inc_return(&stripe->cnt) == 1) ?
	    stripe_lock(stripe, WRITE, stripe->key) : 0;

	return r;
}