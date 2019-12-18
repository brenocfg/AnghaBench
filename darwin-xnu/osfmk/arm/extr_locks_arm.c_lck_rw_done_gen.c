#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  TYPE_1__* thread_t ;
struct TYPE_7__ {int data; int shared_count; scalar_t__ r_waiting; scalar_t__ w_waiting; scalar_t__ priv_excl; } ;
typedef  TYPE_2__ lck_rw_word_t ;
typedef  scalar_t__ lck_rw_type_t ;
typedef  int /*<<< orphan*/  lck_rw_t ;
struct TYPE_6__ {int sched_flags; int /*<<< orphan*/  rwlock_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_RW_READER_EVENT (int /*<<< orphan*/ *) ; 
 scalar_t__ LCK_RW_TYPE_EXCLUSIVE ; 
 scalar_t__ LCK_RW_TYPE_SHARED ; 
 int /*<<< orphan*/  LCK_RW_WRITER_EVENT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOCKSTAT_RECORD (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  LS_LCK_RW_DONE_RELEASE ; 
 int TH_SFLAG_RW_PROMOTED ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  lck_rw_clear_promotion (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unslide_for_kdebug (int /*<<< orphan*/ *) ; 

__attribute__((used)) static lck_rw_type_t
lck_rw_done_gen(
	lck_rw_t	*lck,
	uint32_t	prior_lock_state)
{
	lck_rw_word_t	fake_lck;
	lck_rw_type_t	lock_type;
	thread_t		thread;
	uint32_t		rwlock_count;

	/*
	 * prior_lock state is a snapshot of the 1st word of the
	 * lock in question... we'll fake up a pointer to it
	 * and carefully not access anything beyond whats defined
	 * in the first word of a lck_rw_t
	 */
	fake_lck.data = prior_lock_state;

	if (fake_lck.shared_count <= 1) {
		if (fake_lck.w_waiting)
			thread_wakeup(LCK_RW_WRITER_EVENT(lck));

		if (!(fake_lck.priv_excl && fake_lck.w_waiting) && fake_lck.r_waiting)
			thread_wakeup(LCK_RW_READER_EVENT(lck));
	}
	if (fake_lck.shared_count)
		lock_type = LCK_RW_TYPE_SHARED;
	else
		lock_type = LCK_RW_TYPE_EXCLUSIVE;

	/* Check if dropping the lock means that we need to unpromote */
	thread = current_thread();
	rwlock_count = thread->rwlock_count--;
#if MACH_LDEBUG
	if (rwlock_count == 0)
		panic("rw lock count underflow for thread %p", thread);
#endif
	if ((rwlock_count == 1 /* field now 0 */) && (thread->sched_flags & TH_SFLAG_RW_PROMOTED)) {
		/* sched_flags checked without lock, but will be rechecked while clearing */
		lck_rw_clear_promotion(thread, unslide_for_kdebug(lck));
	}
#if CONFIG_DTRACE
	LOCKSTAT_RECORD(LS_LCK_RW_DONE_RELEASE, lck, lock_type == LCK_RW_TYPE_SHARED ? 0 : 1);
#endif
	return lock_type;
}