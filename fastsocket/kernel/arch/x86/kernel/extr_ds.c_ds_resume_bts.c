#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned long debugctlmsr; } ;
struct task_struct {TYPE_1__ thread; } ;
struct TYPE_10__ {TYPE_4__* context; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
struct TYPE_8__ {TYPE_2__ ds; } ;
struct bts_tracer {TYPE_5__ ds; TYPE_3__ trace; int /*<<< orphan*/  flags; } ;
struct TYPE_9__ {int cpu; struct task_struct* task; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 unsigned long ds_bts_control (struct bts_tracer*) ; 
 unsigned long get_debugctlmsr_on_cpu (int) ; 
 scalar_t__ irqs_disabled () ; 
 int /*<<< orphan*/  update_debugctlmsr_on_cpu (int,unsigned long) ; 
 int /*<<< orphan*/  update_task_debugctlmsr (struct task_struct*,unsigned long) ; 

void ds_resume_bts(struct bts_tracer *tracer)
{
	struct task_struct *task;
	unsigned long debugctlmsr;
	int cpu;

	if (!tracer)
		return;

	tracer->flags = tracer->trace.ds.flags;

	task = tracer->ds.context->task;
	cpu  = tracer->ds.context->cpu;

	WARN_ON(!task && irqs_disabled());

	debugctlmsr = (task ?
		       task->thread.debugctlmsr :
		       get_debugctlmsr_on_cpu(cpu));
	debugctlmsr |= ds_bts_control(tracer);

	if (task)
		update_task_debugctlmsr(task, debugctlmsr);
	else
		update_debugctlmsr_on_cpu(cpu, debugctlmsr);
}