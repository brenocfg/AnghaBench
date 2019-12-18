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
struct tty_driver {struct proc_dir_entry* proc_entry; int /*<<< orphan*/  driver_name; } ;
struct proc_dir_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  proc_tty_driver ; 
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void proc_tty_unregister_driver(struct tty_driver *driver)
{
	struct proc_dir_entry *ent;

	ent = driver->proc_entry;
	if (!ent)
		return;
		
	remove_proc_entry(driver->driver_name, proc_tty_driver);
	
	driver->proc_entry = NULL;
}