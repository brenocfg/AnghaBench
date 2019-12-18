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
struct proc_dir_entry {int /*<<< orphan*/ * read_proc; void* data; } ;
struct ipmi_proc_entry {struct ipmi_proc_entry* next; struct ipmi_proc_entry* name; } ;
typedef  int /*<<< orphan*/  read_proc_t ;
typedef  TYPE_1__* ipmi_smi_t ;
struct TYPE_3__ {int /*<<< orphan*/  proc_entry_lock; struct ipmi_proc_entry* proc_entries; int /*<<< orphan*/  proc_dir; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct proc_dir_entry* create_proc_entry (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ipmi_proc_entry*) ; 
 void* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcpy (struct ipmi_proc_entry*,char*) ; 
 int strlen (char*) ; 

int ipmi_smi_add_proc_entry(ipmi_smi_t smi, char *name,
			    read_proc_t *read_proc,
			    void *data)
{
	int                    rv = 0;
#ifdef CONFIG_PROC_FS
	struct proc_dir_entry  *file;
	struct ipmi_proc_entry *entry;

	/* Create a list element. */
	entry = kmalloc(sizeof(*entry), GFP_KERNEL);
	if (!entry)
		return -ENOMEM;
	entry->name = kmalloc(strlen(name)+1, GFP_KERNEL);
	if (!entry->name) {
		kfree(entry);
		return -ENOMEM;
	}
	strcpy(entry->name, name);

	file = create_proc_entry(name, 0, smi->proc_dir);
	if (!file) {
		kfree(entry->name);
		kfree(entry);
		rv = -ENOMEM;
	} else {
		file->data = data;
		file->read_proc = read_proc;

		mutex_lock(&smi->proc_entry_lock);
		/* Stick it on the list. */
		entry->next = smi->proc_entries;
		smi->proc_entries = entry;
		mutex_unlock(&smi->proc_entry_lock);
	}
#endif /* CONFIG_PROC_FS */

	return rv;
}