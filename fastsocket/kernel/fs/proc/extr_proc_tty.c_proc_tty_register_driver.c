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
struct tty_driver {struct proc_dir_entry* proc_entry; TYPE_1__* ops; int /*<<< orphan*/  driver_name; } ;
struct proc_dir_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  proc_fops; } ;

/* Variables and functions */
 struct proc_dir_entry* proc_create_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tty_driver*) ; 
 int /*<<< orphan*/  proc_tty_driver ; 

void proc_tty_register_driver(struct tty_driver *driver)
{
	struct proc_dir_entry *ent;
		
	if (!driver->driver_name || driver->proc_entry ||
	    !driver->ops->proc_fops)
		return;

	ent = proc_create_data(driver->driver_name, 0, proc_tty_driver,
			       driver->ops->proc_fops, driver);
	driver->proc_entry = ent;
}