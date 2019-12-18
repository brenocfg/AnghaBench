#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  TYPE_1__* thread_t ;
typedef  int /*<<< orphan*/  spl_t ;
typedef  int ast_t ;
struct TYPE_17__ {int state; int sched_flags; scalar_t__ promotions; scalar_t__ was_promoted_on_wakeup; scalar_t__ rwlock_count; int /*<<< orphan*/ * waiting_for_mutex; int /*<<< orphan*/  kevent_ast_bits; } ;

/* Variables and functions */
 int AST_APC ; 
 int AST_BSD ; 
 int AST_DTRACE ; 
 int AST_GUARD ; 
 int AST_KEVENT ; 
 int AST_KPERF ; 
 int AST_LEDGER ; 
 int AST_MACF ; 
 int AST_PER_THREAD ; 
 int AST_PREEMPT ; 
 int AST_PREEMPTION ; 
 int AST_QUANTUM ; 
 int AST_SFI ; 
 int AST_TELEMETRY_ALL ; 
 int AST_UNQUIESCE ; 
 scalar_t__ AST_URGENT ; 
 scalar_t__ FALSE ; 
 int TH_IDLE ; 
 int TH_SFLAG_DEPRESS ; 
 int TH_SFLAG_EXEC_PROMOTED ; 
 int TH_SFLAG_PROMOTED ; 
 int TH_SFLAG_RW_PROMOTED ; 
 int TH_SFLAG_WAITQ_PROMOTED ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int ast_consume (int) ; 
 scalar_t__ ast_peek (scalar_t__) ; 
 int /*<<< orphan*/  ast_propagate (TYPE_1__*) ; 
 scalar_t__ atomic_exchange (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bsd_ast (TYPE_1__*) ; 
 int /*<<< orphan*/  c_ast_taken_block ; 
 int /*<<< orphan*/  counter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_quiescent_counter_assert_ast () ; 
 int /*<<< orphan*/  cpu_quiescent_counter_ast () ; 
 int csw_check (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  current_processor () ; 
 TYPE_1__* current_thread () ; 
 int /*<<< orphan*/  dtrace_ast () ; 
 int /*<<< orphan*/  guard_ast (TYPE_1__*) ; 
 int /*<<< orphan*/  kevent_ast (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  kperf_kpc_thread_ast (TYPE_1__*) ; 
 int /*<<< orphan*/  ledger_ast (TYPE_1__*) ; 
 int /*<<< orphan*/  mac_thread_userret (TYPE_1__*) ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sfi_ast (TYPE_1__*) ; 
 int /*<<< orphan*/  splsched () ; 
 int /*<<< orphan*/  splx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  telemetry_ast (TYPE_1__*,int) ; 
 int /*<<< orphan*/  thread_apc_ast (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_ast_clear (TYPE_1__*,int) ; 
 int /*<<< orphan*/  thread_block_reason (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  thread_lock (TYPE_1__*) ; 
 int /*<<< orphan*/  thread_preempted ; 
 int /*<<< orphan*/  thread_unlock (TYPE_1__*) ; 
 int waitq_wait_possible (TYPE_1__*) ; 

void
ast_taken_user(void)
{
	assert(ml_get_interrupts_enabled() == FALSE);

	thread_t thread = current_thread();

	/* We are about to return to userspace, there must not be a pending wait */
	assert(waitq_wait_possible(thread));
	assert((thread->state & TH_IDLE) == 0);

	/* TODO: Add more 'return to userspace' assertions here */

	/*
	 * If this thread was urgently preempted in userspace,
	 * take the preemption before processing the ASTs.
	 * The trap handler will call us again if we have more ASTs, so it's
	 * safe to block in a continuation here.
	 */
	if (ast_peek(AST_URGENT) == AST_URGENT) {
		ast_t urgent_reason = ast_consume(AST_PREEMPTION);

		assert(urgent_reason & AST_PREEMPT);

		/* TODO: Should we csw_check again to notice if conditions have changed? */

		thread_block_reason(thread_preempted, NULL, urgent_reason);
		/* NOTREACHED */
	}

	/*
	 * AST_KEVENT does not send an IPI when setting the ast for a thread running in parallel
	 * on a different processor. Only the ast bit on the thread will be set.
	 *
	 * Force a propagate for concurrent updates without an IPI.
	 */
	ast_propagate(thread);

	/*
	 * Consume all non-preemption processor ASTs matching reasons
	 * because we're handling them here.
	 *
	 * If one of the AST handlers blocks in a continuation,
	 * we'll reinstate the unserviced thread-level AST flags
	 * from the thread to the processor on context switch.
	 * If one of the AST handlers sets another AST,
	 * the trap handler will call ast_taken_user again.
	 *
	 * We expect the AST handlers not to thread_exception_return
	 * without an ast_propagate or context switch to reinstate
	 * the per-processor ASTs.
	 *
	 * TODO: Why are AST_DTRACE and AST_KPERF not per-thread ASTs?
	 */
	ast_t reasons = ast_consume(AST_PER_THREAD | AST_KPERF | AST_DTRACE);

	ml_set_interrupts_enabled(TRUE);

#if CONFIG_DTRACE
	if (reasons & AST_DTRACE) {
		dtrace_ast();
	}
#endif

#ifdef MACH_BSD
	if (reasons & AST_BSD) {
		thread_ast_clear(thread, AST_BSD);
		bsd_ast(thread);
	}
#endif

#if CONFIG_MACF
	if (reasons & AST_MACF) {
		thread_ast_clear(thread, AST_MACF);
		mac_thread_userret(thread);
	}
#endif

	if (reasons & AST_APC) {
		thread_ast_clear(thread, AST_APC);
		thread_apc_ast(thread);
	}

	if (reasons & AST_GUARD) {
		thread_ast_clear(thread, AST_GUARD);
		guard_ast(thread);
	}

	if (reasons & AST_LEDGER) {
		thread_ast_clear(thread, AST_LEDGER);
		ledger_ast(thread);
	}

	if (reasons & AST_KPERF) {
		thread_ast_clear(thread, AST_KPERF);
		kperf_kpc_thread_ast(thread);
	}

	if (reasons & AST_KEVENT) {
		thread_ast_clear(thread, AST_KEVENT);
		uint16_t bits = atomic_exchange(&thread->kevent_ast_bits, 0);
		if (bits) kevent_ast(thread, bits);
	}

#if CONFIG_TELEMETRY
	if (reasons & AST_TELEMETRY_ALL) {
		ast_t telemetry_reasons = reasons & AST_TELEMETRY_ALL;
		thread_ast_clear(thread, AST_TELEMETRY_ALL);
		telemetry_ast(thread, telemetry_reasons);
	}
#endif

	spl_t s = splsched();

#if CONFIG_SCHED_SFI
	/*
	 * SFI is currently a per-processor AST, not a per-thread AST
	 *      TODO: SFI should be a per-thread AST
	 */
	if (ast_consume(AST_SFI) == AST_SFI) {
		sfi_ast(thread);
	}
#endif

	/* We are about to return to userspace, there must not be a pending wait */
	assert(waitq_wait_possible(thread));

	/*
	 * We've handled all per-thread ASTs, time to handle non-urgent preemption.
	 *
	 * We delay reading the preemption bits until now in case the thread
	 * blocks while handling per-thread ASTs.
	 *
	 * If one of the AST handlers had managed to set a new AST bit,
	 * thread_exception_return will call ast_taken again.
	 */
	ast_t preemption_reasons = ast_consume(AST_PREEMPTION);

	if (preemption_reasons & AST_PREEMPT) {
		/* Conditions may have changed from when the AST_PREEMPT was originally set, so re-check. */

		thread_lock(thread);
		preemption_reasons = csw_check(current_processor(), (preemption_reasons & AST_QUANTUM));
		thread_unlock(thread);

#if CONFIG_SCHED_SFI
		/* csw_check might tell us that SFI is needed */
		if (preemption_reasons & AST_SFI) {
			sfi_ast(thread);
		}
#endif

		if (preemption_reasons & AST_PREEMPT) {
			counter(c_ast_taken_block++);
			/* switching to a continuation implicitly re-enables interrupts */
			thread_block_reason(thread_preempted, NULL, preemption_reasons);
			/* NOTREACHED */
		}
	}

	if (ast_consume(AST_UNQUIESCE) == AST_UNQUIESCE) {
		cpu_quiescent_counter_ast();
	}

	cpu_quiescent_counter_assert_ast();

	splx(s);

	/*
	 * Here's a good place to put assertions of things which must be true
	 * upon return to userspace.
	 */
	assert((thread->sched_flags & TH_SFLAG_WAITQ_PROMOTED) == 0);
	assert((thread->sched_flags & TH_SFLAG_RW_PROMOTED) == 0);
	assert((thread->sched_flags & TH_SFLAG_EXEC_PROMOTED) == 0);
	assert((thread->sched_flags & TH_SFLAG_PROMOTED) == 0);
	assert((thread->sched_flags & TH_SFLAG_DEPRESS) == 0);

	assert(thread->promotions == 0);
	assert(thread->was_promoted_on_wakeup == 0);
	assert(thread->waiting_for_mutex == NULL);
	assert(thread->rwlock_count == 0);
}