#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
struct kperf_context {TYPE_1__* cur_thread; } ;
struct callstack {int flags; int nframes; int /*<<< orphan*/ * frames; } ;
struct TYPE_2__ {int /*<<< orphan*/ * continuation; } ;

/* Variables and functions */
 int CALLSTACK_64BIT ; 
 int CALLSTACK_CONTINUATION ; 
 int CALLSTACK_KERNEL ; 
 int CALLSTACK_VALID ; 
 int /*<<< orphan*/  VM_KERNEL_UNSLIDE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void
kperf_continuation_sample(struct callstack *cs, struct kperf_context *context)
{
	thread_t thread;

	assert(cs != NULL);
	assert(context != NULL);

	thread = context->cur_thread;
	assert(thread != NULL);
	assert(thread->continuation != NULL);

	cs->flags = CALLSTACK_CONTINUATION | CALLSTACK_VALID | CALLSTACK_KERNEL;
#ifdef __LP64__
	cs->flags |= CALLSTACK_64BIT;
#endif

	cs->nframes = 1;
	cs->frames[0] = VM_KERNEL_UNSLIDE(thread->continuation);
}