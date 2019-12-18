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
struct proc_dir_entry {int /*<<< orphan*/  count; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_proc_entry (struct proc_dir_entry*) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 

void de_put(struct proc_dir_entry *de)
{
	if (!atomic_read(&de->count)) {
		printk("de_put: entry %s already free!\n", de->name);
		return;
	}

	if (atomic_dec_and_test(&de->count))
		free_proc_entry(de);
}