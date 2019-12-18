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
struct nfs_server {int /*<<< orphan*/  backing_dev_info; int /*<<< orphan*/  writeback; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_RW_ASYNC ; 
 scalar_t__ NFS_CONGESTION_OFF_THRESH ; 
 struct nfs_server* NFS_SERVER (struct inode*) ; 
 scalar_t__ atomic_long_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bdi_congested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_page_writeback (struct page*) ; 

__attribute__((used)) static void nfs_end_page_writeback(struct page *page)
{
	struct inode *inode = page->mapping->host;
	struct nfs_server *nfss = NFS_SERVER(inode);

	end_page_writeback(page);
	if (atomic_long_dec_return(&nfss->writeback) < NFS_CONGESTION_OFF_THRESH)
		clear_bdi_congested(&nfss->backing_dev_info, BLK_RW_ASYNC);
}