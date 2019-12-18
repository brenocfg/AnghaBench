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
struct stackframe {unsigned long fp; int /*<<< orphan*/  lr; } ;
struct stack_trace {int skip; scalar_t__ nr_entries; scalar_t__ max_entries; int /*<<< orphan*/ * entries; } ;

/* Variables and functions */
 unsigned long THREAD_SIZE ; 
 int /*<<< orphan*/  current ; 
 unsigned long current_frame_pointer ; 
 scalar_t__ task_stack_page (int /*<<< orphan*/ ) ; 

void save_stack_trace(struct stack_trace *trace)
{
	unsigned long low, high;
	unsigned long fp;
	struct stackframe *frame;
	int skip = trace->skip;

	low = (unsigned long)task_stack_page(current);
	high = low + THREAD_SIZE;
	fp = current_frame_pointer;

	while (fp >= low && fp <= (high - 8)) {
		frame = (struct stackframe *)fp;

		if (skip) {
			skip--;
		} else {
			trace->entries[trace->nr_entries++] = frame->lr;
			if (trace->nr_entries >= trace->max_entries)
				break;
		}

		/*
		 * The next frame must be at a higher address than the
		 * current frame.
		 */
		low = fp + 8;
		fp = frame->fp;
	}
}