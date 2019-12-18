#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pv_cpu_asm_switch {unsigned long switch_to; unsigned long leave_syscall; unsigned long work_processed_syscall; unsigned long leave_kernel; } ;

/* Variables and functions */

void
paravirt_cpu_asm_init(const struct pv_cpu_asm_switch *cpu_asm_switch)
{
	extern unsigned long paravirt_switch_to_targ;
	extern unsigned long paravirt_leave_syscall_targ;
	extern unsigned long paravirt_work_processed_syscall_targ;
	extern unsigned long paravirt_leave_kernel_targ;

	paravirt_switch_to_targ = cpu_asm_switch->switch_to;
	paravirt_leave_syscall_targ = cpu_asm_switch->leave_syscall;
	paravirt_work_processed_syscall_targ =
		cpu_asm_switch->work_processed_syscall;
	paravirt_leave_kernel_targ = cpu_asm_switch->leave_kernel;
}