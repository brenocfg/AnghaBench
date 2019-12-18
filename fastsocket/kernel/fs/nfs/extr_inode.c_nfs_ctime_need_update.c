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
struct nfs_fattr {int valid; int /*<<< orphan*/  ctime; } ;
struct inode {int /*<<< orphan*/  i_ctime; } ;

/* Variables and functions */
 int NFS_ATTR_FATTR_CTIME ; 
 scalar_t__ timespec_compare (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfs_ctime_need_update(const struct inode *inode, const struct nfs_fattr *fattr)
{
	if (!(fattr->valid & NFS_ATTR_FATTR_CTIME))
		return 0;
	return timespec_compare(&fattr->ctime, &inode->i_ctime) > 0;
}