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
struct thin_c {TYPE_1__* pool; } ;
struct dm_thin_new_mapping {int /*<<< orphan*/  bio; int /*<<< orphan*/  data_block; scalar_t__ definitely_not_shared; scalar_t__ pass_discard; int /*<<< orphan*/  cell2; int /*<<< orphan*/  cell; struct thin_c* tc; } ;
struct TYPE_2__ {int /*<<< orphan*/  mapping_pool; int /*<<< orphan*/  pmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_endio (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cell_defer_no_holder (struct thin_c*,int /*<<< orphan*/ ) ; 
 scalar_t__ dm_pool_block_is_used (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  inc_all_io_entry (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct dm_thin_new_mapping*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remap_and_issue (struct thin_c*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_prepared_discard_passdown(struct dm_thin_new_mapping *m)
{
	struct thin_c *tc = m->tc;

	inc_all_io_entry(tc->pool, m->bio);
	cell_defer_no_holder(tc, m->cell);
	cell_defer_no_holder(tc, m->cell2);

	if (m->pass_discard)
		if (m->definitely_not_shared)
			remap_and_issue(tc, m->bio, m->data_block);
		else {
			bool used = false;
			if (dm_pool_block_is_used(tc->pool->pmd, m->data_block, &used) || used)
				bio_endio(m->bio, 0);
			else
				remap_and_issue(tc, m->bio, m->data_block);
		}
	else
		bio_endio(m->bio, 0);

	mempool_free(m, tc->pool->mapping_pool);
}