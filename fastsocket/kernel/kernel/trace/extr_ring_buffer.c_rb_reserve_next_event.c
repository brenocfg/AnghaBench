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
typedef  scalar_t__ u64 ;
struct ring_buffer_per_cpu {scalar_t__ tail_page; scalar_t__ commit_page; scalar_t__ write_stamp; int /*<<< orphan*/  buffer; int /*<<< orphan*/  commits; int /*<<< orphan*/  committing; } ;
struct ring_buffer_event {scalar_t__ time_delta; } ;
struct ring_buffer {int dummy; } ;

/* Variables and functions */
 struct ring_buffer* ACCESS_ONCE (int /*<<< orphan*/ ) ; 
 int EAGAIN ; 
 int EBUSY ; 
 int PTR_ERR (struct ring_buffer_event*) ; 
 scalar_t__ RB_WARN_ON (struct ring_buffer_per_cpu*,int) ; 
 struct ring_buffer_event* __rb_reserve_next (struct ring_buffer_per_cpu*,int /*<<< orphan*/ ,unsigned long,scalar_t__*) ; 
 int /*<<< orphan*/  barrier () ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  local_dec (int /*<<< orphan*/ *) ; 
 int rb_add_time_stamp (struct ring_buffer_per_cpu*,scalar_t__*,scalar_t__*) ; 
 unsigned long rb_calculate_event_length (unsigned long) ; 
 scalar_t__ rb_commit_index (struct ring_buffer_per_cpu*) ; 
 int /*<<< orphan*/  rb_end_commit (struct ring_buffer_per_cpu*) ; 
 int /*<<< orphan*/  rb_event_is_commit (struct ring_buffer_per_cpu*,struct ring_buffer_event*) ; 
 scalar_t__ rb_page_write (scalar_t__) ; 
 int /*<<< orphan*/  rb_start_commit (struct ring_buffer_per_cpu*) ; 
 scalar_t__ rb_time_stamp (int /*<<< orphan*/ ) ; 
 int test_time_stamp (scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct ring_buffer_event *
rb_reserve_next_event(struct ring_buffer *buffer,
		      struct ring_buffer_per_cpu *cpu_buffer,
		      unsigned long length)
{
	struct ring_buffer_event *event;
	u64 ts, delta = 0;
	int commit = 0;
	int nr_loops = 0;

	rb_start_commit(cpu_buffer);

#ifdef CONFIG_RING_BUFFER_ALLOW_SWAP
	/*
	 * Due to the ability to swap a cpu buffer from a buffer
	 * it is possible it was swapped before we committed.
	 * (committing stops a swap). We check for it here and
	 * if it happened, we have to fail the write.
	 */
	barrier();
	if (unlikely(ACCESS_ONCE(cpu_buffer->buffer) != buffer)) {
		local_dec(&cpu_buffer->committing);
		local_dec(&cpu_buffer->commits);
		return NULL;
	}
#endif

	length = rb_calculate_event_length(length);
 again:
	/*
	 * We allow for interrupts to reenter here and do a trace.
	 * If one does, it will cause this original code to loop
	 * back here. Even with heavy interrupts happening, this
	 * should only happen a few times in a row. If this happens
	 * 1000 times in a row, there must be either an interrupt
	 * storm or we have something buggy.
	 * Bail!
	 */
	if (RB_WARN_ON(cpu_buffer, ++nr_loops > 1000))
		goto out_fail;

	ts = rb_time_stamp(cpu_buffer->buffer);

	/*
	 * Only the first commit can update the timestamp.
	 * Yes there is a race here. If an interrupt comes in
	 * just after the conditional and it traces too, then it
	 * will also check the deltas. More than one timestamp may
	 * also be made. But only the entry that did the actual
	 * commit will be something other than zero.
	 */
	if (likely(cpu_buffer->tail_page == cpu_buffer->commit_page &&
		   rb_page_write(cpu_buffer->tail_page) ==
		   rb_commit_index(cpu_buffer))) {
		u64 diff;

		diff = ts - cpu_buffer->write_stamp;

		/* make sure this diff is calculated here */
		barrier();

		/* Did the write stamp get updated already? */
		if (unlikely(ts < cpu_buffer->write_stamp))
			goto get_event;

		delta = diff;
		if (unlikely(test_time_stamp(delta))) {

			commit = rb_add_time_stamp(cpu_buffer, &ts, &delta);
			if (commit == -EBUSY)
				goto out_fail;

			if (commit == -EAGAIN)
				goto again;

			RB_WARN_ON(cpu_buffer, commit < 0);
		}
	}

 get_event:
	event = __rb_reserve_next(cpu_buffer, 0, length, &ts);
	if (unlikely(PTR_ERR(event) == -EAGAIN))
		goto again;

	if (!event)
		goto out_fail;

	if (!rb_event_is_commit(cpu_buffer, event))
		delta = 0;

	event->time_delta = delta;

	return event;

 out_fail:
	rb_end_commit(cpu_buffer);
	return NULL;
}