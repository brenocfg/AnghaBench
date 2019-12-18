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
struct trace_iterator {int /*<<< orphan*/  iter_flags; } ;
struct inode {scalar_t__ i_private; } ;
struct file {int f_mode; int f_flags; } ;

/* Variables and functions */
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 scalar_t__ IS_ERR (struct trace_iterator*) ; 
 int O_TRUNC ; 
 int PTR_ERR (struct trace_iterator*) ; 
 int /*<<< orphan*/  TRACE_FILE_LAT_FMT ; 
 int TRACE_ITER_LATENCY_FMT ; 
 long TRACE_PIPE_ALL_CPU ; 
 struct trace_iterator* __tracing_open (struct inode*,struct file*) ; 
 int /*<<< orphan*/  global_trace ; 
 int trace_flags ; 
 int /*<<< orphan*/  tracing_reset (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  tracing_reset_online_cpus (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tracing_open(struct inode *inode, struct file *file)
{
	struct trace_iterator *iter;
	int ret = 0;

	/* If this file was open for write, then erase contents */
	if ((file->f_mode & FMODE_WRITE) &&
	    (file->f_flags & O_TRUNC)) {
		long cpu = (long) inode->i_private;

		if (cpu == TRACE_PIPE_ALL_CPU)
			tracing_reset_online_cpus(&global_trace);
		else
			tracing_reset(&global_trace, cpu);
	}

	if (file->f_mode & FMODE_READ) {
		iter = __tracing_open(inode, file);
		if (IS_ERR(iter))
			ret = PTR_ERR(iter);
		else if (trace_flags & TRACE_ITER_LATENCY_FMT)
			iter->iter_flags |= TRACE_FILE_LAT_FMT;
	}
	return ret;
}