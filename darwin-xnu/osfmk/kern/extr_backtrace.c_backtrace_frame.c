#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  TYPE_1__* thread_t ;
struct TYPE_3__ {uintptr_t kernel_stack; } ;

/* Variables and functions */
 int IN_STK_BOUNDS (uintptr_t*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* current_thread () ; 
 uintptr_t kernel_stack_size ; 

uint32_t __attribute__((noinline,not_tail_called))
backtrace_frame(uintptr_t *bt, uint32_t max_frames, void *start_frame)
{
	thread_t thread = current_thread();
	uintptr_t *fp;
	uint32_t frame_index = 0;
	uintptr_t top, bottom;
	bool in_valid_stack;

	assert(bt != NULL);
	assert(max_frames > 0);

	fp = start_frame;
	bottom = thread->kernel_stack;
	top = bottom + kernel_stack_size;

#define IN_STK_BOUNDS(__addr) \
	(((uintptr_t)(__addr) >= (uintptr_t)bottom) && \
	((uintptr_t)(__addr) < (uintptr_t)top))

	in_valid_stack = IN_STK_BOUNDS(fp);

	if (!in_valid_stack) {
		fp = NULL;
	}

	while (fp != NULL && frame_index < max_frames) {
		uintptr_t *next_fp = (uintptr_t *)*fp;
		uintptr_t ret_addr = *(fp + 1); /* return address is one word higher than frame pointer */

		/*
		 * If the frame pointer is 0, backtracing has reached the top of
		 * the stack and there is no return address.  Some stacks might not
		 * have set this up, so bounds check, as well.
		 */
		in_valid_stack = IN_STK_BOUNDS(next_fp);

		if (next_fp == NULL || !in_valid_stack)
		{
			break;
		}

		bt[frame_index++] = ret_addr;

		/* stacks grow down; backtracing should be moving to higher addresses */
		if (next_fp <= fp) {
			break;
		}
		fp = next_fp;
	}

	return frame_index;
#undef IN_STK_BOUNDS
}