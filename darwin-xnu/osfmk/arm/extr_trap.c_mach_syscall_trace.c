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
struct arm_saved_state {scalar_t__* r; } ;
struct TYPE_2__ {int mach_trap_arg_count; } ;

/* Variables and functions */
 int DBG_FUNC_START ; 
 int /*<<< orphan*/  DBG_MACH_EXCP_SC ; 
 int /*<<< orphan*/  KDEBUG_TRACE ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT_IST (int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MACHDBG_CODE (int /*<<< orphan*/ ,unsigned int) ; 
 TYPE_1__* mach_trap_table ; 

void
mach_syscall_trace(
		   struct arm_saved_state * regs,
		   unsigned int call_number)
{
	int             i, argc;
	int             kdarg[3] = {0, 0, 0};

	argc = mach_trap_table[call_number].mach_trap_arg_count;

	if (argc > 3)
		argc = 3;

	for (i = 0; i < argc; i++)
		kdarg[i] = (int) regs->r[i];

	KERNEL_DEBUG_CONSTANT_IST(KDEBUG_TRACE,
		MACHDBG_CODE(DBG_MACH_EXCP_SC, (call_number)) | DBG_FUNC_START,
		kdarg[0], kdarg[1], kdarg[2], 0, 0);

}