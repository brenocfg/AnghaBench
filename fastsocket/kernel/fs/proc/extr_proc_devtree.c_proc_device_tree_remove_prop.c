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
struct property {int /*<<< orphan*/  name; } ;
struct proc_dir_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  remove_proc_entry (int /*<<< orphan*/ ,struct proc_dir_entry*) ; 

void proc_device_tree_remove_prop(struct proc_dir_entry *pde,
				  struct property *prop)
{
	remove_proc_entry(prop->name, pde);
}