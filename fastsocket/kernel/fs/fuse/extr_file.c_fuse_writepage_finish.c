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
struct inode {TYPE_1__* i_mapping; } ;
struct fuse_req {int /*<<< orphan*/ * pages; int /*<<< orphan*/  writepages_entry; struct inode* inode; } ;
struct fuse_inode {int /*<<< orphan*/  page_waitq; } ;
struct fuse_conn {int dummy; } ;
struct backing_dev_info {int dummy; } ;
struct TYPE_2__ {struct backing_dev_info* backing_dev_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDI_WRITEBACK ; 
 int /*<<< orphan*/  NR_WRITEBACK_TEMP ; 
 int /*<<< orphan*/  bdi_writeout_inc (struct backing_dev_info*) ; 
 int /*<<< orphan*/  dec_bdi_stat (struct backing_dev_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dec_zone_page_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fuse_writepage_finish(struct fuse_conn *fc, struct fuse_req *req)
{
	struct inode *inode = req->inode;
	struct fuse_inode *fi = get_fuse_inode(inode);
	struct backing_dev_info *bdi = inode->i_mapping->backing_dev_info;

	list_del(&req->writepages_entry);
	dec_bdi_stat(bdi, BDI_WRITEBACK);
	dec_zone_page_state(req->pages[0], NR_WRITEBACK_TEMP);
	bdi_writeout_inc(bdi);
	wake_up(&fi->page_waitq);
}