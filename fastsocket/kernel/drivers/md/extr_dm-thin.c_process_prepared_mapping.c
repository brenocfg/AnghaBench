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
struct thin_c {int /*<<< orphan*/  td; struct pool* pool; } ;
struct pool {int /*<<< orphan*/  mapping_pool; } ;
struct dm_thin_new_mapping {int /*<<< orphan*/  list; int /*<<< orphan*/  cell; int /*<<< orphan*/  data_block; int /*<<< orphan*/  virt_block; scalar_t__ err; int /*<<< orphan*/  saved_bi_end_io; struct bio* bio; struct thin_c* tc; } ;
struct bio {int /*<<< orphan*/  bi_end_io; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_endio (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cell_defer (struct thin_c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cell_defer_no_holder (struct thin_c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cell_error (struct pool*,int /*<<< orphan*/ ) ; 
 int dm_thin_insert_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mempool_free (struct dm_thin_new_mapping*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  metadata_operation_failed (struct pool*,char*,int) ; 

__attribute__((used)) static void process_prepared_mapping(struct dm_thin_new_mapping *m)
{
	struct thin_c *tc = m->tc;
	struct pool *pool = tc->pool;
	struct bio *bio;
	int r;

	bio = m->bio;
	if (bio)
		bio->bi_end_io = m->saved_bi_end_io;

	if (m->err) {
		cell_error(pool, m->cell);
		goto out;
	}

	/*
	 * Commit the prepared block into the mapping btree.
	 * Any I/O for this block arriving after this point will get
	 * remapped to it directly.
	 */
	r = dm_thin_insert_block(tc->td, m->virt_block, m->data_block);
	if (r) {
		metadata_operation_failed(pool, "dm_thin_insert_block", r);
		cell_error(pool, m->cell);
		goto out;
	}

	/*
	 * Release any bios held while the block was being provisioned.
	 * If we are processing a write bio that completely covers the block,
	 * we already processed it so can ignore it now when processing
	 * the bios in the cell.
	 */
	if (bio) {
		cell_defer_no_holder(tc, m->cell);
		bio_endio(bio, 0);
	} else
		cell_defer(tc, m->cell);

out:
	list_del(&m->list);
	mempool_free(m, pool->mapping_pool);
}