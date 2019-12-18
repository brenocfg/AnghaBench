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
struct TYPE_2__ {int /*<<< orphan*/  i_ctime; } ;
struct gfs2_inode {TYPE_1__ i_inode; int /*<<< orphan*/  i_gl; } ;
struct gfs2_ea_request {int dummy; } ;
struct gfs2_alloc_parms {unsigned int target; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
typedef  int (* ea_skeleton_call_t ) (struct gfs2_inode*,struct gfs2_ea_request*,void*) ;

/* Variables and functions */
 int /*<<< orphan*/  CURRENT_TIME ; 
 int /*<<< orphan*/  GFS2_SB (TYPE_1__*) ; 
 scalar_t__ RES_DINODE ; 
 scalar_t__ RES_QUOTA ; 
 scalar_t__ RES_STATFS ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  gfs2_dinode_out (struct gfs2_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_inplace_release (struct gfs2_inode*) ; 
 int gfs2_inplace_reserve (struct gfs2_inode*,struct gfs2_alloc_parms*) ; 
 int gfs2_meta_inode_buffer (struct gfs2_inode*,struct buffer_head**) ; 
 int gfs2_quota_lock_check (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_quota_unlock (struct gfs2_inode*) ; 
 scalar_t__ gfs2_rg_blocks (struct gfs2_inode*,unsigned int) ; 
 int gfs2_rindex_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int gfs2_trans_begin (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ea_alloc_skeleton(struct gfs2_inode *ip, struct gfs2_ea_request *er,
			     unsigned int blks,
			     ea_skeleton_call_t skeleton_call, void *private)
{
	struct gfs2_alloc_parms ap = { .target = blks };
	struct buffer_head *dibh;
	int error;

	error = gfs2_rindex_update(GFS2_SB(&ip->i_inode));
	if (error)
		return error;

	error = gfs2_quota_lock_check(ip);
	if (error)
		return error;

	error = gfs2_inplace_reserve(ip, &ap);
	if (error)
		goto out_gunlock_q;

	error = gfs2_trans_begin(GFS2_SB(&ip->i_inode),
				 blks + gfs2_rg_blocks(ip, blks) +
				 RES_DINODE + RES_STATFS + RES_QUOTA, 0);
	if (error)
		goto out_ipres;

	error = skeleton_call(ip, er, private);
	if (error)
		goto out_end_trans;

	error = gfs2_meta_inode_buffer(ip, &dibh);
	if (!error) {
		ip->i_inode.i_ctime = CURRENT_TIME;
		gfs2_trans_add_meta(ip->i_gl, dibh);
		gfs2_dinode_out(ip, dibh->b_data);
		brelse(dibh);
	}

out_end_trans:
	gfs2_trans_end(GFS2_SB(&ip->i_inode));
out_ipres:
	gfs2_inplace_release(ip);
out_gunlock_q:
	gfs2_quota_unlock(ip);
	return error;
}