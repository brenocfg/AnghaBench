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
struct super_block {int dummy; } ;
struct nfs_inode {scalar_t__ fscache; } ;
struct inode {struct super_block* i_sb; } ;
struct TYPE_2__ {int options; int /*<<< orphan*/  fscache; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSCACHE ; 
 int /*<<< orphan*/  NFS_FSCACHE (struct inode*) ; 
 struct nfs_inode* NFS_I (struct inode*) ; 
 int NFS_OPTION_FSCACHE ; 
 TYPE_1__* NFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,struct super_block*,struct nfs_inode*,scalar_t__) ; 
 scalar_t__ fscache_acquire_cookie (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct nfs_inode*) ; 
 int /*<<< orphan*/  nfs_fscache_inode_object_def ; 

__attribute__((used)) static void nfs_fscache_enable_inode_cookie(struct inode *inode)
{
	struct super_block *sb = inode->i_sb;
	struct nfs_inode *nfsi = NFS_I(inode);

	if (nfsi->fscache || !NFS_FSCACHE(inode))
		return;

	if ((NFS_SB(sb)->options & NFS_OPTION_FSCACHE)) {
		nfsi->fscache = fscache_acquire_cookie(
			NFS_SB(sb)->fscache,
			&nfs_fscache_inode_object_def,
			nfsi);

		dfprintk(FSCACHE, "NFS: get FH cookie (0x%p/0x%p/0x%p)\n",
			 sb, nfsi, nfsi->fscache);
	}
}