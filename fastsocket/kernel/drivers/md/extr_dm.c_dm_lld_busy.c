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
struct request_queue {struct mapped_device* queuedata; } ;
struct mapped_device {int /*<<< orphan*/  flags; } ;
struct dm_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMF_BLOCK_IO_FOR_SUSPEND ; 
 struct dm_table* dm_get_live_table (struct mapped_device*) ; 
 int dm_table_any_busy_target (struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_put (struct dm_table*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dm_lld_busy(struct request_queue *q)
{
	int r;
	struct mapped_device *md = q->queuedata;
	struct dm_table *map = dm_get_live_table(md);

	if (!map || test_bit(DMF_BLOCK_IO_FOR_SUSPEND, &md->flags))
		r = 1;
	else
		r = dm_table_any_busy_target(map);

	dm_table_put(map);

	return r;
}