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
struct TYPE_3__ {int /*<<< orphan*/  plist; } ;
struct futex_q {int /*<<< orphan*/  key; int /*<<< orphan*/  lock_ptr; int /*<<< orphan*/ * pi_state; TYPE_1__ list; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drop_futex_key_refs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_pi_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plist_del (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  plist_node_empty (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unqueue_me_pi(struct futex_q *q)
{
	WARN_ON(plist_node_empty(&q->list));
	plist_del(&q->list, &q->list.plist);

	BUG_ON(!q->pi_state);
	free_pi_state(q->pi_state);
	q->pi_state = NULL;

	spin_unlock(q->lock_ptr);

	drop_futex_key_refs(&q->key);
}