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
struct dm_bufio_client {scalar_t__ block_size; scalar_t__ aux_size; } ;
struct dm_buffer {int /*<<< orphan*/  data_mode; int /*<<< orphan*/  data; struct dm_bufio_client* c; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  adjust_total_allocated (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  alloc_buffer_data (struct dm_bufio_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct dm_buffer*) ; 
 struct dm_buffer* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dm_buffer *alloc_buffer(struct dm_bufio_client *c, gfp_t gfp_mask)
{
	struct dm_buffer *b = kmalloc(sizeof(struct dm_buffer) + c->aux_size,
				      gfp_mask);

	if (!b)
		return NULL;

	b->c = c;

	b->data = alloc_buffer_data(c, gfp_mask, &b->data_mode);
	if (!b->data) {
		kfree(b);
		return NULL;
	}

	adjust_total_allocated(b->data_mode, (long)c->block_size);

	return b;
}