#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct proc_inode {struct mnt_namespace* ns; int /*<<< orphan*/ * ns_ops; } ;
struct path {TYPE_1__* dentry; } ;
struct mnt_namespace {scalar_t__ seq; } ;
struct inode {int dummy; } ;
struct TYPE_8__ {TYPE_3__* nsproxy; } ;
struct TYPE_7__ {TYPE_2__* mnt_ns; } ;
struct TYPE_6__ {scalar_t__ seq; } ;
struct TYPE_5__ {struct inode* d_inode; } ;

/* Variables and functions */
 struct proc_inode* PROC_I (struct inode*) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  mntns_operations ; 
 int /*<<< orphan*/  proc_ns_inode (struct inode*) ; 

__attribute__((used)) static bool mnt_ns_loop(struct path *path)
{
	/* Could bind mounting the mount namespace inode cause a
	 * mount namespace loop?
	 */
	struct inode *inode = path->dentry->d_inode;
	struct proc_inode *ei;
	struct mnt_namespace *mnt_ns;

	if (!proc_ns_inode(inode))
		return false;

	ei = PROC_I(inode);
	if (ei->ns_ops != &mntns_operations)
		return false;

	mnt_ns = ei->ns;
	return current->nsproxy->mnt_ns->seq >= mnt_ns->seq;
}