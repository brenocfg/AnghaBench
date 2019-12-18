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
struct lockf {int lf_start; int lf_end; scalar_t__ lf_id; struct lockf* lf_next; } ;
typedef  int /*<<< orphan*/  overlap_t ;
typedef  int off_t ;

/* Variables and functions */
 int LF_DBG_LIST ; 
 int /*<<< orphan*/  LOCKF_DEBUG (int,char*) ; 
 struct lockf* NOLOCKF ; 
 int OTHERS ; 
 int /*<<< orphan*/  OVERLAP_CONTAINED_BY_LOCK ; 
 int /*<<< orphan*/  OVERLAP_CONTAINS_LOCK ; 
 int /*<<< orphan*/  OVERLAP_ENDS_AFTER_LOCK ; 
 int /*<<< orphan*/  OVERLAP_EQUALS_LOCK ; 
 int /*<<< orphan*/  OVERLAP_NONE ; 
 int /*<<< orphan*/  OVERLAP_STARTS_BEFORE_LOCK ; 
 int SELF ; 
 int /*<<< orphan*/  lf_print (char*,struct lockf*) ; 
 int lockf_debug ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static overlap_t
lf_findoverlap(struct lockf *lf, struct lockf *lock, int type,
	       struct lockf ***prev, struct lockf **overlap)
{
	off_t start, end;
	int found_self = 0;

	*overlap = lf;
	if (lf == NOLOCKF)
		return (0);
#ifdef LOCKF_DEBUGGING
	if (lockf_debug & LF_DBG_LIST)
		lf_print("lf_findoverlap: looking for overlap in", lock);
#endif /* LOCKF_DEBUGGING */
	start = lock->lf_start;
	end = lock->lf_end;
	while (lf != NOLOCKF) {
		if (((type & SELF) && lf->lf_id != lock->lf_id) ||
		    ((type & OTHERS) && lf->lf_id == lock->lf_id)) {
			/* 
			 * Locks belonging to one process are adjacent on the
			 * list, so if we've found any locks belonging to us,
			 * and we're now seeing something else, then we've
			 * examined all "self" locks.  Note that bailing out
			 * here is quite important; for coalescing, we assume 
			 * numerically adjacent locks from the same owner to 
			 * be adjacent on the list.
			 */
			if ((type & SELF) && found_self) {
				return OVERLAP_NONE;
			}

			*prev = &lf->lf_next;
			*overlap = lf = lf->lf_next;
			continue;
		}

		if ((type & SELF)) {
			found_self = 1;
		}

#ifdef LOCKF_DEBUGGING
		if (lockf_debug & LF_DBG_LIST)
			lf_print("\tchecking", lf);
#endif /* LOCKF_DEBUGGING */
		/*
		 * OK, check for overlap
		 */
		if ((lf->lf_end != -1 && start > lf->lf_end) ||
		    (end != -1 && lf->lf_start > end)) {
			/* Case 0 */
			LOCKF_DEBUG(LF_DBG_LIST, "no overlap\n");

			/*
			 * NOTE: assumes that locks for the same process are 
			 * nonintersecting and ordered.
			 */
			if ((type & SELF) && end != -1 && lf->lf_start > end)
				return (OVERLAP_NONE);
			*prev = &lf->lf_next;
			*overlap = lf = lf->lf_next;
			continue;
		}
		if ((lf->lf_start == start) && (lf->lf_end == end)) {
			LOCKF_DEBUG(LF_DBG_LIST, "overlap == lock\n");
			return (OVERLAP_EQUALS_LOCK);
		}
		if ((lf->lf_start <= start) &&
		    (end != -1) &&
		    ((lf->lf_end >= end) || (lf->lf_end == -1))) {
			LOCKF_DEBUG(LF_DBG_LIST, "overlap contains lock\n");
			return (OVERLAP_CONTAINS_LOCK);
		}
		if (start <= lf->lf_start &&
		           (end == -1 ||
			   (lf->lf_end != -1 && end >= lf->lf_end))) {
			LOCKF_DEBUG(LF_DBG_LIST, "lock contains overlap\n");
			return (OVERLAP_CONTAINED_BY_LOCK);
		}
		if ((lf->lf_start < start) &&
			((lf->lf_end >= start) || (lf->lf_end == -1))) {
			LOCKF_DEBUG(LF_DBG_LIST, "overlap starts before lock\n");
			return (OVERLAP_STARTS_BEFORE_LOCK);
		}
		if ((lf->lf_start > start) &&
			(end != -1) &&
			((lf->lf_end > end) || (lf->lf_end == -1))) {
			LOCKF_DEBUG(LF_DBG_LIST, "overlap ends after lock\n");
			return (OVERLAP_ENDS_AFTER_LOCK);
		}
		panic("lf_findoverlap: default");
	}
	return (OVERLAP_NONE);
}