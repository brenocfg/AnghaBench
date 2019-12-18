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
struct stack_frame {int /*<<< orphan*/  next_frame; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  in_irq_stack (unsigned long*,unsigned long*,unsigned long*) ; 
 int /*<<< orphan*/  probe_kernel_address (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline unsigned long
fixup_bp_irq_link(unsigned long bp, unsigned long *stack,
		  unsigned long *irq_stack, unsigned long *irq_stack_end)
{
#ifdef CONFIG_FRAME_POINTER
	struct stack_frame *frame = (struct stack_frame *)bp;
	unsigned long next;

	if (!in_irq_stack(stack, irq_stack, irq_stack_end)) {
		if (!probe_kernel_address(&frame->next_frame, next))
			return next;
		else
			WARN_ONCE(1, "Perf: bad frame pointer = %p in "
				  "callchain\n", &frame->next_frame);
	}
#endif
	return bp;
}