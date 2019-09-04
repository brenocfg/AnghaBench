#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int boolean_t ;
struct TYPE_3__ {scalar_t__ save_r12; int /*<<< orphan*/  save_r3; int /*<<< orphan*/  save_r2; int /*<<< orphan*/  save_r1; int /*<<< orphan*/  save_r0; int /*<<< orphan*/  save_r4; } ;
typedef  TYPE_1__ arm_saved_state32_t ;

/* Variables and functions */
 int BSDDBG_CODE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DBG_BSD_EXCP_SC ; 
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
arm_trace_u32_unix_syscall(int code, arm_saved_state32_t *regs) 
{
	boolean_t indirect = (regs->save_r12 == 0);
	if (indirect)
		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE, 
			BSDDBG_CODE(DBG_BSD_EXCP_SC, code) | DBG_FUNC_START,
			regs->save_r1, regs->save_r2, regs->save_r3, regs->save_r4, 0);
	else
		KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE, 
			BSDDBG_CODE(DBG_BSD_EXCP_SC, code) | DBG_FUNC_START,
			regs->save_r0, regs->save_r1, regs->save_r2, regs->save_r3, 0);
}