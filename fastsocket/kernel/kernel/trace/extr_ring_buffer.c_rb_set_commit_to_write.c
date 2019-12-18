#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ring_buffer_per_cpu {TYPE_3__* tail_page; TYPE_3__* commit_page; int /*<<< orphan*/  write_stamp; TYPE_1__* buffer; } ;
struct TYPE_8__ {TYPE_2__* page; } ;
struct TYPE_7__ {int /*<<< orphan*/  commit; int /*<<< orphan*/  time_stamp; } ;
struct TYPE_6__ {int pages; } ;

/* Variables and functions */
 scalar_t__ RB_WARN_ON (struct ring_buffer_per_cpu*,int) ; 
 int RB_WRITE_MASK ; 
 int /*<<< orphan*/  barrier () ; 
 int local_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_set (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ rb_commit_index (struct ring_buffer_per_cpu*) ; 
 int /*<<< orphan*/  rb_inc_page (struct ring_buffer_per_cpu*,TYPE_3__**) ; 
 int rb_is_reader_page (TYPE_3__*) ; 
 scalar_t__ rb_page_write (TYPE_3__*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
rb_set_commit_to_write(struct ring_buffer_per_cpu *cpu_buffer)
{
	unsigned long max_count;

	/*
	 * We only race with interrupts and NMIs on this CPU.
	 * If we own the commit event, then we can commit
	 * all others that interrupted us, since the interruptions
	 * are in stack format (they finish before they come
	 * back to us). This allows us to do a simple loop to
	 * assign the commit to the tail.
	 */
 again:
	max_count = cpu_buffer->buffer->pages * 100;

	while (cpu_buffer->commit_page != cpu_buffer->tail_page) {
		if (RB_WARN_ON(cpu_buffer, !(--max_count)))
			return;
		if (RB_WARN_ON(cpu_buffer,
			       rb_is_reader_page(cpu_buffer->tail_page)))
			return;
		local_set(&cpu_buffer->commit_page->page->commit,
			  rb_page_write(cpu_buffer->commit_page));
		rb_inc_page(cpu_buffer, &cpu_buffer->commit_page);
		cpu_buffer->write_stamp =
			cpu_buffer->commit_page->page->time_stamp;
		/* add barrier to keep gcc from optimizing too much */
		barrier();
	}
	while (rb_commit_index(cpu_buffer) !=
	       rb_page_write(cpu_buffer->commit_page)) {

		local_set(&cpu_buffer->commit_page->page->commit,
			  rb_page_write(cpu_buffer->commit_page));
		RB_WARN_ON(cpu_buffer,
			   local_read(&cpu_buffer->commit_page->page->commit) &
			   ~RB_WRITE_MASK);
		barrier();
	}

	/* again, keep gcc from optimizing */
	barrier();

	/*
	 * If an interrupt came in just after the first while loop
	 * and pushed the tail page forward, we will be left with
	 * a dangling commit that will never go forward.
	 */
	if (unlikely(cpu_buffer->commit_page != cpu_buffer->tail_page))
		goto again;
}