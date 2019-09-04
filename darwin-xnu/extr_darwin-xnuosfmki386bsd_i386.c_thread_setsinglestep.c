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
struct TYPE_7__ {TYPE_1__ isf; } ;
typedef  TYPE_2__ x86_saved_state64_t ;
struct TYPE_8__ {scalar_t__ cs; int /*<<< orphan*/  efl; } ;
typedef  TYPE_3__ x86_saved_state32_t ;
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  DIRTY ; 
 int /*<<< orphan*/  EFL_TF ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ SYSENTER_CS ; 
 scalar_t__ SYSENTER_TF_CS ; 
 TYPE_3__* USER_REGS32 (int /*<<< orphan*/ ) ; 
 TYPE_2__* USER_REGS64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pal_register_cache_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ thread_is_64bit_addr (int /*<<< orphan*/ ) ; 

kern_return_t
thread_setsinglestep(thread_t thread, int on)
{
	pal_register_cache_state(thread, DIRTY);
	if (thread_is_64bit_addr(thread)) {
		x86_saved_state64_t	*iss64;

		iss64 = USER_REGS64(thread);

		if (on)
			iss64->isf.rflags |= EFL_TF;
		else
			iss64->isf.rflags &= ~EFL_TF;
	} else {
		x86_saved_state32_t	*iss32;

		iss32 = USER_REGS32(thread);

		if (on) {
			iss32->efl |= EFL_TF;
			/* Ensure IRET */
			if (iss32->cs == SYSENTER_CS)
				iss32->cs = SYSENTER_TF_CS;
		}
		else
			iss32->efl &= ~EFL_TF;
	}
	
	return (KERN_SUCCESS);
}