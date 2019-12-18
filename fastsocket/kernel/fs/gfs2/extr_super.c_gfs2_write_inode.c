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
struct writeback_control {scalar_t__ sync_mode; } ;
struct inode {int dummy; } ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; } ;
struct backing_dev_info {scalar_t__ dirty_exceeded; } ;
struct address_space {struct backing_dev_info* backing_dev_info; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 scalar_t__ WB_SYNC_ALL ; 
 int filemap_fdatawait (struct address_space*) ; 
 int /*<<< orphan*/  filemap_fdatawrite (struct address_space*) ; 
 int /*<<< orphan*/  gfs2_ail1_flush (struct gfs2_sbd*,struct writeback_control*) ; 
 struct address_space* gfs2_glock2aspace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_log_flush (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_inode_dirty_sync (struct inode*) ; 

__attribute__((used)) static int gfs2_write_inode(struct inode *inode, struct writeback_control *wbc)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct address_space *metamapping = gfs2_glock2aspace(ip->i_gl);
	struct backing_dev_info *bdi = metamapping->backing_dev_info;
	int ret = 0;

	if (wbc->sync_mode == WB_SYNC_ALL)
		gfs2_log_flush(GFS2_SB(inode), ip->i_gl);
	if (bdi->dirty_exceeded)
		gfs2_ail1_flush(sdp, wbc);
	else
		filemap_fdatawrite(metamapping);
	if (wbc->sync_mode == WB_SYNC_ALL)
		ret = filemap_fdatawait(metamapping);
	if (ret)
		mark_inode_dirty_sync(inode);
	return ret;
}