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
struct dentry {int dummy; } ;

/* Variables and functions */
 struct dentry* debugfs_create_dir (char*,struct dentry*) ; 
 int /*<<< orphan*/  pr_warning (char*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,long) ; 
 int /*<<< orphan*/  trace_create_file (char*,int,struct dentry*,void*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tracing_buffers_fops ; 
 struct dentry* tracing_dentry_percpu () ; 
 int /*<<< orphan*/  tracing_fops ; 
 int /*<<< orphan*/  tracing_pipe_fops ; 
 int /*<<< orphan*/  tracing_stats_fops ; 

__attribute__((used)) static void tracing_init_debugfs_percpu(long cpu)
{
	struct dentry *d_percpu = tracing_dentry_percpu();
	struct dentry *d_cpu;
	/* strlen(cpu) + MAX(log10(cpu)) + '\0' */
	char cpu_dir[7];

	if (cpu > 999 || cpu < 0)
		return;

	sprintf(cpu_dir, "cpu%ld", cpu);
	d_cpu = debugfs_create_dir(cpu_dir, d_percpu);
	if (!d_cpu) {
		pr_warning("Could not create debugfs '%s' entry\n", cpu_dir);
		return;
	}

	/* per cpu trace_pipe */
	trace_create_file("trace_pipe", 0444, d_cpu,
			(void *) cpu, &tracing_pipe_fops);

	/* per cpu trace */
	trace_create_file("trace", 0644, d_cpu,
			(void *) cpu, &tracing_fops);

	trace_create_file("trace_pipe_raw", 0444, d_cpu,
			(void *) cpu, &tracing_buffers_fops);

	trace_create_file("stats", 0444, d_cpu,
			(void *) cpu, &tracing_stats_fops);
}