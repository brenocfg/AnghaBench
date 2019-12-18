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
struct mapped_device {int dummy; } ;
struct dm_table {int dummy; } ;

/* Variables and functions */
 struct dm_table* dm_get_live_table (struct mapped_device*) ; 
 scalar_t__ dm_request_based (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_table_put (struct dm_table*) ; 
 int /*<<< orphan*/  dm_table_unplug_all (struct dm_table*) ; 
 int /*<<< orphan*/  generic_unplug_device (struct request_queue*) ; 

__attribute__((used)) static void dm_unplug_all(struct request_queue *q)
{
	struct mapped_device *md = q->queuedata;
	struct dm_table *map = dm_get_live_table(md);

	if (map) {
		if (dm_request_based(md))
			generic_unplug_device(q);

		dm_table_unplug_all(map);
		dm_table_put(map);
	}
}