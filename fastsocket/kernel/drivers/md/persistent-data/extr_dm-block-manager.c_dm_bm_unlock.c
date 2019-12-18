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
struct dm_block {int dummy; } ;
struct buffer_aux {int /*<<< orphan*/  lock; scalar_t__ write_locked; } ;

/* Variables and functions */
 int /*<<< orphan*/  bl_up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bl_up_write (int /*<<< orphan*/ *) ; 
 struct buffer_aux* dm_bufio_get_aux_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_bufio_mark_buffer_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_bufio_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_buffer (struct dm_block*) ; 

int dm_bm_unlock(struct dm_block *b)
{
	struct buffer_aux *aux;
	aux = dm_bufio_get_aux_data(to_buffer(b));

	if (aux->write_locked) {
		dm_bufio_mark_buffer_dirty(to_buffer(b));
		bl_up_write(&aux->lock);
	} else
		bl_up_read(&aux->lock);

	dm_bufio_release(to_buffer(b));

	return 0;
}