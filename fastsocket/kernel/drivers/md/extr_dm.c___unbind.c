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
struct mapped_device {int /*<<< orphan*/  map_lock; struct dm_table* map; } ;
struct dm_table {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dm_table_event_callback (struct dm_table*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct dm_table *__unbind(struct mapped_device *md)
{
	struct dm_table *map = md->map;
	unsigned long flags;

	if (!map)
		return NULL;

	dm_table_event_callback(map, NULL, NULL);
	write_lock_irqsave(&md->map_lock, flags);
	md->map = NULL;
	write_unlock_irqrestore(&md->map_lock, flags);

	return map;
}