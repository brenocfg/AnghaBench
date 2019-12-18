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
struct TYPE_2__ {int /*<<< orphan*/  old_k1; int /*<<< orphan*/  old_iob; void* fdr; void* fir; void* fcr; void* fsr; void* eflag; } ;
struct task_struct {TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  IA64_KR_IO_BASE ; 
 int /*<<< orphan*/  IA64_KR_TSSD ; 
 int /*<<< orphan*/  _IA64_REG_AR_EFLAG ; 
 int /*<<< orphan*/  _IA64_REG_AR_FCR ; 
 int /*<<< orphan*/  _IA64_REG_AR_FDR ; 
 int /*<<< orphan*/  _IA64_REG_AR_FIR ; 
 int /*<<< orphan*/  _IA64_REG_AR_FSR ; 
 void* ia64_getreg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ia64_set_kr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ia32_save_state (struct task_struct *t)
{
	t->thread.eflag = ia64_getreg(_IA64_REG_AR_EFLAG);
	t->thread.fsr   = ia64_getreg(_IA64_REG_AR_FSR);
	t->thread.fcr   = ia64_getreg(_IA64_REG_AR_FCR);
	t->thread.fir   = ia64_getreg(_IA64_REG_AR_FIR);
	t->thread.fdr   = ia64_getreg(_IA64_REG_AR_FDR);
	ia64_set_kr(IA64_KR_IO_BASE, t->thread.old_iob);
	ia64_set_kr(IA64_KR_TSSD, t->thread.old_k1);
}