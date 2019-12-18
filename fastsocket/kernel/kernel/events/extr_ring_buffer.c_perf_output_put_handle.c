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
struct ring_buffer {int /*<<< orphan*/  wakeup; int /*<<< orphan*/  nest; int /*<<< orphan*/  head; TYPE_1__* user_page; } ;
struct perf_output_handle {unsigned long wakeup; struct ring_buffer* rb; } ;
struct TYPE_2__ {unsigned long data_head; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  local_inc (int /*<<< orphan*/ *) ; 
 unsigned long local_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  perf_output_wakeup (struct perf_output_handle*) ; 
 int /*<<< orphan*/  preempt_enable () ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void perf_output_put_handle(struct perf_output_handle *handle)
{
	struct ring_buffer *rb = handle->rb;
	unsigned long head;

again:
	head = local_read(&rb->head);

	/*
	 * IRQ/NMI can happen here, which means we can miss a head update.
	 */

	if (!local_dec_and_test(&rb->nest))
		goto out;

	/*
	 * Publish the known good head. Rely on the full barrier implied
	 * by atomic_dec_and_test() order the rb->head read and this
	 * write.
	 */
	rb->user_page->data_head = head;

	/*
	 * Now check if we missed an update, rely on the (compiler)
	 * barrier in atomic_dec_and_test() to re-read rb->head.
	 */
	if (unlikely(head != local_read(&rb->head))) {
		local_inc(&rb->nest);
		goto again;
	}

	if (handle->wakeup != local_read(&rb->wakeup))
		perf_output_wakeup(handle);

out:
	preempt_enable();
}