#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct strip_mine {unsigned int sm_height; scalar_t__ sm_first; } ;
struct gfs2_sbd {unsigned int sd_inptrs; unsigned int sd_diptrs; } ;
struct gfs2_rgrpd {scalar_t__ rd_length; } ;
struct gfs2_rgrp_list {int rl_rgrps; TYPE_2__* rl_ghs; } ;
struct TYPE_8__ {int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct gfs2_inode {int i_height; int /*<<< orphan*/  i_rw_mutex; TYPE_4__ i_inode; int /*<<< orphan*/  i_gl; int /*<<< orphan*/  i_res; scalar_t__ i_depth; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  int /*<<< orphan*/  s64 ;
typedef  scalar_t__ __be64 ;
struct TYPE_7__ {TYPE_1__* gh_gl; } ;
struct TYPE_6__ {struct gfs2_rgrpd* gl_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 struct gfs2_sbd* GFS2_SB (TYPE_4__*) ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 scalar_t__ RES_DINODE ; 
 scalar_t__ RES_INDIRECT ; 
 scalar_t__ RES_QUOTA ; 
 scalar_t__ RES_STATFS ; 
 int /*<<< orphan*/  __gfs2_free_blocks (struct gfs2_inode*,scalar_t__,int,int) ; 
 scalar_t__ be64_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_add_inode_blocks (TYPE_4__*,int) ; 
 int /*<<< orphan*/  gfs2_dinode_out (struct gfs2_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_glock_dq_m (int,TYPE_2__*) ; 
 int gfs2_glock_nq_m (int,TYPE_2__*) ; 
 int /*<<< orphan*/  gfs2_quota_change (struct gfs2_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int gfs2_rindex_update (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_rlist_add (struct gfs2_inode*,struct gfs2_rgrp_list*,scalar_t__) ; 
 int /*<<< orphan*/  gfs2_rlist_alloc (struct gfs2_rgrp_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_rlist_free (struct gfs2_rgrp_list*) ; 
 scalar_t__ gfs2_rs_active (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_rs_deltree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_statfs_change (struct gfs2_sbd*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  memset (struct gfs2_rgrp_list*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_strip(struct gfs2_inode *ip, struct buffer_head *dibh,
		    struct buffer_head *bh, __be64 *top, __be64 *bottom,
		    unsigned int height, struct strip_mine *sm)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	struct gfs2_rgrp_list rlist;
	u64 bn, bstart;
	u32 blen, btotal;
	__be64 *p;
	unsigned int rg_blocks = 0;
	int metadata;
	unsigned int revokes = 0;
	int x;
	int error;

	error = gfs2_rindex_update(sdp);
	if (error)
		return error;

	if (!*top)
		sm->sm_first = 0;

	if (height != sm->sm_height)
		return 0;

	if (sm->sm_first) {
		top++;
		sm->sm_first = 0;
	}

	metadata = (height != ip->i_height - 1);
	if (metadata)
		revokes = (height) ? sdp->sd_inptrs : sdp->sd_diptrs;
	else if (ip->i_depth)
		revokes = sdp->sd_inptrs;

	memset(&rlist, 0, sizeof(struct gfs2_rgrp_list));
	bstart = 0;
	blen = 0;

	for (p = top; p < bottom; p++) {
		if (!*p)
			continue;

		bn = be64_to_cpu(*p);

		if (bstart + blen == bn)
			blen++;
		else {
			if (bstart)
				gfs2_rlist_add(ip, &rlist, bstart);

			bstart = bn;
			blen = 1;
		}
	}

	if (bstart)
		gfs2_rlist_add(ip, &rlist, bstart);
	else
		goto out; /* Nothing to do */

	gfs2_rlist_alloc(&rlist, LM_ST_EXCLUSIVE);

	for (x = 0; x < rlist.rl_rgrps; x++) {
		struct gfs2_rgrpd *rgd;
		rgd = rlist.rl_ghs[x].gh_gl->gl_object;
		rg_blocks += rgd->rd_length;
	}

	error = gfs2_glock_nq_m(rlist.rl_rgrps, rlist.rl_ghs);
	if (error)
		goto out_rlist;

	if (gfs2_rs_active(ip->i_res)) /* needs to be done with the rgrp glock held */
		gfs2_rs_deltree(ip->i_res);

	error = gfs2_trans_begin(sdp, rg_blocks + RES_DINODE +
				 RES_INDIRECT + RES_STATFS + RES_QUOTA,
				 revokes);
	if (error)
		goto out_rg_gunlock;

	down_write(&ip->i_rw_mutex);

	gfs2_trans_add_meta(ip->i_gl, dibh);
	gfs2_trans_add_meta(ip->i_gl, bh);

	bstart = 0;
	blen = 0;
	btotal = 0;

	for (p = top; p < bottom; p++) {
		if (!*p)
			continue;

		bn = be64_to_cpu(*p);

		if (bstart + blen == bn)
			blen++;
		else {
			if (bstart) {
				__gfs2_free_blocks(ip, bstart, blen, metadata);
				btotal += blen;
			}

			bstart = bn;
			blen = 1;
		}

		*p = 0;
		gfs2_add_inode_blocks(&ip->i_inode, -1);
	}
	if (bstart) {
		__gfs2_free_blocks(ip, bstart, blen, metadata);
		btotal += blen;
	}

	gfs2_statfs_change(sdp, 0, +btotal, 0);
	gfs2_quota_change(ip, -(s64)btotal, ip->i_inode.i_uid,
			  ip->i_inode.i_gid);

	ip->i_inode.i_mtime = ip->i_inode.i_ctime = CURRENT_TIME;

	gfs2_dinode_out(ip, dibh->b_data);

	up_write(&ip->i_rw_mutex);

	gfs2_trans_end(sdp);

out_rg_gunlock:
	gfs2_glock_dq_m(rlist.rl_rgrps, rlist.rl_ghs);
out_rlist:
	gfs2_rlist_free(&rlist);
out:
	return error;
}