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
struct task_struct {int dummy; } ;
struct ds_context {struct task_struct* task; int /*<<< orphan*/ ** this; scalar_t__ count; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_DS_AREA_MSR ; 
 int /*<<< orphan*/  clear_tsk_thread_flag (struct task_struct*,int /*<<< orphan*/ ) ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  ds_lock ; 
 int /*<<< orphan*/  kfree (struct ds_context*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_task_context_switch (struct task_struct*) ; 

__attribute__((used)) static void ds_put_context(struct ds_context *context)
{
	struct task_struct *task;
	unsigned long irq;

	if (!context)
		return;

	spin_lock_irqsave(&ds_lock, irq);

	if (--context->count) {
		spin_unlock_irqrestore(&ds_lock, irq);
		return;
	}

	*(context->this) = NULL;

	task = context->task;

	if (task)
		clear_tsk_thread_flag(task, TIF_DS_AREA_MSR);

	/*
	 * We leave the (now dangling) pointer to the DS configuration in
	 * the DS_AREA msr. This is as good or as bad as replacing it with
	 * NULL - the hardware would crash if we enabled tracing.
	 *
	 * This saves us some problems with having to write an msr on a
	 * different cpu while preventing others from doing the same for the
	 * next context for that same cpu.
	 */

	spin_unlock_irqrestore(&ds_lock, irq);

	/* The context might still be in use for context switching. */
	if (task && (task != current))
		wait_task_context_switch(task);

	kfree(context);
}