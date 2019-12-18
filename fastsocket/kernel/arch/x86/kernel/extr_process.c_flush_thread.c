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
struct TYPE_2__ {int /*<<< orphan*/  tls_array; scalar_t__ debugreg7; scalar_t__ debugreg6; scalar_t__ debugreg3; scalar_t__ debugreg2; scalar_t__ debugreg1; scalar_t__ debugreg0; } ;
struct task_struct {scalar_t__ fpu_counter; TYPE_1__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_DEBUG ; 
 int /*<<< orphan*/  clear_fpu (struct task_struct*) ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_used_math () ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void flush_thread(void)
{
	struct task_struct *tsk = current;

	clear_tsk_thread_flag(tsk, TIF_DEBUG);

	tsk->thread.debugreg0 = 0;
	tsk->thread.debugreg1 = 0;
	tsk->thread.debugreg2 = 0;
	tsk->thread.debugreg3 = 0;
	tsk->thread.debugreg6 = 0;
	tsk->thread.debugreg7 = 0;
	memset(tsk->thread.tls_array, 0, sizeof(tsk->thread.tls_array));
	/*
	 * Forget coprocessor state..
	 */
	tsk->fpu_counter = 0;
	clear_fpu(tsk);
	clear_used_math();
}