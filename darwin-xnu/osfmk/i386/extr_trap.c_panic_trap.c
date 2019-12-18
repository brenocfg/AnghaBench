#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t trapno; int err; int cs; int ss; int /*<<< orphan*/  cpu; int /*<<< orphan*/  rip; int /*<<< orphan*/  rflags; int /*<<< orphan*/  rsp; } ;
struct TYPE_6__ {TYPE_1__ isf; int /*<<< orphan*/  cr2; int /*<<< orphan*/  r15; int /*<<< orphan*/  r14; int /*<<< orphan*/  r13; int /*<<< orphan*/  r12; int /*<<< orphan*/  r11; int /*<<< orphan*/  r10; int /*<<< orphan*/  r9; int /*<<< orphan*/  r8; int /*<<< orphan*/  rdi; int /*<<< orphan*/  rsi; int /*<<< orphan*/  rbp; int /*<<< orphan*/  rdx; int /*<<< orphan*/  rcx; int /*<<< orphan*/  rbx; int /*<<< orphan*/  rax; } ;
typedef  TYPE_2__ x86_saved_state64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ pal_cr_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_7__ {TYPE_2__* cpu_fatal_trap_state; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 size_t TRAP_TYPES ; 
 scalar_t__ TRUE ; 
 size_t T_PAGE_FAULT ; 
 int T_PF_EXECUTE ; 
 int T_PF_PROT ; 
 int /*<<< orphan*/  VM_MAX_USER_PAGE_ADDRESS ; 
 int /*<<< orphan*/  VM_MIN_KERNEL_AND_KEXT_ADDRESS ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cpu_number () ; 
 TYPE_4__* current_cpu_datap () ; 
 int /*<<< orphan*/  kprintf (char*,scalar_t__,size_t,scalar_t__,...) ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  pal_get_control_registers (scalar_t__*,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,size_t,char const*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic_io_port_read () ; 
 scalar_t__ pmap_smap_enabled ; 
 scalar_t__ pmap_smep_enabled ; 
 char** trap_type ; 
 scalar_t__ virtualized ; 

__attribute__((used)) static void
panic_trap(x86_saved_state64_t *regs, uint32_t pl, kern_return_t fault_result)
{
	const char	*trapname = "Unknown";
	pal_cr_t	cr0, cr2, cr3, cr4;
	boolean_t	potential_smep_fault = FALSE, potential_kernel_NX_fault = FALSE;
	boolean_t	potential_smap_fault = FALSE;

	pal_get_control_registers( &cr0, &cr2, &cr3, &cr4 );
	assert(ml_get_interrupts_enabled() == FALSE);
	current_cpu_datap()->cpu_fatal_trap_state = regs;
	/*
	 * Issue an I/O port read if one has been requested - this is an
	 * event logic analyzers can use as a trigger point.
	 */
	panic_io_port_read();

	kprintf("CPU %d panic trap number 0x%x, rip 0x%016llx\n",
	    cpu_number(), regs->isf.trapno, regs->isf.rip);
	kprintf("cr0 0x%016llx cr2 0x%016llx cr3 0x%016llx cr4 0x%016llx\n",
		cr0, cr2, cr3, cr4);

	if (regs->isf.trapno < TRAP_TYPES)
	        trapname = trap_type[regs->isf.trapno];

	if ((regs->isf.trapno == T_PAGE_FAULT) && (regs->isf.err == (T_PF_PROT | T_PF_EXECUTE)) && (regs->isf.rip == regs->cr2)) {
		if (pmap_smep_enabled && (regs->isf.rip < VM_MAX_USER_PAGE_ADDRESS)) {
			potential_smep_fault = TRUE;
		} else if (regs->isf.rip >= VM_MIN_KERNEL_AND_KEXT_ADDRESS) {
			potential_kernel_NX_fault = TRUE;
		}
	} else if (pmap_smap_enabled &&
		   regs->isf.trapno == T_PAGE_FAULT &&
		   regs->isf.err & T_PF_PROT &&
		   regs->cr2 < VM_MAX_USER_PAGE_ADDRESS &&
		   regs->isf.rip >= VM_MIN_KERNEL_AND_KEXT_ADDRESS) {
		potential_smap_fault = TRUE;
	}

#undef panic
	panic("Kernel trap at 0x%016llx, type %d=%s, registers:\n"
	      "CR0: 0x%016llx, CR2: 0x%016llx, CR3: 0x%016llx, CR4: 0x%016llx\n"
	      "RAX: 0x%016llx, RBX: 0x%016llx, RCX: 0x%016llx, RDX: 0x%016llx\n"
	      "RSP: 0x%016llx, RBP: 0x%016llx, RSI: 0x%016llx, RDI: 0x%016llx\n"
	      "R8:  0x%016llx, R9:  0x%016llx, R10: 0x%016llx, R11: 0x%016llx\n"
	      "R12: 0x%016llx, R13: 0x%016llx, R14: 0x%016llx, R15: 0x%016llx\n"
	      "RFL: 0x%016llx, RIP: 0x%016llx, CS:  0x%016llx, SS:  0x%016llx\n"
	      "Fault CR2: 0x%016llx, Error code: 0x%016llx, Fault CPU: 0x%x%s%s%s%s, PL: %d, VF: %d\n",
	      regs->isf.rip, regs->isf.trapno, trapname,
	      cr0, cr2, cr3, cr4,
	      regs->rax, regs->rbx, regs->rcx, regs->rdx,
	      regs->isf.rsp, regs->rbp, regs->rsi, regs->rdi,
	      regs->r8,  regs->r9,  regs->r10, regs->r11,
	      regs->r12, regs->r13, regs->r14, regs->r15,
	      regs->isf.rflags, regs->isf.rip, regs->isf.cs & 0xFFFF,
	      regs->isf.ss & 0xFFFF,regs->cr2, regs->isf.err, regs->isf.cpu,
	      virtualized ? " VMM" : "",
	      potential_kernel_NX_fault ? " Kernel NX fault" : "",
	      potential_smep_fault ? " SMEP/User NX fault" : "",
	      potential_smap_fault ? " SMAP fault" : "",
	      pl,
	      fault_result);
	/*
	 * This next statement is not executed,
	 * but it's needed to stop the compiler using tail call optimization
	 * for the panic call - which confuses the subsequent backtrace.
	 */
	cr0 = 0;
}