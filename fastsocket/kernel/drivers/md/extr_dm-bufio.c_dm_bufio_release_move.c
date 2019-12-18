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
struct dm_bufio_client {int dummy; } ;
struct dm_buffer {int hold_count; int /*<<< orphan*/  list_mode; int /*<<< orphan*/  state; int /*<<< orphan*/  block; struct dm_bufio_client* c; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  B_DIRTY ; 
 int /*<<< orphan*/  B_READING ; 
 int /*<<< orphan*/  B_WRITING ; 
 int /*<<< orphan*/  LIST_DIRTY ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  WRITE ; 
 struct dm_buffer* __find (struct dm_bufio_client*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __free_buffer_wake (struct dm_buffer*) ; 
 int /*<<< orphan*/  __link_buffer (struct dm_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __make_buffer_clean (struct dm_buffer*) ; 
 int /*<<< orphan*/  __unlink_buffer (struct dm_buffer*) ; 
 int /*<<< orphan*/  __wait_for_free_buffer (struct dm_bufio_client*) ; 
 int /*<<< orphan*/  __write_dirty_buffer (struct dm_buffer*,int /*<<< orphan*/ *) ; 
 int dm_bufio_in_request () ; 
 int /*<<< orphan*/  dm_bufio_lock (struct dm_bufio_client*) ; 
 int /*<<< orphan*/  dm_bufio_release (struct dm_buffer*) ; 
 int /*<<< orphan*/  dm_bufio_unlock (struct dm_bufio_client*) ; 
 int /*<<< orphan*/  do_io_schedule ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  submit_io (struct dm_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_on_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_on_bit_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_endio ; 

void dm_bufio_release_move(struct dm_buffer *b, sector_t new_block)
{
	struct dm_bufio_client *c = b->c;
	struct dm_buffer *new;

	BUG_ON(dm_bufio_in_request());

	dm_bufio_lock(c);

retry:
	new = __find(c, new_block);
	if (new) {
		if (new->hold_count) {
			__wait_for_free_buffer(c);
			goto retry;
		}

		/*
		 * FIXME: Is there any point waiting for a write that's going
		 * to be overwritten in a bit?
		 */
		__make_buffer_clean(new);
		__unlink_buffer(new);
		__free_buffer_wake(new);
	}

	BUG_ON(!b->hold_count);
	BUG_ON(test_bit(B_READING, &b->state));

	__write_dirty_buffer(b, NULL);
	if (b->hold_count == 1) {
		wait_on_bit(&b->state, B_WRITING,
			    do_io_schedule, TASK_UNINTERRUPTIBLE);
		set_bit(B_DIRTY, &b->state);
		__unlink_buffer(b);
		__link_buffer(b, new_block, LIST_DIRTY);
	} else {
		sector_t old_block;
		wait_on_bit_lock(&b->state, B_WRITING,
				 do_io_schedule, TASK_UNINTERRUPTIBLE);
		/*
		 * Relink buffer to "new_block" so that write_callback
		 * sees "new_block" as a block number.
		 * After the write, link the buffer back to old_block.
		 * All this must be done in bufio lock, so that block number
		 * change isn't visible to other threads.
		 */
		old_block = b->block;
		__unlink_buffer(b);
		__link_buffer(b, new_block, b->list_mode);
		submit_io(b, WRITE, new_block, write_endio);
		wait_on_bit(&b->state, B_WRITING,
			    do_io_schedule, TASK_UNINTERRUPTIBLE);
		__unlink_buffer(b);
		__link_buffer(b, old_block, b->list_mode);
	}

	dm_bufio_unlock(c);
	dm_bufio_release(b);
}