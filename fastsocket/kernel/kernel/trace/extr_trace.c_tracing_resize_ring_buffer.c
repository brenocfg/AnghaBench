#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  use_max_tr; } ;
struct TYPE_5__ {unsigned long entries; int /*<<< orphan*/  buffer; } ;
struct TYPE_4__ {unsigned long entries; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_3__* current_trace ; 
 TYPE_2__ global_trace ; 
 TYPE_1__ max_tr ; 
 int ring_buffer_expanded ; 
 int ring_buffer_resize (int /*<<< orphan*/ ,unsigned long) ; 
 int tracing_disabled ; 

__attribute__((used)) static int tracing_resize_ring_buffer(unsigned long size)
{
	int ret;

	/*
	 * If kernel or user changes the size of the ring buffer
	 * we use the size that was given, and we can forget about
	 * expanding it later.
	 */
	ring_buffer_expanded = 1;

	ret = ring_buffer_resize(global_trace.buffer, size);
	if (ret < 0)
		return ret;

	if (!current_trace->use_max_tr)
		goto out;

	ret = ring_buffer_resize(max_tr.buffer, size);
	if (ret < 0) {
		int r;

		r = ring_buffer_resize(global_trace.buffer,
				       global_trace.entries);
		if (r < 0) {
			/*
			 * AARGH! We are left with different
			 * size max buffer!!!!
			 * The max buffer is our "snapshot" buffer.
			 * When a tracer needs a snapshot (one of the
			 * latency tracers), it swaps the max buffer
			 * with the saved snap shot. We succeeded to
			 * update the size of the main buffer, but failed to
			 * update the size of the max buffer. But when we tried
			 * to reset the main buffer to the original size, we
			 * failed there too. This is very unlikely to
			 * happen, but if it does, warn and kill all
			 * tracing.
			 */
			WARN_ON(1);
			tracing_disabled = 1;
		}
		return ret;
	}

	max_tr.entries = size;
 out:
	global_trace.entries = size;

	return ret;
}