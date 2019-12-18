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
struct dock_station {int /*<<< orphan*/  hp_lock; int /*<<< orphan*/  hotplug_devices; } ;
struct dock_dependent_device {int /*<<< orphan*/  hotplug_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
dock_add_hotplug_device(struct dock_station *ds,
			struct dock_dependent_device *dd)
{
	mutex_lock(&ds->hp_lock);
	list_add_tail(&dd->hotplug_list, &ds->hotplug_devices);
	mutex_unlock(&ds->hp_lock);
}