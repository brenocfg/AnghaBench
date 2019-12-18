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
struct pid_namespace {int dummy; } ;
struct nameidata {int dummy; } ;
struct dentry {TYPE_1__* d_sb; } ;
typedef  int pid_t ;
struct TYPE_2__ {struct pid_namespace* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 char* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  current ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nd_set_link (struct nameidata*,char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int task_tgid_nr_ns (int /*<<< orphan*/ ,struct pid_namespace*) ; 

__attribute__((used)) static void *proc_self_follow_link(struct dentry *dentry, struct nameidata *nd)
{
	struct pid_namespace *ns = dentry->d_sb->s_fs_info;
	pid_t tgid = task_tgid_nr_ns(current, ns);
	char *name = ERR_PTR(-ENOENT);
	if (tgid) {
		/* 11 for max length of signed int in decimal + NULL term */
		name = kmalloc(12, GFP_KERNEL);
		if (!name)
			name = ERR_PTR(-ENOMEM);
		else
			sprintf(name, "%d", tgid);
	}
	nd_set_link(nd, name);
	return NULL;
}