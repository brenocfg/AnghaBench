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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct inode {scalar_t__ i_uid; scalar_t__ i_gid; } ;
struct iattr {scalar_t__ ia_uid; scalar_t__ ia_gid; int ia_valid; } ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_inode {int /*<<< orphan*/  i_inode; int /*<<< orphan*/  i_gl; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;

/* Variables and functions */
 int ATTR_GID ; 
 int ATTR_UID ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 scalar_t__ NO_QUOTA_CHANGE ; 
 scalar_t__ RES_DINODE ; 
 int RES_QUOTA ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  gfs2_assert_warn (struct gfs2_sbd*,int) ; 
 int /*<<< orphan*/  gfs2_dinode_out (struct gfs2_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_get_inode_blocks (int /*<<< orphan*/ *) ; 
 int gfs2_meta_inode_buffer (struct gfs2_inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  gfs2_quota_change (struct gfs2_inode*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int gfs2_quota_check (struct gfs2_inode*,scalar_t__,scalar_t__) ; 
 int gfs2_quota_lock (struct gfs2_inode*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gfs2_quota_unlock (struct gfs2_inode*) ; 
 int gfs2_rindex_update (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 int inode_setattr (struct inode*,struct iattr*) ; 

__attribute__((used)) static int setattr_chown(struct inode *inode, struct iattr *attr)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct buffer_head *dibh;
	u32 ouid, ogid, nuid, ngid;
	int error;

	ouid = inode->i_uid;
	ogid = inode->i_gid;
	nuid = attr->ia_uid;
	ngid = attr->ia_gid;

	if (!(attr->ia_valid & ATTR_UID) || ouid == nuid)
		ouid = nuid = NO_QUOTA_CHANGE;
	if (!(attr->ia_valid & ATTR_GID) || ogid == ngid)
		ogid = ngid = NO_QUOTA_CHANGE;

	error = gfs2_rindex_update(sdp);
	if (error)
		return error;

	error = gfs2_quota_lock(ip, nuid, ngid);
	if (error)
		return error;

	if (ouid != NO_QUOTA_CHANGE || ogid != NO_QUOTA_CHANGE) {
		error = gfs2_quota_check(ip, nuid, ngid);
		if (error)
			goto out_gunlock_q;
	}

	error = gfs2_trans_begin(sdp, RES_DINODE + 2 * RES_QUOTA, 0);
	if (error)
		goto out_gunlock_q;

	error = gfs2_meta_inode_buffer(ip, &dibh);
	if (error)
		goto out_end_trans;

	error = inode_setattr(inode, attr);
	gfs2_assert_warn(sdp, !error);

	gfs2_trans_add_meta(ip->i_gl, dibh);
	gfs2_dinode_out(ip, dibh->b_data);
	brelse(dibh);

	if (ouid != NO_QUOTA_CHANGE || ogid != NO_QUOTA_CHANGE) {
		u64 blocks = gfs2_get_inode_blocks(&ip->i_inode);
		gfs2_quota_change(ip, -blocks, ouid, ogid);
		gfs2_quota_change(ip, blocks, nuid, ngid);
	}

out_end_trans:
	gfs2_trans_end(sdp);
out_gunlock_q:
	gfs2_quota_unlock(ip);
	return error;
}