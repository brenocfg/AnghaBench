#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_37__   TYPE_3__ ;
typedef  struct TYPE_36__   TYPE_30__ ;
typedef  struct TYPE_35__   TYPE_2__ ;
typedef  struct TYPE_34__   TYPE_20__ ;
typedef  struct TYPE_33__   TYPE_1__ ;
typedef  struct TYPE_32__   TYPE_14__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  TYPE_2__* thread_t ;
typedef  int sched_options_t ;
typedef  TYPE_3__* processor_t ;
typedef  scalar_t__ int64_t ;
typedef  void* boolean_t ;
typedef  int ast_t ;
struct TYPE_37__ {scalar_t__ last_dispatch; scalar_t__ quantum_end; scalar_t__ starting_pri; void* first_timeslice; int /*<<< orphan*/  quantum_timer; } ;
struct TYPE_36__ {int /*<<< orphan*/  cpu_time; } ;
struct TYPE_33__ {int /*<<< orphan*/  deadline; } ;
struct TYPE_35__ {scalar_t__ kernel_stack; int state; scalar_t__ quantum_remaining; int reason; scalar_t__ t_deduct_bank_ledger_time; scalar_t__ rwlock_count; scalar_t__ sched_pri; scalar_t__ sched_mode; scalar_t__ computation_epoch; scalar_t__ last_made_runnable_time; scalar_t__ last_basepri_change_time; scalar_t__ same_pri_latency; scalar_t__ block_hint; void* wake_active; int /*<<< orphan*/  (* sched_call ) (int /*<<< orphan*/ ,TYPE_2__*) ;int /*<<< orphan*/  chosen_processor; int /*<<< orphan*/  runnable_timer; int /*<<< orphan*/  computation_metered; TYPE_1__ realtime; scalar_t__ t_bankledger; scalar_t__ t_threadledger; scalar_t__ t_ledger; int /*<<< orphan*/ * continuation; TYPE_3__* last_processor; } ;
struct TYPE_34__ {int /*<<< orphan*/  cpu_time; } ;
struct TYPE_32__ {int /*<<< orphan*/  cpu_time; } ;

/* Variables and functions */
 int AST_HANDOFF ; 
 int AST_LEDGER ; 
 int AST_NONE ; 
 int AST_PREEMPT ; 
 int AST_QUANTUM ; 
 int AST_REBALANCE ; 
 int DBG_FUNC_NONE ; 
 int /*<<< orphan*/  DBG_MACH_SCHED ; 
 void* FALSE ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,uintptr_t,int,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_DISPATCH ; 
 int /*<<< orphan*/  PROCESSOR_NULL ; 
 int /*<<< orphan*/  SCHED_CALL_BLOCK ; 
 int SCHED_HEADQ ; 
 int SCHED_NONE ; 
 int SCHED_PREEMPT ; 
 int SCHED_REBALANCE ; 
 int SCHED_TAILQ ; 
 scalar_t__ THREAD_NOT_RUNNABLE ; 
 TYPE_2__* THREAD_NULL ; 
 int THREAD_URGENCY_NONE ; 
 size_t TH_BUCKET_RUN ; 
 int TH_IDLE ; 
 scalar_t__ TH_MODE_REALTIME ; 
 int TH_RUN ; 
 int TH_TERMINATE ; 
 int TH_TERMINATE2 ; 
 int TH_WAIT ; 
 int TH_WAIT_REPORT ; 
 void* TRUE ; 
 int /*<<< orphan*/  UINT64_MAX ; 
 scalar_t__ __improbable (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  assertf (int,char*,scalar_t__,scalar_t__) ; 
 TYPE_30__ bank_ledgers ; 
 TYPE_3__* current_processor () ; 
 TYPE_2__* current_thread_volatile () ; 
 scalar_t__ kThreadWaitNone ; 
 int /*<<< orphan*/  lck_rw_set_promotion_locked (TYPE_2__*) ; 
 int /*<<< orphan*/  ledger_credit_thread (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  machine_thread_going_off_core (TYPE_2__*,void*,scalar_t__) ; 
 int /*<<< orphan*/  machine_thread_going_on_core (TYPE_2__*,int,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__* sched_run_buckets ; 
 scalar_t__ sched_run_decr (TYPE_2__*) ; 
 int /*<<< orphan*/  stack_free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_20__ task_ledgers ; 
 int /*<<< orphan*/  thread_csw_callout (TYPE_2__*,TYPE_2__*,scalar_t__) ; 
 int thread_get_urgency (TYPE_2__*,scalar_t__*,scalar_t__*) ; 
 TYPE_14__ thread_ledgers ; 
 int /*<<< orphan*/  thread_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  thread_quantum_init (TYPE_2__*) ; 
 int /*<<< orphan*/  thread_setrun (TYPE_2__*,int) ; 
 int /*<<< orphan*/  thread_tell_urgency (int,scalar_t__,scalar_t__,scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  thread_terminate_enqueue (TYPE_2__*) ; 
 scalar_t__ thread_tid (TYPE_2__*) ; 
 int /*<<< orphan*/  thread_unlock (TYPE_2__*) ; 
 int /*<<< orphan*/  thread_wakeup (void**) ; 
 int /*<<< orphan*/  timer_call_quantum_timer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_call_quantum_timer_enter (int /*<<< orphan*/ *,TYPE_2__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  timer_stop (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  wake_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  wake_unlock (TYPE_2__*) ; 

void
thread_dispatch(
	thread_t		thread,
	thread_t		self)
{
	processor_t		processor = self->last_processor;

	assert(processor == current_processor());
	assert(self == current_thread_volatile());
	assert(thread != self);

	if (thread != THREAD_NULL) {
		/* 
		 * Do the perfcontrol callout for context switch. 
		 * The reason we do this here is:
		 * - thread_dispatch() is called from various places that are not 
		 *   the direct context switch path for eg. processor shutdown etc.
		 *   So adding the callout here covers all those cases.
		 * - We want this callout as early as possible to be close 
		 *   to the timestamp taken in thread_invoke()
		 * - We want to avoid holding the thread lock while doing the 
		 *   callout
		 * - We do not want to callout if "thread" is NULL.
		 */
		thread_csw_callout(thread, self, processor->last_dispatch);	

#if KASAN
		if (thread->continuation != NULL) {
			/*
			 * Thread has a continuation and the normal stack is going away.
			 * Unpoison the stack and mark all fakestack objects as unused.
			 */
			kasan_fakestack_drop(thread);
			if (thread->kernel_stack) {
				kasan_unpoison_stack(thread->kernel_stack, kernel_stack_size);
			}
		}

		/*
		 * Free all unused fakestack objects.
		 */
		kasan_fakestack_gc(thread);
#endif

		/*
		 *	If blocked at a continuation, discard
		 *	the stack.
		 */
		if (thread->continuation != NULL && thread->kernel_stack != 0)
			stack_free(thread);

		if (thread->state & TH_IDLE) {
			KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
			        MACHDBG_CODE(DBG_MACH_SCHED,MACH_DISPATCH) | DBG_FUNC_NONE,
			        (uintptr_t)thread_tid(thread), 0, thread->state,
			        sched_run_buckets[TH_BUCKET_RUN], 0);
		} else {
			int64_t consumed;
			int64_t remainder = 0;

			if (processor->quantum_end > processor->last_dispatch)
				remainder = processor->quantum_end -
				    processor->last_dispatch;

			consumed = thread->quantum_remaining - remainder;

			if ((thread->reason & AST_LEDGER) == 0) {
				/*
				 * Bill CPU time to both the task and
				 * the individual thread.
				 */
				ledger_credit_thread(thread, thread->t_ledger,
				                     task_ledgers.cpu_time, consumed);
				ledger_credit_thread(thread, thread->t_threadledger,
				                     thread_ledgers.cpu_time, consumed);
				if (thread->t_bankledger) {
					ledger_credit_thread(thread, thread->t_bankledger,
					                     bank_ledgers.cpu_time,
					                     (consumed - thread->t_deduct_bank_ledger_time));
				}
				thread->t_deduct_bank_ledger_time = 0;
			}

			wake_lock(thread);
			thread_lock(thread);

			/*
			 * Apply a priority floor if the thread holds a kernel resource
			 * Do this before checking starting_pri to avoid overpenalizing
			 * repeated rwlock blockers.
			 */
			if (__improbable(thread->rwlock_count != 0))
				lck_rw_set_promotion_locked(thread);

			boolean_t keep_quantum = processor->first_timeslice;

			/*
			 * Treat a thread which has dropped priority since it got on core
			 * as having expired its quantum.
			 */
			if (processor->starting_pri > thread->sched_pri)
				keep_quantum = FALSE;

			/* Compute remainder of current quantum. */
			if (keep_quantum &&
			    processor->quantum_end > processor->last_dispatch)
				thread->quantum_remaining = (uint32_t)remainder;
			else
				thread->quantum_remaining = 0;

			if (thread->sched_mode == TH_MODE_REALTIME) {
				/*
				 *	Cancel the deadline if the thread has
				 *	consumed the entire quantum.
				 */
				if (thread->quantum_remaining == 0) {
					thread->realtime.deadline = UINT64_MAX;
				}
			} else {
#if defined(CONFIG_SCHED_TIMESHARE_CORE)
				/*
				 *	For non-realtime threads treat a tiny
				 *	remaining quantum as an expired quantum
				 *	but include what's left next time.
				 */
				if (thread->quantum_remaining < min_std_quantum) {
					thread->reason |= AST_QUANTUM;
					thread->quantum_remaining += SCHED(initial_quantum_size)(thread);
				}
#endif /* CONFIG_SCHED_TIMESHARE_CORE */
			}

			/*
			 *	If we are doing a direct handoff then
			 *	take the remainder of the quantum.
			 */
			if ((thread->reason & (AST_HANDOFF|AST_QUANTUM)) == AST_HANDOFF) {
				self->quantum_remaining = thread->quantum_remaining;
				thread->reason |= AST_QUANTUM;
				thread->quantum_remaining = 0;
			} else {
#if defined(CONFIG_SCHED_MULTIQ)
				if (SCHED(sched_groups_enabled) &&
				    thread->sched_group == self->sched_group) {
					KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
					    MACHDBG_CODE(DBG_MACH_SCHED, MACH_QUANTUM_HANDOFF),
					    self->reason, (uintptr_t)thread_tid(thread),
					    self->quantum_remaining, thread->quantum_remaining, 0);

					self->quantum_remaining = thread->quantum_remaining;
					thread->quantum_remaining = 0;
					/* Don't set AST_QUANTUM here - old thread might still want to preempt someone else */
				}
#endif /* defined(CONFIG_SCHED_MULTIQ) */
			}

			thread->computation_metered += (processor->last_dispatch - thread->computation_epoch);

			if (!(thread->state & TH_WAIT)) {
				/*
				 *	Still runnable.
				 */
				thread->last_made_runnable_time = thread->last_basepri_change_time = processor->last_dispatch;

				machine_thread_going_off_core(thread, FALSE, processor->last_dispatch);

				ast_t reason = thread->reason;
				sched_options_t options = SCHED_NONE;

				if (reason & AST_REBALANCE) {
					options |= SCHED_REBALANCE;
					if (reason & AST_QUANTUM) {
						/*
						 * Having gone to the trouble of forcing this thread off a less preferred core,
						 * we should force the preferable core to reschedule immediately to give this
						 * thread a chance to run instead of just sitting on the run queue where
						 * it may just be stolen back by the idle core we just forced it off.
						 * But only do this at the end of a quantum to prevent cascading effects.
						 */
						options |= SCHED_PREEMPT;
					}
				}

				if (reason & AST_QUANTUM)
					options |= SCHED_TAILQ;
				else if (reason & AST_PREEMPT)
					options |= SCHED_HEADQ;
				else
					options |= (SCHED_PREEMPT | SCHED_TAILQ);

				thread_setrun(thread, options);

				KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
				        MACHDBG_CODE(DBG_MACH_SCHED,MACH_DISPATCH) | DBG_FUNC_NONE,
				        (uintptr_t)thread_tid(thread), thread->reason, thread->state,
				        sched_run_buckets[TH_BUCKET_RUN], 0);

				if (thread->wake_active) {
					thread->wake_active = FALSE;
					thread_unlock(thread);

					thread_wakeup(&thread->wake_active);
				} else {
					thread_unlock(thread);
				}

				wake_unlock(thread);
			} else {
				/*
				 *	Waiting.
				 */
				boolean_t should_terminate = FALSE;
				uint32_t new_run_count;
				int thread_state = thread->state;

				/* Only the first call to thread_dispatch
				 * after explicit termination should add
				 * the thread to the termination queue
				 */
				if ((thread_state & (TH_TERMINATE|TH_TERMINATE2)) == TH_TERMINATE) {
					should_terminate = TRUE;
					thread_state |= TH_TERMINATE2;
				}

				timer_stop(&thread->runnable_timer, processor->last_dispatch);

				thread_state &= ~TH_RUN;
				thread->state = thread_state;

				thread->last_made_runnable_time = thread->last_basepri_change_time = THREAD_NOT_RUNNABLE;
				thread->chosen_processor = PROCESSOR_NULL;

				new_run_count = sched_run_decr(thread);

#if CONFIG_SCHED_SFI
				if (thread->reason & AST_SFI) {
					thread->wait_sfi_begin_time = processor->last_dispatch;
				}
#endif

				machine_thread_going_off_core(thread, should_terminate, processor->last_dispatch);

				KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
				        MACHDBG_CODE(DBG_MACH_SCHED,MACH_DISPATCH) | DBG_FUNC_NONE,
				        (uintptr_t)thread_tid(thread), thread->reason, thread_state,
				        new_run_count, 0);

				if (thread_state & TH_WAIT_REPORT) {
					(*thread->sched_call)(SCHED_CALL_BLOCK, thread);
				}

				if (thread->wake_active) {
					thread->wake_active = FALSE;
					thread_unlock(thread);

					thread_wakeup(&thread->wake_active);
				} else {
					thread_unlock(thread);
				}

				wake_unlock(thread);

				if (should_terminate)
					thread_terminate_enqueue(thread);
			}
		}
	}

	int urgency = THREAD_URGENCY_NONE;
	uint64_t latency = 0;

	/* Update (new) current thread and reprogram quantum timer */
	thread_lock(self);
	
	if (!(self->state & TH_IDLE)) {
		uint64_t        arg1, arg2;

#if CONFIG_SCHED_SFI
		ast_t			new_ast;

		new_ast = sfi_thread_needs_ast(self, NULL);

		if (new_ast != AST_NONE) {
			ast_on(new_ast);
		}
#endif

		assertf(processor->last_dispatch >= self->last_made_runnable_time,
		        "Non-monotonic time? dispatch at 0x%llx, runnable at 0x%llx",
		        processor->last_dispatch, self->last_made_runnable_time);

		assert(self->last_made_runnable_time <= self->last_basepri_change_time);

		latency = processor->last_dispatch - self->last_made_runnable_time;
		assert(latency >= self->same_pri_latency);

		urgency = thread_get_urgency(self, &arg1, &arg2);

		thread_tell_urgency(urgency, arg1, arg2, latency, self);

		/*
		 *	Get a new quantum if none remaining.
		 */
		if (self->quantum_remaining == 0) {
			thread_quantum_init(self);
		}

		/*
		 *	Set up quantum timer and timeslice.
		 */
		processor->quantum_end = processor->last_dispatch + self->quantum_remaining;
		timer_call_quantum_timer_enter(&processor->quantum_timer, self,
			processor->quantum_end, processor->last_dispatch);

		processor->first_timeslice = TRUE;
	} else {
		timer_call_quantum_timer_cancel(&processor->quantum_timer);
		processor->first_timeslice = FALSE;

		thread_tell_urgency(THREAD_URGENCY_NONE, 0, 0, 0, self);
	}

	assert(self->block_hint == kThreadWaitNone);
	self->computation_epoch = processor->last_dispatch;
	self->reason = AST_NONE;
	processor->starting_pri = self->sched_pri;

	thread_unlock(self);

	machine_thread_going_on_core(self, urgency, latency, self->same_pri_latency,
	                             processor->last_dispatch);

#if defined(CONFIG_SCHED_DEFERRED_AST)
	/*
	 * TODO: Can we state that redispatching our old thread is also
	 * uninteresting?
	 */
	if ((((volatile uint32_t)sched_run_buckets[TH_BUCKET_RUN]) == 1) &&
	    !(self->state & TH_IDLE)) {
		pset_cancel_deferred_dispatch(processor->processor_set, processor);
	}
#endif
}