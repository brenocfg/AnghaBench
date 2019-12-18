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
struct ds_tracer {size_t size; struct ds_context* context; void* buffer; } ;
struct ds_trace {int dummy; } ;
struct ds_context {int dummy; } ;
typedef  enum ds_qualifier { ____Placeholder_ds_qualifier } ds_qualifier ;
struct TYPE_2__ {size_t* sizeof_rec; } ;

/* Variables and functions */
 scalar_t__ DS_ALIGNMENT ; 
 int EINVAL ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  IS_ALIGNED (unsigned long,scalar_t__) ; 
 TYPE_1__ ds_cfg ; 
 struct ds_context* ds_get_context (struct task_struct*,int) ; 

__attribute__((used)) static int ds_request(struct ds_tracer *tracer, struct ds_trace *trace,
		      enum ds_qualifier qual, struct task_struct *task,
		      int cpu, void *base, size_t size, size_t th)
{
	struct ds_context *context;
	int error;
	size_t req_size;

	error = -EOPNOTSUPP;
	if (!ds_cfg.sizeof_rec[qual])
		goto out;

	error = -EINVAL;
	if (!base)
		goto out;

	req_size = ds_cfg.sizeof_rec[qual];
	/* We might need space for alignment adjustments. */
	if (!IS_ALIGNED((unsigned long)base, DS_ALIGNMENT))
		req_size += DS_ALIGNMENT;

	error = -EINVAL;
	if (size < req_size)
		goto out;

	if (th != (size_t)-1) {
		th *= ds_cfg.sizeof_rec[qual];

		error = -EINVAL;
		if (size <= th)
			goto out;
	}

	tracer->buffer = base;
	tracer->size = size;

	error = -ENOMEM;
	context = ds_get_context(task, cpu);
	if (!context)
		goto out;
	tracer->context = context;

	/*
	 * Defer any tracer-specific initialization work for the context until
	 * context ownership has been clarified.
	 */

	error = 0;
 out:
	return error;
}