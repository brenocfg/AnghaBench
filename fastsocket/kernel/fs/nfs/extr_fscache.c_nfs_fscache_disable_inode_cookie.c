#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_3__ {scalar_t__ fscache; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSCACHE ; 
 TYPE_1__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  NFS_INO_FSCACHE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  fscache_uncache_all_inode_pages (scalar_t__,struct inode*) ; 
 int /*<<< orphan*/  nfs_fscache_zap_inode_cookie (struct inode*) ; 

__attribute__((used)) static void nfs_fscache_disable_inode_cookie(struct inode *inode)
{
	clear_bit(NFS_INO_FSCACHE, &NFS_I(inode)->flags);

	if (NFS_I(inode)->fscache) {
		dfprintk(FSCACHE,
			 "NFS: nfsi 0x%p turning cache off\n", NFS_I(inode));

		/* Need to uncache any pages attached to this inode that
		 * fscache knows about before turning off the cache.
		 */
		fscache_uncache_all_inode_pages(NFS_I(inode)->fscache, inode);
		nfs_fscache_zap_inode_cookie(inode);
	}
}