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
struct proc_ns_operations {int /*<<< orphan*/  (* put ) (void*) ;} ;
struct proc_dir_entry {int dummy; } ;
struct inode {int /*<<< orphan*/  i_data; } ;
struct TYPE_2__ {void* ns; struct proc_ns_operations* ns_ops; scalar_t__ sysctl; struct proc_dir_entry* pde; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 TYPE_1__* PROC_I (struct inode*) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  de_put (struct proc_dir_entry*) ; 
 int /*<<< orphan*/  put_pid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 int /*<<< orphan*/  sysctl_head_put (scalar_t__) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void proc_delete_inode(struct inode *inode)
{
	struct proc_dir_entry *de;
	const struct proc_ns_operations *ns_ops;
	void *ns;

	truncate_inode_pages(&inode->i_data, 0);

	/* Stop tracking associated processes */
	put_pid(PROC_I(inode)->pid);

	/* Let go of any associated proc directory entry */
	de = PROC_I(inode)->pde;
	if (de)
		de_put(de);
	if (PROC_I(inode)->sysctl)
		sysctl_head_put(PROC_I(inode)->sysctl);
	clear_inode(inode);
	/* Release any associated namespace */
	ns_ops = PROC_I(inode)->ns_ops;
	ns = PROC_I(inode)->ns;
	if (ns_ops && ns)
		ns_ops->put(ns);
}