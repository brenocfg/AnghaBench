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
struct proc_dir_entry {int /*<<< orphan*/ * write_proc; int /*<<< orphan*/  read_proc; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int S_IFREG ; 
 int S_IRUGO ; 
 struct proc_dir_entry* create_proc_entry (char*,int,struct proc_dir_entry*) ; 
 int /*<<< orphan*/  make_proc_ide () ; 
 int /*<<< orphan*/  proc_ide ; 
 int /*<<< orphan*/  proc_ide_read_media ; 
 int /*<<< orphan*/ * proc_ide_root ; 
 struct proc_dir_entry* proc_mkdir (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  proc_symlink (char const*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 

__attribute__((used)) static void make_ide_entries(const char *dev_name)
{
	struct proc_dir_entry *dir, *ent;
	char name[64];

	if(proc_ide_root == NULL) make_proc_ide();

	dir = proc_mkdir(dev_name, proc_ide);
	if(!dir) return;

	ent = create_proc_entry("media", S_IFREG|S_IRUGO, dir);
	if(!ent) return;
	ent->data = NULL;
	ent->read_proc = proc_ide_read_media;
	ent->write_proc = NULL;
	snprintf(name, sizeof(name), "ide0/%s", dev_name);
	proc_symlink(dev_name, proc_ide_root, name);
}