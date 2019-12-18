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
struct nfs_fattr {int valid; int /*<<< orphan*/  size; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int NFS_ATTR_FATTR_SIZE ; 
 scalar_t__ i_size_read (struct inode const*) ; 
 scalar_t__ nfs_size_to_loff_t (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nfs_size_need_update(const struct inode *inode, const struct nfs_fattr *fattr)
{
	if (!(fattr->valid & NFS_ATTR_FATTR_SIZE))
		return 0;
	return nfs_size_to_loff_t(fattr->size) > i_size_read(inode);
}