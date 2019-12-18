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
struct nfs_entry {int /*<<< orphan*/  fh; } ;
struct dentry {int /*<<< orphan*/ * d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_FH (int /*<<< orphan*/ *) ; 
 scalar_t__ nfs_compare_fh (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
int nfs_same_file(struct dentry *dentry, struct nfs_entry *entry)
{
	if (dentry->d_inode == NULL)
		goto different;
	if (nfs_compare_fh(entry->fh, NFS_FH(dentry->d_inode)) != 0)
		goto different;
	return 1;
different:
	return 0;
}