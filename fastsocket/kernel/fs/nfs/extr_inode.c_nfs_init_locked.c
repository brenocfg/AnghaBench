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
struct nfs_find_desc {int /*<<< orphan*/  fh; struct nfs_fattr* fattr; } ;
struct nfs_fattr {int /*<<< orphan*/  fileid; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFS_FH (struct inode*) ; 
 int /*<<< orphan*/  nfs_copy_fh (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_nfs_fileid (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nfs_init_locked(struct inode *inode, void *opaque)
{
	struct nfs_find_desc	*desc = (struct nfs_find_desc *)opaque;
	struct nfs_fattr	*fattr = desc->fattr;

	set_nfs_fileid(inode, fattr->fileid);
	nfs_copy_fh(NFS_FH(inode), desc->fh);
	return 0;
}