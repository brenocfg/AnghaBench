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
struct nfs_inode {int /*<<< orphan*/  silly_count; int /*<<< orphan*/  waitqueue; } ;
struct dentry {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 struct nfs_inode* NFS_I (int /*<<< orphan*/ ) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 

void nfs_wait_on_sillyrename(struct dentry *dentry)
{
	struct nfs_inode *nfsi = NFS_I(dentry->d_inode);

	wait_event(nfsi->waitqueue, atomic_read(&nfsi->silly_count) <= 1);
}