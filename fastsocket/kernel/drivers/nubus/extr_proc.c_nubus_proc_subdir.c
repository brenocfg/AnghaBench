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
struct nubus_dirent {int type; } ;
struct nubus_dir {int dummy; } ;
struct nubus_dev {int dummy; } ;

/* Variables and functions */
 int S_IFREG ; 
 int S_IRUGO ; 
 int S_IWUSR ; 
 struct proc_dir_entry* create_proc_entry (char*,int,struct proc_dir_entry*) ; 
 int nubus_readdir (struct nubus_dir*,struct nubus_dirent*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static void nubus_proc_subdir(struct nubus_dev* dev,
			      struct proc_dir_entry* parent,
			      struct nubus_dir* dir)
{
	struct nubus_dirent ent;

	/* Some of these are directories, others aren't */
	while (nubus_readdir(dir, &ent) != -1) {
		char name[8];
		struct proc_dir_entry* e;
		
		sprintf(name, "%x", ent.type);
		e = create_proc_entry(name, S_IFREG | S_IRUGO |
				      S_IWUSR, parent);
		if (!e) return;
	}
}