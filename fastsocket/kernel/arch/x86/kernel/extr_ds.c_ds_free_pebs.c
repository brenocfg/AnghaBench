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
struct TYPE_3__ {TYPE_2__* context; } ;
struct pebs_tracer {TYPE_1__ ds; } ;
struct TYPE_4__ {struct pebs_tracer* pebs_master; struct task_struct* task; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ds_put_context (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (struct pebs_tracer*) ; 
 int /*<<< orphan*/  put_tracer (struct task_struct*) ; 

__attribute__((used)) static void ds_free_pebs(struct pebs_tracer *tracer)
{
	struct task_struct *task;

	task = tracer->ds.context->task;

	WARN_ON_ONCE(tracer->ds.context->pebs_master != tracer);
	tracer->ds.context->pebs_master = NULL;

	ds_put_context(tracer->ds.context);
	put_tracer(task);

	kfree(tracer);
}