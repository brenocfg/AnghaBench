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
struct proc_dir_entry {int /*<<< orphan*/  name; int /*<<< orphan*/  count; } ;
struct nubus_dev {struct proc_dir_entry* procdir; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_bus_nubus_dir ; 
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nubus_proc_detach_device(struct nubus_dev *dev)
{
	struct proc_dir_entry *e;

	if ((e = dev->procdir)) {
		if (atomic_read(&e->count))
			return -EBUSY;
		remove_proc_entry(e->name, proc_bus_nubus_dir);
		dev->procdir = NULL;
	}
	return 0;
}