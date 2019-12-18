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
struct dlm_lock_resource {int state; scalar_t__ inflight_locks; int /*<<< orphan*/  refmap; int /*<<< orphan*/  dirty; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DLM_LOCK_RES_DIRTY ; 
 int O2NM_MAX_NODES ; 
 int /*<<< orphan*/  __dlm_lockres_has_locks (struct dlm_lock_resource*) ; 
 int find_next_bit (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

int __dlm_lockres_unused(struct dlm_lock_resource *res)
{
	if (!__dlm_lockres_has_locks(res) &&
	    (list_empty(&res->dirty) && !(res->state & DLM_LOCK_RES_DIRTY))) {
		/* try not to scan the bitmap unless the first two
		 * conditions are already true */
		int bit = find_next_bit(res->refmap, O2NM_MAX_NODES, 0);
		if (bit >= O2NM_MAX_NODES) {
			/* since the bit for dlm->node_num is not
			 * set, inflight_locks better be zero */
			BUG_ON(res->inflight_locks != 0);
			return 1;
		}
	}
	return 0;
}