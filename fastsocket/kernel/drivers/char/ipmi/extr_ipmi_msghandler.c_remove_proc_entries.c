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
struct ipmi_proc_entry {struct ipmi_proc_entry* name; struct ipmi_proc_entry* next; } ;
typedef  TYPE_1__* ipmi_smi_t ;
struct TYPE_3__ {struct ipmi_proc_entry* proc_dir_name; int /*<<< orphan*/  proc_entry_lock; int /*<<< orphan*/  proc_dir; struct ipmi_proc_entry* proc_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct ipmi_proc_entry*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_ipmi_root ; 
 int /*<<< orphan*/  remove_proc_entry (struct ipmi_proc_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_proc_entries(ipmi_smi_t smi)
{
#ifdef CONFIG_PROC_FS
	struct ipmi_proc_entry *entry;

	mutex_lock(&smi->proc_entry_lock);
	while (smi->proc_entries) {
		entry = smi->proc_entries;
		smi->proc_entries = entry->next;

		remove_proc_entry(entry->name, smi->proc_dir);
		kfree(entry->name);
		kfree(entry);
	}
	mutex_unlock(&smi->proc_entry_lock);
	remove_proc_entry(smi->proc_dir_name, proc_ipmi_root);
#endif /* CONFIG_PROC_FS */
}