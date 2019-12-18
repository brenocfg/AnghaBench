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
struct trace_iterator {int dummy; } ;
struct file {struct trace_iterator* private_data; } ;
typedef  int /*<<< orphan*/  poll_table ;

/* Variables and functions */
 unsigned int POLLIN ; 
 unsigned int POLLRDNORM ; 
 int TRACE_ITER_BLOCK ; 
 int /*<<< orphan*/  poll_wait (struct file*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_empty (struct trace_iterator*) ; 
 int trace_flags ; 
 int /*<<< orphan*/  trace_wait ; 

__attribute__((used)) static unsigned int
tracing_poll_pipe(struct file *filp, poll_table *poll_table)
{
	struct trace_iterator *iter = filp->private_data;

	if (trace_flags & TRACE_ITER_BLOCK) {
		/*
		 * Always select as readable when in blocking mode
		 */
		return POLLIN | POLLRDNORM;
	} else {
		if (!trace_empty(iter))
			return POLLIN | POLLRDNORM;
		poll_wait(filp, &trace_wait, poll_table);
		if (!trace_empty(iter))
			return POLLIN | POLLRDNORM;

		return 0;
	}
}