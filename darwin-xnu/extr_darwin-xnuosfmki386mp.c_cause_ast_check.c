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
typedef  TYPE_1__* processor_t ;
struct TYPE_3__ {int cpu_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC ; 
 int /*<<< orphan*/  DBG_MACH_SCHED ; 
 int /*<<< orphan*/  KERNEL_DEBUG_CONSTANT (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACHDBG_CODE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MACH_REMOTE_AST ; 
 int /*<<< orphan*/  MP_AST ; 
 int cpu_number () ; 
 int /*<<< orphan*/  i386_signal_cpu (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
cause_ast_check(
	processor_t	processor)
{
	int	cpu = processor->cpu_id;

	if (cpu != cpu_number()) {
		i386_signal_cpu(cpu, MP_AST, ASYNC);
		KERNEL_DEBUG_CONSTANT(MACHDBG_CODE(DBG_MACH_SCHED, MACH_REMOTE_AST), cpu, 1, 0, 0, 0);
	}
}