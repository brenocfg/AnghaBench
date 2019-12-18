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
typedef  int /*<<< orphan*/  u64 ;
struct ring_buffer_per_cpu {scalar_t__ commit_page; scalar_t__ tail_page; scalar_t__ reader_page; int /*<<< orphan*/  commit_overrun; struct ring_buffer* buffer; } ;
struct ring_buffer_event {int dummy; } ;
struct ring_buffer {int flags; } ;
struct buffer_page {TYPE_1__* page; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  time_stamp; } ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 struct ring_buffer_event* ERR_PTR (int /*<<< orphan*/ ) ; 
 int RB_FL_OVERWRITE ; 
 int /*<<< orphan*/  local_inc (int /*<<< orphan*/ *) ; 
 int rb_handle_head_page (struct ring_buffer_per_cpu*,struct buffer_page*,struct buffer_page*) ; 
 int /*<<< orphan*/  rb_inc_page (struct ring_buffer_per_cpu*,struct buffer_page**) ; 
 scalar_t__ rb_is_head_page (struct ring_buffer_per_cpu*,struct buffer_page*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_is_reader_page (scalar_t__) ; 
 int /*<<< orphan*/  rb_reset_tail (struct ring_buffer_per_cpu*,struct buffer_page*,unsigned long,unsigned long) ; 
 int rb_tail_page_update (struct ring_buffer_per_cpu*,struct buffer_page*,struct buffer_page*) ; 
 int /*<<< orphan*/  rb_time_stamp (struct ring_buffer*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct ring_buffer_event *
rb_move_tail(struct ring_buffer_per_cpu *cpu_buffer,
	     unsigned long length, unsigned long tail,
	     struct buffer_page *commit_page,
	     struct buffer_page *tail_page, u64 *ts)
{
	struct ring_buffer *buffer = cpu_buffer->buffer;
	struct buffer_page *next_page;
	int ret;

	next_page = tail_page;

	rb_inc_page(cpu_buffer, &next_page);

	/*
	 * If for some reason, we had an interrupt storm that made
	 * it all the way around the buffer, bail, and warn
	 * about it.
	 */
	if (unlikely(next_page == commit_page)) {
		local_inc(&cpu_buffer->commit_overrun);
		goto out_reset;
	}

	/*
	 * This is where the fun begins!
	 *
	 * We are fighting against races between a reader that
	 * could be on another CPU trying to swap its reader
	 * page with the buffer head.
	 *
	 * We are also fighting against interrupts coming in and
	 * moving the head or tail on us as well.
	 *
	 * If the next page is the head page then we have filled
	 * the buffer, unless the commit page is still on the
	 * reader page.
	 */
	if (rb_is_head_page(cpu_buffer, next_page, &tail_page->list)) {

		/*
		 * If the commit is not on the reader page, then
		 * move the header page.
		 */
		if (!rb_is_reader_page(cpu_buffer->commit_page)) {
			/*
			 * If we are not in overwrite mode,
			 * this is easy, just stop here.
			 */
			if (!(buffer->flags & RB_FL_OVERWRITE))
				goto out_reset;

			ret = rb_handle_head_page(cpu_buffer,
						  tail_page,
						  next_page);
			if (ret < 0)
				goto out_reset;
			if (ret)
				goto out_again;
		} else {
			/*
			 * We need to be careful here too. The
			 * commit page could still be on the reader
			 * page. We could have a small buffer, and
			 * have filled up the buffer with events
			 * from interrupts and such, and wrapped.
			 *
			 * Note, if the tail page is also the on the
			 * reader_page, we let it move out.
			 */
			if (unlikely((cpu_buffer->commit_page !=
				      cpu_buffer->tail_page) &&
				     (cpu_buffer->commit_page ==
				      cpu_buffer->reader_page))) {
				local_inc(&cpu_buffer->commit_overrun);
				goto out_reset;
			}
		}
	}

	ret = rb_tail_page_update(cpu_buffer, tail_page, next_page);
	if (ret) {
		/*
		 * Nested commits always have zero deltas, so
		 * just reread the time stamp
		 */
		*ts = rb_time_stamp(buffer);
		next_page->page->time_stamp = *ts;
	}

 out_again:

	rb_reset_tail(cpu_buffer, tail_page, tail, length);

	/* fail and let the caller try again */
	return ERR_PTR(-EAGAIN);

 out_reset:
	/* reset write */
	rb_reset_tail(cpu_buffer, tail_page, tail, length);

	return NULL;
}