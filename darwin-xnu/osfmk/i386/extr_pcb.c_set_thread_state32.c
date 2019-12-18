#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ cs; int eflags; int /*<<< orphan*/  gs; int /*<<< orphan*/  fs; void* es; void* ds; void* ss; int /*<<< orphan*/  eip; int /*<<< orphan*/  esp; int /*<<< orphan*/  ebp; int /*<<< orphan*/  esi; int /*<<< orphan*/  edi; int /*<<< orphan*/  edx; int /*<<< orphan*/  ecx; int /*<<< orphan*/  ebx; int /*<<< orphan*/  eax; } ;
typedef  TYPE_2__ x86_thread_state32_t ;
struct TYPE_12__ {int efl; scalar_t__ cs; int /*<<< orphan*/  gs; int /*<<< orphan*/  fs; void* es; void* ds; void* ss; int /*<<< orphan*/  eip; int /*<<< orphan*/  uesp; int /*<<< orphan*/  ebp; int /*<<< orphan*/  esi; int /*<<< orphan*/  edi; int /*<<< orphan*/  edx; int /*<<< orphan*/  ecx; int /*<<< orphan*/  ebx; int /*<<< orphan*/  eax; } ;
typedef  TYPE_3__ x86_saved_state32_t ;
typedef  TYPE_4__* thread_t ;
struct TYPE_10__ {scalar_t__ cthread_self; } ;
struct TYPE_13__ {TYPE_1__ machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIRTY ; 
 int EFL_TF ; 
 int EFL_USER_CLEAR ; 
 int EFL_USER_SET ; 
 int KERN_INVALID_ARGUMENT ; 
 int KERN_SUCCESS ; 
 int /*<<< orphan*/  NULL_SEG ; 
 scalar_t__ SYSENTER_CS ; 
 scalar_t__ SYSENTER_TF_CS ; 
 scalar_t__ USER_CS ; 
 int /*<<< orphan*/  USER_CTHREAD ; 
 void* USER_DS ; 
 TYPE_3__* USER_REGS32 (TYPE_4__*) ; 
 int /*<<< orphan*/  pal_register_cache_state (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  valid_user_segment_selectors (scalar_t__,void*,void*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
set_thread_state32(thread_t thread, x86_thread_state32_t *ts)
{
        x86_saved_state32_t	*saved_state;

	pal_register_cache_state(thread, DIRTY);

	saved_state = USER_REGS32(thread);

	/*
	 * Scrub segment selector values:
	 */
	ts->cs = USER_CS;
	/*
	 * On a 64 bit kernel, we always override the data segments,
	 * as the actual selector numbers have changed. This also
	 * means that we don't support setting the data segments
	 * manually any more.
	 */
	ts->ss = USER_DS;
	ts->ds = USER_DS;
	ts->es = USER_DS;

	/* Set GS to CTHREAD only if's been established */
	ts->gs = thread->machine.cthread_self ? USER_CTHREAD : NULL_SEG;
 
	/* Check segment selectors are safe */
	if (!valid_user_segment_selectors(ts->cs,
					  ts->ss,
					  ts->ds,
					  ts->es,
					  ts->fs,
					  ts->gs))
		return(KERN_INVALID_ARGUMENT);

	saved_state->eax = ts->eax;
	saved_state->ebx = ts->ebx;
	saved_state->ecx = ts->ecx;
	saved_state->edx = ts->edx;
	saved_state->edi = ts->edi;
	saved_state->esi = ts->esi;
	saved_state->ebp = ts->ebp;
	saved_state->uesp = ts->esp;
	saved_state->efl = (ts->eflags & ~EFL_USER_CLEAR) | EFL_USER_SET;
	saved_state->eip = ts->eip;
	saved_state->cs = ts->cs;
	saved_state->ss = ts->ss;
	saved_state->ds = ts->ds;
	saved_state->es = ts->es;
	saved_state->fs = ts->fs;
	saved_state->gs = ts->gs;

	/*
	 * If the trace trap bit is being set,
	 * ensure that the user returns via iret
	 * - which is signaled thusly:
	 */
	if ((saved_state->efl & EFL_TF) && saved_state->cs == SYSENTER_CS)
		saved_state->cs = SYSENTER_TF_CS;

	return(KERN_SUCCESS);
}