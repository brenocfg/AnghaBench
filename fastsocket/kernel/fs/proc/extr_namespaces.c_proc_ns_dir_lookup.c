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
struct task_struct {int dummy; } ;
struct proc_ns_operations {int /*<<< orphan*/  name; } ;
struct nameidata {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {unsigned int len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct proc_ns_operations**) ; 
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct task_struct* get_proc_task (struct inode*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 struct proc_ns_operations** ns_entries ; 
 struct dentry* proc_ns_instantiate (struct inode*,struct dentry*,struct task_struct*,struct proc_ns_operations const*) ; 
 int /*<<< orphan*/  put_task_struct (struct task_struct*) ; 
 unsigned int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct dentry *proc_ns_dir_lookup(struct inode *dir,
				struct dentry *dentry, struct nameidata *nd)
{
	struct dentry *error;
	struct task_struct *task = get_proc_task(dir);
	const struct proc_ns_operations **entry, **last;
	unsigned int len = dentry->d_name.len;

	error = ERR_PTR(-ENOENT);

	if (!task)
		goto out_no_task;

	last = &ns_entries[ARRAY_SIZE(ns_entries)];
	for (entry = ns_entries; entry < last; entry++) {
		if (strlen((*entry)->name) != len)
			continue;
		if (!memcmp(dentry->d_name.name, (*entry)->name, len))
			break;
	}
	if (entry == last)
		goto out;

	error = proc_ns_instantiate(dir, dentry, task, *entry);
out:
	put_task_struct(task);
out_no_task:
	return error;
}