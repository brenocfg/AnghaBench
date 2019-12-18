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
struct kperf_context {scalar_t__ cur_thread; int /*<<< orphan*/  starting_fp; } ;
struct callstack {int flags; int nframes; scalar_t__* frames; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_VERB (int,int) ; 
 int CALLSTACK_64BIT ; 
 int CALLSTACK_KERNEL ; 
 int CALLSTACK_KERNEL_WORDS ; 
 int CALLSTACK_VALID ; 
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int PERF_CS_BACKTRACE ; 
 int /*<<< orphan*/  assert (int) ; 
 int backtrace_frame (uintptr_t*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ current_thread () ; 

void
kperf_backtrace_sample(struct callstack *cs, struct kperf_context *context)
{
	assert(cs != NULL);
	assert(context != NULL);
	assert(context->cur_thread == current_thread());

	cs->flags = CALLSTACK_KERNEL | CALLSTACK_KERNEL_WORDS;
#ifdef __LP64__
	cs->flags |= CALLSTACK_64BIT;
#endif

	BUF_VERB(PERF_CS_BACKTRACE | DBG_FUNC_START, 1);

	cs->nframes = backtrace_frame((uintptr_t *)&(cs->frames), cs->nframes - 1,
	                              context->starting_fp);
	if (cs->nframes > 0) {
		cs->flags |= CALLSTACK_VALID;
		/*
		 * Fake the value pointed to by the stack pointer or the link
		 * register for symbolicators.
		 */
		cs->frames[cs->nframes + 1] = 0;
		cs->nframes += 1;
	}

	BUF_VERB(PERF_CS_BACKTRACE | DBG_FUNC_END, cs->nframes);
}