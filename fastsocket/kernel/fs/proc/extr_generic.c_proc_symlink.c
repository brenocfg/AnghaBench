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
struct proc_dir_entry {struct proc_dir_entry* data; int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int S_IFLNK ; 
 int S_IRUGO ; 
 int S_IWUGO ; 
 int S_IXUGO ; 
 struct proc_dir_entry* __proc_create (struct proc_dir_entry**,char const*,int,int) ; 
 int /*<<< orphan*/  kfree (struct proc_dir_entry*) ; 
 struct proc_dir_entry* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ proc_register (struct proc_dir_entry*,struct proc_dir_entry*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

struct proc_dir_entry *proc_symlink(const char *name,
		struct proc_dir_entry *parent, const char *dest)
{
	struct proc_dir_entry *ent;

	ent = __proc_create(&parent, name,
			  (S_IFLNK | S_IRUGO | S_IWUGO | S_IXUGO),1);

	if (ent) {
		ent->data = kmalloc((ent->size=strlen(dest))+1, GFP_KERNEL);
		if (ent->data) {
			strcpy((char*)ent->data,dest);
			if (proc_register(parent, ent) < 0) {
				kfree(ent->data);
				kfree(ent);
				ent = NULL;
			}
		} else {
			kfree(ent);
			ent = NULL;
		}
	}
	return ent;
}