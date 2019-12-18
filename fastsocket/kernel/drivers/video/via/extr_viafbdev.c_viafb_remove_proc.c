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
struct proc_dir_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  remove_proc_entry (char*,struct proc_dir_entry*) ; 

__attribute__((used)) static void viafb_remove_proc(struct proc_dir_entry *viafb_entry)
{
	/* no problem if it was not registered */
	remove_proc_entry("dvp0", viafb_entry);/* parent dir */
	remove_proc_entry("dvp1", viafb_entry);
	remove_proc_entry("dfph", viafb_entry);
	remove_proc_entry("dfpl", viafb_entry);
	remove_proc_entry("vt1636", viafb_entry);
	remove_proc_entry("vt1625", viafb_entry);
	remove_proc_entry("viafb", NULL);
}