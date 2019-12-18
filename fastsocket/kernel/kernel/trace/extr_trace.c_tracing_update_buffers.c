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

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ring_buffer_expanded ; 
 int /*<<< orphan*/  trace_buf_size ; 
 int /*<<< orphan*/  trace_types_lock ; 
 int tracing_resize_ring_buffer (int /*<<< orphan*/ ) ; 

int tracing_update_buffers(void)
{
	int ret = 0;

	mutex_lock(&trace_types_lock);
	if (!ring_buffer_expanded)
		ret = tracing_resize_ring_buffer(trace_buf_size);
	mutex_unlock(&trace_types_lock);

	return ret;
}