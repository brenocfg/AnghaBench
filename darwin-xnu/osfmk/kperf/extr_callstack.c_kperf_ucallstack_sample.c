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
typedef  int /*<<< orphan*/ * thread_t ;
struct kperf_context {int /*<<< orphan*/ * cur_thread; } ;
struct callstack {scalar_t__ nframes; int /*<<< orphan*/  flags; scalar_t__ frames; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_INFO (int,uintptr_t,scalar_t__,...) ; 
 int /*<<< orphan*/  CALLSTACK_64BIT ; 
 int /*<<< orphan*/  CALLSTACK_KERNEL_WORDS ; 
 int /*<<< orphan*/  CALLSTACK_VALID ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int EFAULT ; 
 int /*<<< orphan*/  ERR_GETSTACK ; 
 scalar_t__ MAX_CALLSTACK_FRAMES ; 
 int /*<<< orphan*/  PERF_CS_ERROR ; 
 int PERF_CS_USAMPLE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int backtrace_thread_user (int /*<<< orphan*/ *,uintptr_t*,scalar_t__,scalar_t__*,int*) ; 
 int /*<<< orphan*/  callstack_fixup_user (struct callstack*,int /*<<< orphan*/ *) ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 scalar_t__ thread_tid (int /*<<< orphan*/ *) ; 

void
kperf_ucallstack_sample(struct callstack *cs, struct kperf_context *context)
{
	thread_t thread;
	bool user_64 = false;
	int err;

	assert(cs != NULL);
	assert(context != NULL);
	assert(cs->nframes <= MAX_CALLSTACK_FRAMES);
	assert(ml_get_interrupts_enabled() == TRUE);

	thread = context->cur_thread;
	assert(thread != NULL);

	BUF_INFO(PERF_CS_USAMPLE | DBG_FUNC_START, (uintptr_t)thread_tid(thread),
		cs->nframes);

	cs->flags = 0;

	err = backtrace_thread_user(thread, (uintptr_t *)cs->frames,
		cs->nframes - 1, &cs->nframes, &user_64);
	cs->flags |= CALLSTACK_KERNEL_WORDS;
	if (user_64) {
		cs->flags |= CALLSTACK_64BIT;
	}

	if (!err || err == EFAULT) {
		callstack_fixup_user(cs, thread);
		cs->flags |= CALLSTACK_VALID;
	} else {
		cs->nframes = 0;
		BUF_INFO(PERF_CS_ERROR, ERR_GETSTACK, err);
	}

	BUF_INFO(PERF_CS_USAMPLE | DBG_FUNC_END, (uintptr_t)thread_tid(thread),
		cs->flags, cs->nframes);
}