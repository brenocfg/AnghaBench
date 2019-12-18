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
struct TYPE_3__ {int nr_entries; int skip; } ;

/* Variables and functions */
 int THREAD_SIZE ; 
 int /*<<< orphan*/  __raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __raw_spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  max_stack_lock ; 
 unsigned long max_stack_size ; 
 TYPE_1__ max_stack_trace ; 
 int /*<<< orphan*/  object_is_on_stack (unsigned long*) ; 
 int /*<<< orphan*/  save_stack_trace (TYPE_1__*) ; 
 unsigned long* stack_dump_index ; 
 unsigned long* stack_dump_trace ; 

__attribute__((used)) static inline void check_stack(void)
{
	unsigned long this_size, flags;
	unsigned long *p, *top, *start;
	int i;

	this_size = ((unsigned long)&this_size) & (THREAD_SIZE-1);
	this_size = THREAD_SIZE - this_size;

	if (this_size <= max_stack_size)
		return;

	/* we do not handle interrupt stacks yet */
	if (!object_is_on_stack(&this_size))
		return;

	local_irq_save(flags);
	__raw_spin_lock(&max_stack_lock);

	/* a race could have already updated it */
	if (this_size <= max_stack_size)
		goto out;

	max_stack_size = this_size;

	max_stack_trace.nr_entries	= 0;
	max_stack_trace.skip		= 3;

	save_stack_trace(&max_stack_trace);

	/*
	 * Now find where in the stack these are.
	 */
	i = 0;
	start = &this_size;
	top = (unsigned long *)
		(((unsigned long)start & ~(THREAD_SIZE-1)) + THREAD_SIZE);

	/*
	 * Loop through all the entries. One of the entries may
	 * for some reason be missed on the stack, so we may
	 * have to account for them. If they are all there, this
	 * loop will only happen once. This code only takes place
	 * on a new max, so it is far from a fast path.
	 */
	while (i < max_stack_trace.nr_entries) {
		int found = 0;

		stack_dump_index[i] = this_size;
		p = start;

		for (; p < top && i < max_stack_trace.nr_entries; p++) {
			if (*p == stack_dump_trace[i]) {
				this_size = stack_dump_index[i++] =
					(top - p) * sizeof(unsigned long);
				found = 1;
				/* Start the search from here */
				start = p + 1;
			}
		}

		if (!found)
			i++;
	}

 out:
	__raw_spin_unlock(&max_stack_lock);
	local_irq_restore(flags);
}