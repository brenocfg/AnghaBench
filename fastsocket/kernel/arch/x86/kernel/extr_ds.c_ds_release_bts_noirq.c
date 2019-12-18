#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct task_struct {int dummy; } ;
struct TYPE_4__ {TYPE_1__* context; } ;
struct bts_tracer {TYPE_2__ ds; } ;
struct TYPE_3__ {scalar_t__ cpu; struct task_struct* task; } ;

/* Variables and functions */
 int EPERM ; 
 struct task_struct* current ; 
 int /*<<< orphan*/  ds_free_bts (struct bts_tracer*) ; 
 int /*<<< orphan*/  ds_suspend_bts_noirq (struct bts_tracer*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 scalar_t__ smp_processor_id () ; 

int ds_release_bts_noirq(struct bts_tracer *tracer)
{
	struct task_struct *task;
	unsigned long irq;
	int error;

	if (!tracer)
		return 0;

	task = tracer->ds.context->task;

	local_irq_save(irq);

	error = -EPERM;
	if (!task &&
	    (tracer->ds.context->cpu != smp_processor_id()))
		goto out;

	error = -EPERM;
	if (task && (task != current))
		goto out;

	ds_suspend_bts_noirq(tracer);
	ds_free_bts(tracer);

	error = 0;
 out:
	local_irq_restore(irq);
	return error;
}