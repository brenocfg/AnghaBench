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
struct ring_buffer_per_cpu {struct buffer_page* tail_page; } ;
struct buffer_page {TYPE_1__* page; int /*<<< orphan*/  entries; int /*<<< orphan*/  write; } ;
struct TYPE_2__ {int /*<<< orphan*/  commit; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_WRITE_INTCNT ; 
 unsigned long RB_WRITE_MASK ; 
 int /*<<< orphan*/  barrier () ; 
 struct buffer_page* cmpxchg (struct buffer_page**,struct buffer_page*,struct buffer_page*) ; 
 unsigned long local_add_return (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_cmpxchg (int /*<<< orphan*/ *,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  local_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rb_tail_page_update(struct ring_buffer_per_cpu *cpu_buffer,
			       struct buffer_page *tail_page,
			       struct buffer_page *next_page)
{
	struct buffer_page *old_tail;
	unsigned long old_entries;
	unsigned long old_write;
	int ret = 0;

	/*
	 * The tail page now needs to be moved forward.
	 *
	 * We need to reset the tail page, but without messing
	 * with possible erasing of data brought in by interrupts
	 * that have moved the tail page and are currently on it.
	 *
	 * We add a counter to the write field to denote this.
	 */
	old_write = local_add_return(RB_WRITE_INTCNT, &next_page->write);
	old_entries = local_add_return(RB_WRITE_INTCNT, &next_page->entries);

	/*
	 * Just make sure we have seen our old_write and synchronize
	 * with any interrupts that come in.
	 */
	barrier();

	/*
	 * If the tail page is still the same as what we think
	 * it is, then it is up to us to update the tail
	 * pointer.
	 */
	if (tail_page == cpu_buffer->tail_page) {
		/* Zero the write counter */
		unsigned long val = old_write & ~RB_WRITE_MASK;
		unsigned long eval = old_entries & ~RB_WRITE_MASK;

		/*
		 * This will only succeed if an interrupt did
		 * not come in and change it. In which case, we
		 * do not want to modify it.
		 *
		 * We add (void) to let the compiler know that we do not care
		 * about the return value of these functions. We use the
		 * cmpxchg to only update if an interrupt did not already
		 * do it for us. If the cmpxchg fails, we don't care.
		 */
		(void)local_cmpxchg(&next_page->write, old_write, val);
		(void)local_cmpxchg(&next_page->entries, old_entries, eval);

		/*
		 * No need to worry about races with clearing out the commit.
		 * it only can increment when a commit takes place. But that
		 * only happens in the outer most nested commit.
		 */
		local_set(&next_page->page->commit, 0);

		old_tail = cmpxchg(&cpu_buffer->tail_page,
				   tail_page, next_page);

		if (old_tail == tail_page)
			ret = 1;
	}

	return ret;
}