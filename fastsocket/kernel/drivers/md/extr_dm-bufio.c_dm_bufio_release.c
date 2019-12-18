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
struct dm_bufio_client {int /*<<< orphan*/  free_buffer_wait; } ;
struct dm_buffer {int /*<<< orphan*/  state; scalar_t__ write_error; scalar_t__ read_error; int /*<<< orphan*/  hold_count; struct dm_bufio_client* c; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  B_DIRTY ; 
 int /*<<< orphan*/  B_READING ; 
 int /*<<< orphan*/  B_WRITING ; 
 int /*<<< orphan*/  __free_buffer_wake (struct dm_buffer*) ; 
 int /*<<< orphan*/  __unlink_buffer (struct dm_buffer*) ; 
 int /*<<< orphan*/  dm_bufio_lock (struct dm_bufio_client*) ; 
 int /*<<< orphan*/  dm_bufio_unlock (struct dm_bufio_client*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

void dm_bufio_release(struct dm_buffer *b)
{
	struct dm_bufio_client *c = b->c;

	dm_bufio_lock(c);

	BUG_ON(!b->hold_count);

	b->hold_count--;
	if (!b->hold_count) {
		wake_up(&c->free_buffer_wait);

		/*
		 * If there were errors on the buffer, and the buffer is not
		 * to be written, free the buffer. There is no point in caching
		 * invalid buffer.
		 */
		if ((b->read_error || b->write_error) &&
		    !test_bit(B_READING, &b->state) &&
		    !test_bit(B_WRITING, &b->state) &&
		    !test_bit(B_DIRTY, &b->state)) {
			__unlink_buffer(b);
			__free_buffer_wake(b);
		}
	}

	dm_bufio_unlock(c);
}