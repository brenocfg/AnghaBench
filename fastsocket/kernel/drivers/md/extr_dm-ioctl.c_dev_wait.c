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
struct mapped_device {int dummy; } ;
struct dm_table {int dummy; } ;
struct dm_ioctl {int /*<<< orphan*/  event_nr; } ;

/* Variables and functions */
 int ENXIO ; 
 int ERESTARTSYS ; 
 int /*<<< orphan*/  __dev_status (struct mapped_device*,struct dm_ioctl*) ; 
 struct dm_table* dm_get_live_or_inactive_table (struct mapped_device*,struct dm_ioctl*) ; 
 int /*<<< orphan*/  dm_put (struct mapped_device*) ; 
 int /*<<< orphan*/  dm_table_put (struct dm_table*) ; 
 scalar_t__ dm_wait_event (struct mapped_device*,int /*<<< orphan*/ ) ; 
 struct mapped_device* find_device (struct dm_ioctl*) ; 
 int /*<<< orphan*/  retrieve_status (struct dm_table*,struct dm_ioctl*,size_t) ; 

__attribute__((used)) static int dev_wait(struct dm_ioctl *param, size_t param_size)
{
	int r = 0;
	struct mapped_device *md;
	struct dm_table *table;

	md = find_device(param);
	if (!md)
		return -ENXIO;

	/*
	 * Wait for a notification event
	 */
	if (dm_wait_event(md, param->event_nr)) {
		r = -ERESTARTSYS;
		goto out;
	}

	/*
	 * The userland program is going to want to know what
	 * changed to trigger the event, so we may as well tell
	 * him and save an ioctl.
	 */
	__dev_status(md, param);

	table = dm_get_live_or_inactive_table(md, param);
	if (table) {
		retrieve_status(table, param, param_size);
		dm_table_put(table);
	}

out:
	dm_put(md);

	return r;
}