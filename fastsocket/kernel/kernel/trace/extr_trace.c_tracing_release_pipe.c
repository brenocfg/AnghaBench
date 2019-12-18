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
struct trace_iterator {scalar_t__ cpu_file; struct trace_iterator* trace; int /*<<< orphan*/  mutex; int /*<<< orphan*/  started; } ;
struct inode {int dummy; } ;
struct file {struct trace_iterator* private_data; } ;

/* Variables and functions */
 scalar_t__ TRACE_PIPE_ALL_CPU ; 
 int /*<<< orphan*/  cpumask_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_clear_cpu (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_cpumask_var (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct trace_iterator*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_types_lock ; 
 int /*<<< orphan*/  tracing_reader_cpumask ; 

__attribute__((used)) static int tracing_release_pipe(struct inode *inode, struct file *file)
{
	struct trace_iterator *iter = file->private_data;

	mutex_lock(&trace_types_lock);

	if (iter->cpu_file == TRACE_PIPE_ALL_CPU)
		cpumask_clear(tracing_reader_cpumask);
	else
		cpumask_clear_cpu(iter->cpu_file, tracing_reader_cpumask);

	mutex_unlock(&trace_types_lock);

	free_cpumask_var(iter->started);
	mutex_destroy(&iter->mutex);
	kfree(iter->trace);
	kfree(iter);

	return 0;
}