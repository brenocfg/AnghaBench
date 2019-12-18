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
struct lockf {scalar_t__ lf_type; scalar_t__ lf_boosted; int /*<<< orphan*/  lf_end; int /*<<< orphan*/  lf_start; struct lockf* lf_next; struct lockf** lf_head; } ;
typedef  int overlap_t ;

/* Variables and functions */
 int ENOLCK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FREE (struct lockf*,int /*<<< orphan*/ ) ; 
 scalar_t__ F_UNLCK ; 
 scalar_t__ LF_BOOSTED ; 
 int LF_DBG_LOCKOP ; 
 int /*<<< orphan*/  M_LOCKF ; 
 struct lockf* NOLOCKF ; 
#define  OVERLAP_CONTAINED_BY_LOCK 133 
#define  OVERLAP_CONTAINS_LOCK 132 
#define  OVERLAP_ENDS_AFTER_LOCK 131 
#define  OVERLAP_EQUALS_LOCK 130 
#define  OVERLAP_NONE 129 
#define  OVERLAP_STARTS_BEFORE_LOCK 128 
 int /*<<< orphan*/  SELF ; 
 int /*<<< orphan*/  lf_drop_assertion (struct lockf*) ; 
 int lf_findoverlap (struct lockf*,struct lockf*,int /*<<< orphan*/ ,struct lockf***,struct lockf**) ; 
 int /*<<< orphan*/  lf_print (char*,struct lockf*) ; 
 int /*<<< orphan*/  lf_printlist (char*,struct lockf*) ; 
 int /*<<< orphan*/  lf_split (struct lockf*,struct lockf*) ; 
 int /*<<< orphan*/  lf_wakelock (struct lockf*,int /*<<< orphan*/ ) ; 
 int lockf_debug ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static int
lf_clearlock(struct lockf *unlock)
{
	struct lockf **head = unlock->lf_head;
	struct lockf *lf = *head;
	struct lockf *overlap, **prev;
	overlap_t ovcase;

	if (lf == NOLOCKF)
		return (0);
#ifdef LOCKF_DEBUGGING
	if (unlock->lf_type != F_UNLCK)
		panic("lf_clearlock: bad type");
	if (lockf_debug & LF_DBG_LOCKOP)
		lf_print("lf_clearlock", unlock);
#endif /* LOCKF_DEBUGGING */
	prev = head;
	while ((ovcase = lf_findoverlap(lf, unlock, SELF, &prev, &overlap)) != OVERLAP_NONE) {
		/*
		 * Wakeup the list of locks to be retried.
		 */
	        lf_wakelock(overlap, FALSE);
#if IMPORTANCE_INHERITANCE
		if (overlap->lf_boosted == LF_BOOSTED) {
			lf_drop_assertion(overlap);
		}
#endif /* IMPORTANCE_INHERITANCE */

		switch (ovcase) {
		case OVERLAP_NONE:	/* satisfy compiler enum/switch */
			break;

		case OVERLAP_EQUALS_LOCK:
			*prev = overlap->lf_next;
			FREE(overlap, M_LOCKF);
			break;

		case OVERLAP_CONTAINS_LOCK: /* split it */
			if (overlap->lf_start == unlock->lf_start) {
				overlap->lf_start = unlock->lf_end + 1;
				break;
			}
			/*
			 * If we can't split the lock, we can't grant it.
			 * Claim a system limit for the resource shortage.
			 */
			if (lf_split(overlap, unlock))
				return (ENOLCK);
			overlap->lf_next = unlock->lf_next;
			break;

		case OVERLAP_CONTAINED_BY_LOCK:
			*prev = overlap->lf_next;
			lf = overlap->lf_next;
			FREE(overlap, M_LOCKF);
			continue;

		case OVERLAP_STARTS_BEFORE_LOCK:
			overlap->lf_end = unlock->lf_start - 1;
			prev = &overlap->lf_next;
			lf = overlap->lf_next;
			continue;

		case OVERLAP_ENDS_AFTER_LOCK:
			overlap->lf_start = unlock->lf_end + 1;
			break;
		}
		break;
	}
#ifdef LOCKF_DEBUGGING
	if (lockf_debug & LF_DBG_LOCKOP)
		lf_printlist("lf_clearlock", unlock);
#endif /* LOCKF_DEBUGGING */
	return (0);
}