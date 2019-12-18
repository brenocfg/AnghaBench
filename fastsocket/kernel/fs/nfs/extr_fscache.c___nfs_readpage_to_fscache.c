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
struct page {int /*<<< orphan*/  flags; int /*<<< orphan*/  index; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  fscache; } ;

/* Variables and functions */
 int /*<<< orphan*/  FSCACHE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NFSIOS_FSCACHE_PAGES_UNCACHED ; 
 int /*<<< orphan*/  NFSIOS_FSCACHE_PAGES_WRITTEN_FAIL ; 
 int /*<<< orphan*/  NFSIOS_FSCACHE_PAGES_WRITTEN_OK ; 
 TYPE_1__* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,struct page*,struct page*,int /*<<< orphan*/ ,int,...) ; 
 int /*<<< orphan*/  fscache_uncache_page (int /*<<< orphan*/ ,struct page*) ; 
 int fscache_write_page (int /*<<< orphan*/ ,struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_add_fscache_stats (struct inode*,int /*<<< orphan*/ ,int) ; 

void __nfs_readpage_to_fscache(struct inode *inode, struct page *page, int sync)
{
	int ret;

	dfprintk(FSCACHE,
		 "NFS: readpage_to_fscache(fsc:%p/p:%p(i:%lx f:%lx)/%d)\n",
		 NFS_I(inode)->fscache, page, page->index, page->flags, sync);

	ret = fscache_write_page(NFS_I(inode)->fscache, page, GFP_KERNEL);
	dfprintk(FSCACHE,
		 "NFS:     readpage_to_fscache: p:%p(i:%lu f:%lx) ret %d\n",
		 page, page->index, page->flags, ret);

	if (ret != 0) {
		fscache_uncache_page(NFS_I(inode)->fscache, page);
		nfs_add_fscache_stats(inode,
				      NFSIOS_FSCACHE_PAGES_WRITTEN_FAIL, 1);
		nfs_add_fscache_stats(inode, NFSIOS_FSCACHE_PAGES_UNCACHED, 1);
	} else {
		nfs_add_fscache_stats(inode,
				      NFSIOS_FSCACHE_PAGES_WRITTEN_OK, 1);
	}
}