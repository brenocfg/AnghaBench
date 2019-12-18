#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned long eflag; unsigned long fsr; unsigned long fcr; unsigned long fir; unsigned long fdr; } ;
struct task_struct {TYPE_2__ thread; } ;
struct pt_regs {int r17; void* r30; } ;
typedef  int __u32 ;
struct TYPE_4__ {void* old_k1; void* old_iob; } ;
struct TYPE_6__ {TYPE_1__ thread; } ;

/* Variables and functions */
 unsigned long IA32_IOBASE ; 
 int /*<<< orphan*/  IA64_KR_IO_BASE ; 
 int /*<<< orphan*/  IA64_KR_TSSD ; 
 int /*<<< orphan*/  _IA64_REG_AR_EFLAG ; 
 int /*<<< orphan*/  _IA64_REG_AR_FCR ; 
 int /*<<< orphan*/  _IA64_REG_AR_FDR ; 
 int /*<<< orphan*/  _IA64_REG_AR_FIR ; 
 int /*<<< orphan*/  _IA64_REG_AR_FSR ; 
 int _LDT ; 
 int _TSS ; 
 TYPE_3__* current ; 
 void* ia64_get_kr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ia64_set_kr (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ia64_setreg (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  load_TLS (TYPE_2__*,int /*<<< orphan*/ ) ; 
 void* load_desc (int) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 struct pt_regs* task_pt_regs (struct task_struct*) ; 

void
ia32_load_state (struct task_struct *t)
{
	unsigned long eflag, fsr, fcr, fir, fdr, tssd;
	struct pt_regs *regs = task_pt_regs(t);

	eflag = t->thread.eflag;
	fsr = t->thread.fsr;
	fcr = t->thread.fcr;
	fir = t->thread.fir;
	fdr = t->thread.fdr;
	tssd = load_desc(_TSS);					/* TSSD */

	ia64_setreg(_IA64_REG_AR_EFLAG, eflag);
	ia64_setreg(_IA64_REG_AR_FSR, fsr);
	ia64_setreg(_IA64_REG_AR_FCR, fcr);
	ia64_setreg(_IA64_REG_AR_FIR, fir);
	ia64_setreg(_IA64_REG_AR_FDR, fdr);
	current->thread.old_iob = ia64_get_kr(IA64_KR_IO_BASE);
	current->thread.old_k1 = ia64_get_kr(IA64_KR_TSSD);
	ia64_set_kr(IA64_KR_IO_BASE, IA32_IOBASE);
	ia64_set_kr(IA64_KR_TSSD, tssd);

	regs->r17 = (_TSS << 48) | (_LDT << 32) | (__u32) regs->r17;
	regs->r30 = load_desc(_LDT);				/* LDTD */
	load_TLS(&t->thread, smp_processor_id());
}