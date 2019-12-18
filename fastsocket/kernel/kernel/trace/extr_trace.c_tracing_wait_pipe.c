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
struct trace_iterator {scalar_t__ pos; int /*<<< orphan*/  mutex; TYPE_1__* trace; } ;
struct file {int f_flags; struct trace_iterator* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* wait_pipe ) (struct trace_iterator*) ;} ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct trace_iterator*) ; 
 scalar_t__ trace_empty (struct trace_iterator*) ; 
 int /*<<< orphan*/  tracer_enabled ; 

__attribute__((used)) static int tracing_wait_pipe(struct file *filp)
{
	struct trace_iterator *iter = filp->private_data;

	while (trace_empty(iter)) {

		if ((filp->f_flags & O_NONBLOCK)) {
			return -EAGAIN;
		}

		mutex_unlock(&iter->mutex);

		iter->trace->wait_pipe(iter);

		mutex_lock(&iter->mutex);

		if (signal_pending(current))
			return -EINTR;

		/*
		 * We block until we read something and tracing is disabled.
		 * We still block if tracing is disabled, but we have never
		 * read anything. This allows a user to cat this file, and
		 * then enable tracing. But after we have read something,
		 * we give an EOF when tracing is again disabled.
		 *
		 * iter->pos will be 0 if we haven't read anything.
		 */
		if (!tracer_enabled && iter->pos)
			break;
	}

	return 1;
}