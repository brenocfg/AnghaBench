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
struct task_struct {int dummy; } ;
struct TYPE_2__ {int t; scalar_t__ l; scalar_t__ h; scalar_t__ r; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_BLOCKSTEP ; 
 int /*<<< orphan*/  TIF_SINGLESTEP ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 TYPE_1__* pa_psw (struct task_struct*) ; 
 int /*<<< orphan*/  set_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 

void user_enable_block_step(struct task_struct *task)
{
	clear_tsk_thread_flag(task, TIF_SINGLESTEP);
	set_tsk_thread_flag(task, TIF_BLOCKSTEP);

	/* Enable taken branch trap. */
	pa_psw(task)->r = 0;
	pa_psw(task)->t = 1;
	pa_psw(task)->h = 0;
	pa_psw(task)->l = 0;
}