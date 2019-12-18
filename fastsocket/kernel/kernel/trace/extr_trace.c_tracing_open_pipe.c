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
struct trace_iterator {long cpu_file; struct trace_iterator* trace; int /*<<< orphan*/  (* pipe_open ) (struct trace_iterator*) ;int /*<<< orphan*/  mutex; int /*<<< orphan*/ * tr; int /*<<< orphan*/  iter_flags; int /*<<< orphan*/  started; } ;
struct inode {scalar_t__ i_private; } ;
struct file {struct trace_iterator* private_data; } ;
struct TYPE_2__ {scalar_t__ in_ns; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  TRACE_FILE_LAT_FMT ; 
 int /*<<< orphan*/  TRACE_FILE_TIME_IN_NS ; 
 int TRACE_ITER_LATENCY_FMT ; 
 long TRACE_PIPE_ALL_CPU ; 
 int /*<<< orphan*/  alloc_cpumask_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_set_cpu (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_setall (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_test_cpu (long,int /*<<< orphan*/ ) ; 
 struct trace_iterator* current_trace ; 
 int /*<<< orphan*/  global_trace ; 
 int /*<<< orphan*/  kfree (struct trace_iterator*) ; 
 struct trace_iterator* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct trace_iterator* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct trace_iterator*) ; 
 size_t trace_clock_id ; 
 TYPE_1__* trace_clocks ; 
 int trace_flags ; 
 int /*<<< orphan*/  trace_types_lock ; 
 scalar_t__ tracing_disabled ; 
 int /*<<< orphan*/  tracing_reader_cpumask ; 

__attribute__((used)) static int tracing_open_pipe(struct inode *inode, struct file *filp)
{
	long cpu_file = (long) inode->i_private;
	struct trace_iterator *iter;
	int ret = 0;

	if (tracing_disabled)
		return -ENODEV;

	mutex_lock(&trace_types_lock);

	/* We only allow one reader per cpu */
	if (cpu_file == TRACE_PIPE_ALL_CPU) {
		if (!cpumask_empty(tracing_reader_cpumask)) {
			ret = -EBUSY;
			goto out;
		}
		cpumask_setall(tracing_reader_cpumask);
	} else {
		if (!cpumask_test_cpu(cpu_file, tracing_reader_cpumask))
			cpumask_set_cpu(cpu_file, tracing_reader_cpumask);
		else {
			ret = -EBUSY;
			goto out;
		}
	}

	/* create a buffer to store the information to pass to userspace */
	iter = kzalloc(sizeof(*iter), GFP_KERNEL);
	if (!iter) {
		ret = -ENOMEM;
		goto out;
	}

	/*
	 * We make a copy of the current tracer to avoid concurrent
	 * changes on it while we are reading.
	 */
	iter->trace = kmalloc(sizeof(*iter->trace), GFP_KERNEL);
	if (!iter->trace) {
		ret = -ENOMEM;
		goto fail;
	}
	if (current_trace)
		*iter->trace = *current_trace;

	if (!alloc_cpumask_var(&iter->started, GFP_KERNEL)) {
		ret = -ENOMEM;
		goto fail;
	}

	/* trace pipe does not show start of buffer */
	cpumask_setall(iter->started);

	if (trace_flags & TRACE_ITER_LATENCY_FMT)
		iter->iter_flags |= TRACE_FILE_LAT_FMT;

	/* Output in nanoseconds only if we are using a clock in nanoseconds. */
	if (trace_clocks[trace_clock_id].in_ns)
		iter->iter_flags |= TRACE_FILE_TIME_IN_NS;

	iter->cpu_file = cpu_file;
	iter->tr = &global_trace;
	mutex_init(&iter->mutex);
	filp->private_data = iter;

	if (iter->trace->pipe_open)
		iter->trace->pipe_open(iter);

out:
	mutex_unlock(&trace_types_lock);
	return ret;

fail:
	kfree(iter->trace);
	kfree(iter);
	mutex_unlock(&trace_types_lock);
	return ret;
}