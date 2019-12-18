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
struct TYPE_5__ {int /*<<< orphan*/  cr2; int /*<<< orphan*/  err; int /*<<< orphan*/  cpu; int /*<<< orphan*/  trapno; } ;
typedef  TYPE_1__ x86_saved_state32_t ;
struct TYPE_6__ {int /*<<< orphan*/  faultvaddr; int /*<<< orphan*/  err; int /*<<< orphan*/  cpu; int /*<<< orphan*/  trapno; } ;
typedef  TYPE_2__ x86_exception_state32_t ;
typedef  int /*<<< orphan*/  thread_t ;

/* Variables and functions */
 TYPE_1__* USER_REGS32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_exception_state32(thread_t thread, x86_exception_state32_t *es)
{
        x86_saved_state32_t *saved_state;

        saved_state = USER_REGS32(thread);

	es->trapno = saved_state->trapno;
	es->cpu = saved_state->cpu;
	es->err = saved_state->err;
	es->faultvaddr = saved_state->cr2;
}