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
struct dm_thin_new_mapping {int /*<<< orphan*/  cell2; int /*<<< orphan*/  cell; int /*<<< orphan*/  bio; struct thin_c* tc; } ;
struct TYPE_2__ {int /*<<< orphan*/  mapping_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_io_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cell_defer_no_holder (struct thin_c*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct dm_thin_new_mapping*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_prepared_discard_fail(struct dm_thin_new_mapping *m)
{
	struct thin_c *tc = m->tc;

	bio_io_error(m->bio);
	cell_defer_no_holder(tc, m->cell);
	cell_defer_no_holder(tc, m->cell2);
	mempool_free(m, tc->pool->mapping_pool);
}