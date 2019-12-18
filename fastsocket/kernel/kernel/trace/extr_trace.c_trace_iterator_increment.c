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
struct trace_iterator {size_t cpu; scalar_t__* buffer_iter; int /*<<< orphan*/  idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  ftrace_disable_cpu () ; 
 int /*<<< orphan*/  ftrace_enable_cpu () ; 
 int /*<<< orphan*/  ring_buffer_read (scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void trace_iterator_increment(struct trace_iterator *iter)
{
	/* Don't allow ftrace to trace into the ring buffers */
	ftrace_disable_cpu();

	iter->idx++;
	if (iter->buffer_iter[iter->cpu])
		ring_buffer_read(iter->buffer_iter[iter->cpu], NULL);

	ftrace_enable_cpu();
}