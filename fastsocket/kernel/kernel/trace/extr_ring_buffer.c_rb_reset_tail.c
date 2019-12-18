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
struct ring_buffer_per_cpu {int dummy; } ;
struct ring_buffer_event {unsigned long* array; int time_delta; int /*<<< orphan*/  type_len; } ;
struct buffer_page {int /*<<< orphan*/  write; } ;

/* Variables and functions */
 unsigned long BUF_PAGE_SIZE ; 
 unsigned long RB_EVNT_HDR_SIZE ; 
 unsigned long RB_EVNT_MIN_SIZE ; 
 int /*<<< orphan*/  RINGBUF_TYPE_PADDING ; 
 struct ring_buffer_event* __rb_page_index (struct buffer_page*,unsigned long) ; 
 int /*<<< orphan*/  bitfield ; 
 int /*<<< orphan*/  kmemcheck_annotate_bitfield (struct ring_buffer_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_sub (unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_event_set_padding (struct ring_buffer_event*) ; 

__attribute__((used)) static inline void
rb_reset_tail(struct ring_buffer_per_cpu *cpu_buffer,
	      struct buffer_page *tail_page,
	      unsigned long tail, unsigned long length)
{
	struct ring_buffer_event *event;

	/*
	 * Only the event that crossed the page boundary
	 * must fill the old tail_page with padding.
	 */
	if (tail >= BUF_PAGE_SIZE) {
		local_sub(length, &tail_page->write);
		return;
	}

	event = __rb_page_index(tail_page, tail);
	kmemcheck_annotate_bitfield(event, bitfield);

	/*
	 * If this event is bigger than the minimum size, then
	 * we need to be careful that we don't subtract the
	 * write counter enough to allow another writer to slip
	 * in on this page.
	 * We put in a discarded commit instead, to make sure
	 * that this space is not used again.
	 *
	 * If we are less than the minimum size, we don't need to
	 * worry about it.
	 */
	if (tail > (BUF_PAGE_SIZE - RB_EVNT_MIN_SIZE)) {
		/* No room for any events */

		/* Mark the rest of the page with padding */
		rb_event_set_padding(event);

		/* Set the write back to the previous setting */
		local_sub(length, &tail_page->write);
		return;
	}

	/* Put in a discarded event */
	event->array[0] = (BUF_PAGE_SIZE - tail) - RB_EVNT_HDR_SIZE;
	event->type_len = RINGBUF_TYPE_PADDING;
	/* time delta must be non zero */
	event->time_delta = 1;

	/* Set write to end of buffer */
	length = (tail + length) - BUF_PAGE_SIZE;
	local_sub(length, &tail_page->write);
}