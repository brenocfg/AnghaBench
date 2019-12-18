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
struct dock_station {int /*<<< orphan*/  dd_lock; int /*<<< orphan*/  dependent_devices; } ;
struct dock_dependent_device {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
add_dock_dependent_device(struct dock_station *ds,
			  struct dock_dependent_device *dd)
{
	spin_lock(&ds->dd_lock);
	list_add_tail(&dd->list, &ds->dependent_devices);
	spin_unlock(&ds->dd_lock);
}