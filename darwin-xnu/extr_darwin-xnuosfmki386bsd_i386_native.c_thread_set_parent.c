#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  rflags; } ;
struct TYPE_7__ {int rax; TYPE_1__ isf; scalar_t__ rdx; } ;
typedef  TYPE_2__ x86_saved_state64_t ;
struct TYPE_8__ {int eax; int /*<<< orphan*/  efl; scalar_t__ edx; } ;
typedef  TYPE_3__ x86_saved_state32_t ;
typedef  int /*<<< orphan*/  thread_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIRTY ; 
 int /*<<< orphan*/  EFL_CF ; 
 TYPE_3__* USER_REGS32 (int /*<<< orphan*/ ) ; 
 TYPE_2__* USER_REGS64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pal_register_cache_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ thread_is_64bit_addr (int /*<<< orphan*/ ) ; 

void
thread_set_parent(thread_t parent, int pid)
{
	pal_register_cache_state(parent, DIRTY);

	if (thread_is_64bit_addr(parent)) {
		x86_saved_state64_t	*iss64;

		iss64 = USER_REGS64(parent);

		iss64->rax = pid;
		iss64->rdx = 0;
		iss64->isf.rflags &= ~EFL_CF;
	} else {
		x86_saved_state32_t	*iss32;

		iss32 = USER_REGS32(parent);

		iss32->eax = pid;
		iss32->edx = 0;
		iss32->efl &= ~EFL_CF;
	}
}