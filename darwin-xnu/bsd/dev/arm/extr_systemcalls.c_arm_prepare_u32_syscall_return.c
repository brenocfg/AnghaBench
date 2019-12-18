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
typedef  TYPE_1__* uthread_t ;
struct sysent {int sy_return_type; } ;
typedef  int /*<<< orphan*/  arm_saved_state_t ;
struct TYPE_6__ {int pc; int save_r0; int save_r1; int /*<<< orphan*/  cpsr; } ;
typedef  TYPE_2__ arm_saved_state32_t ;
struct TYPE_5__ {int* uu_rval; } ;

/* Variables and functions */
 int EJUSTRETURN ; 
 int ERESTART ; 
 int /*<<< orphan*/  PSR_CF ; 
#define  _SYSCALL_RET_ADDR_T 135 
#define  _SYSCALL_RET_INT_T 134 
#define  _SYSCALL_RET_NONE 133 
#define  _SYSCALL_RET_OFF_T 132 
#define  _SYSCALL_RET_SIZE_T 131 
#define  _SYSCALL_RET_SSIZE_T 130 
#define  _SYSCALL_RET_UINT64_T 129 
#define  _SYSCALL_RET_UINT_T 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_saved_state32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*) ; 
 TYPE_2__* saved_state32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unix_syscall_return_kprintf (char*) ; 

__attribute__((used)) static void
arm_prepare_u32_syscall_return(struct sysent *callp, arm_saved_state_t *regs, uthread_t uthread, int error)
{
	assert(is_saved_state32(regs));

	arm_saved_state32_t *ss32 = saved_state32(regs);

	if (error == ERESTART) {
		ss32->pc -= 4;
	} else if (error != EJUSTRETURN) {
		if (error) {
			ss32->save_r0 = error;
			ss32->save_r1 = 0;
			/* set the carry bit to execute cerror routine */
			ss32->cpsr |= PSR_CF;
			unix_syscall_return_kprintf("error: setting carry to trigger cerror call\n");
		} else {	/* (not error) */
			switch (callp->sy_return_type) {
			case _SYSCALL_RET_INT_T:
			case _SYSCALL_RET_UINT_T:
			case _SYSCALL_RET_OFF_T:
			case _SYSCALL_RET_ADDR_T:
			case _SYSCALL_RET_SIZE_T:
			case _SYSCALL_RET_SSIZE_T:
			case _SYSCALL_RET_UINT64_T:
				ss32->save_r0 = uthread->uu_rval[0];
				ss32->save_r1 = uthread->uu_rval[1];
				break;
			case _SYSCALL_RET_NONE:
				ss32->save_r0 = 0;
				ss32->save_r1 = 0;
				break;
			default:
				panic("unix_syscall: unknown return type");
				break;
			}
		}
	}
	/* else  (error == EJUSTRETURN) { nothing } */

}