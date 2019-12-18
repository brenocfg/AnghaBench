#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
typedef  int u32 ;
struct gfs2_sbd {int /*<<< orphan*/  sd_jbsize; } ;
struct gfs2_rgrpd {scalar_t__ rd_length; } ;
struct gfs2_rgrp_list {unsigned int rl_rgrps; TYPE_2__* rl_ghs; } ;
struct gfs2_leaf {int /*<<< orphan*/  lf_next; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; int /*<<< orphan*/  i_inode; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_5__ {TYPE_1__* gh_gl; } ;
struct TYPE_4__ {struct gfs2_rgrpd* gl_object; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (unsigned int,int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 int /*<<< orphan*/  NO_QUOTA_CHANGE ; 
 scalar_t__ RES_DINODE ; 
 scalar_t__ RES_QUOTA ; 
 scalar_t__ RES_STATFS ; 
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int get_leaf (struct gfs2_inode*,scalar_t__,struct buffer_head**) ; 
 int /*<<< orphan*/  gfs2_add_inode_blocks (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gfs2_dinode_out (struct gfs2_inode*,scalar_t__) ; 
 int gfs2_dir_write_data (struct gfs2_inode*,char*,int,unsigned int) ; 
 int /*<<< orphan*/  gfs2_free_meta (struct gfs2_inode*,scalar_t__,int) ; 
 int /*<<< orphan*/  gfs2_glock_dq_m (unsigned int,TYPE_2__*) ; 
 int gfs2_glock_nq_m (unsigned int,TYPE_2__*) ; 
 int gfs2_meta_inode_buffer (struct gfs2_inode*,struct buffer_head**) ; 
 int gfs2_quota_hold (struct gfs2_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_quota_unhold (struct gfs2_inode*) ; 
 int gfs2_rindex_update (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_rlist_add (struct gfs2_inode*,struct gfs2_rgrp_list*,scalar_t__) ; 
 int /*<<< orphan*/  gfs2_rlist_alloc (struct gfs2_rgrp_list*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_rlist_free (struct gfs2_rgrp_list*) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 scalar_t__ is_vmalloc_addr (char*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kzalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct gfs2_rgrp_list*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vfree (char*) ; 
 char* vzalloc (unsigned int) ; 

__attribute__((used)) static int leaf_dealloc(struct gfs2_inode *dip, u32 index, u32 len,
			u64 leaf_no)
{
	struct gfs2_sbd *sdp = GFS2_SB(&dip->i_inode);
	struct gfs2_leaf *tmp_leaf;
	struct gfs2_rgrp_list rlist;
	struct buffer_head *bh, *dibh;
	u64 blk, nblk;
	unsigned int rg_blocks = 0, l_blocks = 0;
	char *ht;
	unsigned int x, size = len * sizeof(u64);
	int error;

	error = gfs2_rindex_update(sdp);
	if (error)
		return error;

	memset(&rlist, 0, sizeof(struct gfs2_rgrp_list));

	ht = kzalloc(size, GFP_NOFS);
	if (ht == NULL)
		ht = vzalloc(size);
	if (!ht)
		return -ENOMEM;

	error = gfs2_rindex_update(sdp);
	if (error)
		goto out;

	error = gfs2_quota_hold(dip, NO_QUOTA_CHANGE, NO_QUOTA_CHANGE);
	if (error)
		goto out;

	/*  Count the number of leaves  */

	for (blk = leaf_no; blk; blk = nblk) {
		error = get_leaf(dip, blk, &bh);
		if (error)
			goto out_rlist;
		tmp_leaf = (struct gfs2_leaf *)bh->b_data;
		nblk = be64_to_cpu(tmp_leaf->lf_next);
		brelse(bh);

		gfs2_rlist_add(dip, &rlist, blk);
		l_blocks++;
	}

	gfs2_rlist_alloc(&rlist, LM_ST_EXCLUSIVE);

	for (x = 0; x < rlist.rl_rgrps; x++) {
		struct gfs2_rgrpd *rgd;
		rgd = rlist.rl_ghs[x].gh_gl->gl_object;
		rg_blocks += rgd->rd_length;
	}

	error = gfs2_glock_nq_m(rlist.rl_rgrps, rlist.rl_ghs);
	if (error)
		goto out_rlist;

	error = gfs2_trans_begin(sdp,
			rg_blocks + (DIV_ROUND_UP(size, sdp->sd_jbsize) + 1) +
			RES_DINODE + RES_STATFS + RES_QUOTA, l_blocks);
	if (error)
		goto out_rg_gunlock;

	for (blk = leaf_no; blk; blk = nblk) {
		error = get_leaf(dip, blk, &bh);
		if (error)
			goto out_end_trans;
		tmp_leaf = (struct gfs2_leaf *)bh->b_data;
		nblk = be64_to_cpu(tmp_leaf->lf_next);
		brelse(bh);

		gfs2_free_meta(dip, blk, 1);
		gfs2_add_inode_blocks(&dip->i_inode, -1);
	}

	error = gfs2_dir_write_data(dip, ht, index * sizeof(u64), size);
	if (error != size) {
		if (error >= 0)
			error = -EIO;
		goto out_end_trans;
	}

	error = gfs2_meta_inode_buffer(dip, &dibh);
	if (error)
		goto out_end_trans;

	gfs2_trans_add_meta(dip->i_gl, dibh);
	gfs2_dinode_out(dip, dibh->b_data);
	brelse(dibh);

out_end_trans:
	gfs2_trans_end(sdp);
out_rg_gunlock:
	gfs2_glock_dq_m(rlist.rl_rgrps, rlist.rl_ghs);
out_rlist:
	gfs2_rlist_free(&rlist);
	gfs2_quota_unhold(dip);
out:
	if (is_vmalloc_addr(ht))
		vfree(ht);
	else
		kfree(ht);
	return error;
}