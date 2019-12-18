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
typedef  int u16 ;
struct qstr {int dummy; } ;
struct gfs2_leaf {int /*<<< orphan*/  lf_entries; } ;
struct TYPE_3__ {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; } ;
struct gfs2_inode {int i_diskflags; TYPE_1__ i_inode; int /*<<< orphan*/  i_entries; } ;
struct gfs2_dirent {int /*<<< orphan*/  de_rec_len; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 int EIO ; 
 int GFS2_DIF_EXHASH ; 
 scalar_t__ IS_ERR (struct gfs2_dirent*) ; 
 int PTR_ERR (struct gfs2_dirent*) ; 
 int be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  dirent_del (struct gfs2_inode*,struct buffer_head*,struct gfs2_dirent*,struct gfs2_dirent*) ; 
 int /*<<< orphan*/  gfs2_consist_inode (struct gfs2_inode*) ; 
 scalar_t__ gfs2_dirent_find (struct gfs2_dirent*,struct qstr const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_dirent_prev ; 
 struct gfs2_dirent* gfs2_dirent_search (TYPE_1__*,struct qstr const*,int /*<<< orphan*/ ,struct buffer_head**) ; 
 int /*<<< orphan*/  mark_inode_dirty (TYPE_1__*) ; 

int gfs2_dir_del(struct gfs2_inode *dip, const struct qstr *name)
{
	struct gfs2_dirent *dent, *prev = NULL;
	struct buffer_head *bh;

	/* Returns _either_ the entry (if its first in block) or the
	   previous entry otherwise */
	dent = gfs2_dirent_search(&dip->i_inode, name, gfs2_dirent_prev, &bh);
	if (!dent) {
		gfs2_consist_inode(dip);
		return -EIO;
	}
	if (IS_ERR(dent)) {
		gfs2_consist_inode(dip);
		return PTR_ERR(dent);
	}
	/* If not first in block, adjust pointers accordingly */
	if (gfs2_dirent_find(dent, name, NULL) == 0) {
		prev = dent;
		dent = (struct gfs2_dirent *)((char *)dent + be16_to_cpu(prev->de_rec_len));
	}

	dirent_del(dip, bh, prev, dent);
	if (dip->i_diskflags & GFS2_DIF_EXHASH) {
		struct gfs2_leaf *leaf = (struct gfs2_leaf *)bh->b_data;
		u16 entries = be16_to_cpu(leaf->lf_entries);
		if (!entries)
			gfs2_consist_inode(dip);
		leaf->lf_entries = cpu_to_be16(--entries);
	}
	brelse(bh);

	if (!dip->i_entries)
		gfs2_consist_inode(dip);
	dip->i_entries--;
	dip->i_inode.i_mtime = dip->i_inode.i_ctime = CURRENT_TIME;
	mark_inode_dirty(&dip->i_inode);

	return 0;
}