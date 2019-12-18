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
struct page {TYPE_1__* mapping; } ;
struct nfs_inode {int dummy; } ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 struct nfs_inode* NFS_I (struct inode*) ; 
 int /*<<< orphan*/  PAGECACHE ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,long long) ; 
 int /*<<< orphan*/  nfs_fscache_wait_on_page_write (struct nfs_inode*,struct page*) ; 
 int nfs_wb_page (struct inode*,struct page*) ; 
 scalar_t__ page_offset (struct page*) ; 

__attribute__((used)) static int nfs_launder_page(struct page *page)
{
	struct inode *inode = page->mapping->host;
	struct nfs_inode *nfsi = NFS_I(inode);

	dfprintk(PAGECACHE, "NFS: launder_page(%ld, %llu)\n",
		inode->i_ino, (long long)page_offset(page));

	nfs_fscache_wait_on_page_write(nfsi, page);
	return nfs_wb_page(inode, page);
}