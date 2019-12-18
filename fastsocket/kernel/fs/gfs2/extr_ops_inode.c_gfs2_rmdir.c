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
struct inode {int dummy; } ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_rgrpd {int /*<<< orphan*/  rd_gl; } ;
struct TYPE_2__ {scalar_t__ i_nlink; } ;
struct gfs2_inode {int i_entries; TYPE_1__ i_inode; int /*<<< orphan*/  i_no_addr; int /*<<< orphan*/  i_gl; } ;
struct gfs2_holder {int dummy; } ;
struct dentry {int /*<<< orphan*/  d_name; struct inode* d_inode; } ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 int ENOTEMPTY ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 int RES_DINODE ; 
 int RES_LEAF ; 
 scalar_t__ RES_RG_BIT ; 
 struct gfs2_rgrpd* gfs2_blk2rgrpd (struct gfs2_sbd*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ gfs2_consist_inode (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_dinode_print (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_glock_dq (struct gfs2_holder*) ; 
 int gfs2_glock_nq (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_uninit (struct gfs2_holder*) ; 
 int gfs2_rindex_update (struct gfs2_sbd*) ; 
 int gfs2_rmdiri (struct gfs2_inode*,int /*<<< orphan*/ *,struct gfs2_inode*) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 int gfs2_unlink_ok (struct gfs2_inode*,int /*<<< orphan*/ *,struct gfs2_inode*) ; 

__attribute__((used)) static int gfs2_rmdir(struct inode *dir, struct dentry *dentry)
{
	struct gfs2_inode *dip = GFS2_I(dir);
	struct gfs2_sbd *sdp = GFS2_SB(dir);
	struct gfs2_inode *ip = GFS2_I(dentry->d_inode);
	struct gfs2_holder ghs[3];
	struct gfs2_rgrpd *rgd;
	int error;

	error = gfs2_rindex_update(sdp);
	if (error)
		return error;

	gfs2_holder_init(dip->i_gl, LM_ST_EXCLUSIVE, 0, ghs);
	gfs2_holder_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, ghs + 1);

	rgd = gfs2_blk2rgrpd(sdp, ip->i_no_addr, 1);
	gfs2_holder_init(rgd->rd_gl, LM_ST_EXCLUSIVE, 0, ghs + 2);

	error = gfs2_glock_nq(ghs); /* parent */
	if (error)
		goto out_parent;

	error = gfs2_glock_nq(ghs + 1); /* child */
	if (error)
		goto out_child;

	error = -ENOENT;
	if (ip->i_inode.i_nlink == 0)
		goto out_rgrp;

	error = gfs2_glock_nq(ghs + 2); /* rgrp */
	if (error)
		goto out_rgrp;

	error = gfs2_unlink_ok(dip, &dentry->d_name, ip);
	if (error)
		goto out_gunlock;

	if (ip->i_entries < 2) {
		if (gfs2_consist_inode(ip))
			gfs2_dinode_print(ip);
		error = -EIO;
		goto out_gunlock;
	}
	if (ip->i_entries > 2) {
		error = -ENOTEMPTY;
		goto out_gunlock;
	}
	error = gfs2_trans_begin(sdp, 2 * RES_DINODE + 3 * RES_LEAF + RES_RG_BIT, 0);
	if (error)
		goto out_gunlock;

	error = gfs2_rmdiri(dip, &dentry->d_name, ip);

	gfs2_trans_end(sdp);

out_gunlock:
	gfs2_glock_dq(ghs + 2);
out_rgrp:
	gfs2_holder_uninit(ghs + 2);
	gfs2_glock_dq(ghs + 1);
out_child:
	gfs2_holder_uninit(ghs + 1);
	gfs2_glock_dq(ghs);
out_parent:
	gfs2_holder_uninit(ghs);
	return error;
}