#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  gs; int /*<<< orphan*/  fs; int /*<<< orphan*/  es; int /*<<< orphan*/  ds; int /*<<< orphan*/  ss; int /*<<< orphan*/  cs; int /*<<< orphan*/  eip; int /*<<< orphan*/  eflags; int /*<<< orphan*/  esp; int /*<<< orphan*/  ebp; int /*<<< orphan*/  esi; int /*<<< orphan*/  edi; int /*<<< orphan*/  edx; int /*<<< orphan*/  ecx; int /*<<< orphan*/  ebx; int /*<<< orphan*/  eax; } ;
typedef  TYPE_1__ x86_thread_state32_t ;
struct TYPE_6__ {int /*<<< orphan*/  gs; int /*<<< orphan*/  fs; int /*<<< orphan*/  es; int /*<<< orphan*/  ds; int /*<<< orphan*/  ss; int /*<<< orphan*/  cs; int /*<<< orphan*/  eip; int /*<<< orphan*/  efl; int /*<<< orphan*/  uesp; int /*<<< orphan*/  ebp; int /*<<< orphan*/  esi; int /*<<< orphan*/  edi; int /*<<< orphan*/  edx; int /*<<< orphan*/  ecx; int /*<<< orphan*/  ebx; int /*<<< orphan*/  eax; } ;
typedef  TYPE_2__ x86_saved_state32_t ;
typedef  int /*<<< orphan*/  thread_t ;

/* Variables and functions */
 TYPE_2__* USER_REGS32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VALID ; 
 int /*<<< orphan*/  pal_register_cache_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_thread_state32(thread_t thread, x86_thread_state32_t *ts)
{
        x86_saved_state32_t	*saved_state;

	pal_register_cache_state(thread, VALID);

	saved_state = USER_REGS32(thread);

	ts->eax = saved_state->eax;
	ts->ebx = saved_state->ebx;
	ts->ecx = saved_state->ecx;
	ts->edx = saved_state->edx;
	ts->edi = saved_state->edi;
	ts->esi = saved_state->esi;
	ts->ebp = saved_state->ebp;
	ts->esp = saved_state->uesp;
	ts->eflags = saved_state->efl;
	ts->eip = saved_state->eip;
	ts->cs = saved_state->cs;
	ts->ss = saved_state->ss;
	ts->ds = saved_state->ds;
	ts->es = saved_state->es;
	ts->fs = saved_state->fs;
	ts->gs = saved_state->gs;
}