#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  TYPE_1__* thread_t ;
struct TYPE_11__ {int lck_rw_shared_count; int /*<<< orphan*/  lck_rw_want_upgrade; scalar_t__ lck_w_waiting; } ;
typedef  TYPE_2__ lck_rw_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_10__ {int sched_flags; int /*<<< orphan*/  rwlock_count; } ;

/* Variables and functions */
 int DBG_FUNC_NONE ; 
 int /*<<< orphan*/  DBG_MACH_LOCKS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_RW_LCK_SH_TO_EX_CODE ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RW_LOCK_WRITER_EVENT (TYPE_2__*) ; 
 int TH_SFLAG_RW_PROMOTED ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE_OR_PERM (TYPE_2__*) ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  lck_rw_clear_promotion (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unslide_for_kdebug (TYPE_2__*) ; 

__attribute__((used)) static boolean_t
lck_rw_lock_shared_to_exclusive_failure(
	lck_rw_t	*lck,
	uint32_t	prior_lock_state)
{
	lck_rw_t	*fake_lck;
	thread_t	thread = current_thread();
	uint32_t	rwlock_count;

	/* Check if dropping the lock means that we need to unpromote */
	rwlock_count = thread->rwlock_count--;
#if MACH_LDEBUG
	if (rwlock_count == 0) {
		panic("rw lock count underflow for thread %p", thread);
	}
#endif
	fake_lck = (lck_rw_t *)&prior_lock_state;

	if (fake_lck->lck_w_waiting && fake_lck->lck_rw_shared_count == 1) {
		/*
		 *	Someone else has requested upgrade.
		 *	Since we've released the read lock, wake
		 *	him up if he's blocked waiting
		 */
		thread_wakeup(RW_LOCK_WRITER_EVENT(lck));
	}

	if ((rwlock_count == 1 /* field now 0 */) && (thread->sched_flags & TH_SFLAG_RW_PROMOTED)) {
		/* sched_flags checked without lock, but will be rechecked while clearing */
		lck_rw_clear_promotion(thread, unslide_for_kdebug(lck));
	}

	KERNEL_DEBUG(MACHDBG_CODE(DBG_MACH_LOCKS, LCK_RW_LCK_SH_TO_EX_CODE) | DBG_FUNC_NONE,
		     VM_KERNEL_UNSLIDE_OR_PERM(lck), lck->lck_rw_shared_count, lck->lck_rw_want_upgrade, 0, 0);

	return (FALSE);
}