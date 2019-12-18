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
struct thread_info {scalar_t__* fpsaved; scalar_t__ pcr_reg; int /*<<< orphan*/ * user_cntd1; int /*<<< orphan*/  user_cntd0; TYPE_1__* task; } ;
struct mm_struct {int dummy; } ;
struct TYPE_2__ {struct mm_struct* mm; } ;

/* Variables and functions */
 scalar_t__ ASI_AIUS ; 
 int /*<<< orphan*/  TIF_32BIT ; 
 int /*<<< orphan*/  TIF_ABI_PENDING ; 
 int /*<<< orphan*/  TIF_PERFCTR ; 
 int /*<<< orphan*/  USER_DS ; 
 int /*<<< orphan*/  clear_ti_thread_flag (struct thread_info*,int /*<<< orphan*/ ) ; 
 struct thread_info* current_thread_info () ; 
 scalar_t__ get_thread_current_ds () ; 
 int /*<<< orphan*/  set_fs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_thread_wsaved (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ti_thread_flag (struct thread_info*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_thread_flag (int /*<<< orphan*/ ) ; 
 scalar_t__ test_ti_thread_flag (struct thread_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsb_context_switch (struct mm_struct*) ; 
 int /*<<< orphan*/  write_pcr (int /*<<< orphan*/ ) ; 

void flush_thread(void)
{
	struct thread_info *t = current_thread_info();
	struct mm_struct *mm;

	if (test_ti_thread_flag(t, TIF_ABI_PENDING)) {
		clear_ti_thread_flag(t, TIF_ABI_PENDING);
		if (test_ti_thread_flag(t, TIF_32BIT))
			clear_ti_thread_flag(t, TIF_32BIT);
		else
			set_ti_thread_flag(t, TIF_32BIT);
	}

	mm = t->task->mm;
	if (mm)
		tsb_context_switch(mm);

	set_thread_wsaved(0);

	/* Turn off performance counters if on. */
	if (test_and_clear_thread_flag(TIF_PERFCTR)) {
		t->user_cntd0 = t->user_cntd1 = NULL;
		t->pcr_reg = 0;
		write_pcr(0);
	}

	/* Clear FPU register state. */
	t->fpsaved[0] = 0;
	
	if (get_thread_current_ds() != ASI_AIUS)
		set_fs(USER_DS);
}