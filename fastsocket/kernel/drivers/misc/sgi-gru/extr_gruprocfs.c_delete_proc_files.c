#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct proc_entry {char* name; scalar_t__ entry; } ;
struct TYPE_3__ {struct TYPE_3__* parent; } ;

/* Variables and functions */
 struct proc_entry* proc_files ; 
 TYPE_1__* proc_gru ; 
 int /*<<< orphan*/  remove_proc_entry (char*,TYPE_1__*) ; 

__attribute__((used)) static void delete_proc_files(void)
{
	struct proc_entry *p;

	if (proc_gru) {
		for (p = proc_files; p->name; p++)
			if (p->entry)
				remove_proc_entry(p->name, proc_gru);
		remove_proc_entry("gru", proc_gru->parent);
	}
}