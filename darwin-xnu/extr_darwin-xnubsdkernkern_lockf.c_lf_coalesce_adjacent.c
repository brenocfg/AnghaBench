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
struct lockf {scalar_t__ lf_id; scalar_t__ lf_type; int lf_end; int lf_start; struct lockf* lf_next; struct lockf** lf_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (struct lockf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LF_DBG_LIST ; 
 int /*<<< orphan*/  LOCKF_DEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_LOCKF ; 
 struct lockf* NOLOCKF ; 
 int /*<<< orphan*/  lf_move_blocked (struct lockf*,struct lockf*) ; 

__attribute__((used)) static void
lf_coalesce_adjacent(struct lockf *lock)
{
	struct lockf **lf = lock->lf_head;

	while (*lf != NOLOCKF) {
		/* reject locks that obviously could not be coalesced */
		if ((*lf == lock) ||
		    ((*lf)->lf_id != lock->lf_id) ||
		    ((*lf)->lf_type != lock->lf_type)) {
			lf = &(*lf)->lf_next;
			continue;
		}

		/*
		 * NOTE: Assumes that if two locks are adjacent on the number line 
		 * and belong to the same owner, then they are adjacent on the list.
		 */
		if ((*lf)->lf_end != -1 &&
		    ((*lf)->lf_end + 1) == lock->lf_start) {
			struct lockf *adjacent = *lf;

			LOCKF_DEBUG(LF_DBG_LIST, "lf_coalesce_adjacent: coalesce adjacent previous\n");
			lock->lf_start = (*lf)->lf_start;
			*lf = lock;
			lf = &(*lf)->lf_next;

			lf_move_blocked(lock, adjacent);

			FREE(adjacent, M_LOCKF);
			continue;
		}
		/* If the lock starts adjacent to us, we can coalesce it */
		if (lock->lf_end != -1 &&
		    (lock->lf_end + 1) == (*lf)->lf_start) {
			struct lockf *adjacent = *lf;

			LOCKF_DEBUG(LF_DBG_LIST, "lf_coalesce_adjacent: coalesce adjacent following\n");
			lock->lf_end = (*lf)->lf_end;
			lock->lf_next = (*lf)->lf_next;
			lf = &lock->lf_next;

			lf_move_blocked(lock, adjacent);

			FREE(adjacent, M_LOCKF);
			continue;
		}

		/* no matching conditions; go on to next lock */
		lf = &(*lf)->lf_next;
	}
}