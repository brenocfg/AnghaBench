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
typedef  int /*<<< orphan*/  u32 ;
struct gfs2_sbd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_ino; } ;
struct gfs2_inode {int /*<<< orphan*/  i_no_addr; int /*<<< orphan*/  i_goal; TYPE_1__ i_inode; int /*<<< orphan*/  i_generation; int /*<<< orphan*/  i_no_formal_ino; } ;
struct gfs2_alloc_parms {int /*<<< orphan*/  aflags; int /*<<< orphan*/  target; } ;

/* Variables and functions */
 struct gfs2_sbd* GFS2_SB (TYPE_1__*) ; 
 int /*<<< orphan*/  RES_DINODE ; 
 scalar_t__ RES_QUOTA ; 
 scalar_t__ RES_RG_BIT ; 
 scalar_t__ RES_STATFS ; 
 int gfs2_alloc_blocks (struct gfs2_inode*,int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_inplace_release (struct gfs2_inode*) ; 
 int gfs2_inplace_reserve (struct gfs2_inode*,struct gfs2_alloc_parms*) ; 
 int gfs2_quota_lock_check (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_quota_unlock (struct gfs2_inode*) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 

__attribute__((used)) static int alloc_dinode(struct gfs2_inode *ip, u32 flags)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	struct gfs2_alloc_parms ap = { .target = RES_DINODE, .aflags = flags, };
	int error;
	int dblocks = 1;

	error = gfs2_quota_lock_check(ip);
	if (error)
		goto out;

	error = gfs2_inplace_reserve(ip, &ap);
	if (error)
		goto out_quota;

	error = gfs2_trans_begin(sdp, RES_RG_BIT + RES_STATFS + RES_QUOTA, 0);
	if (error)
		goto out_ipreserv;

	error = gfs2_alloc_blocks(ip, &ip->i_no_addr, &dblocks, 1, &ip->i_generation);
	ip->i_no_formal_ino = ip->i_generation;
	ip->i_inode.i_ino = ip->i_no_addr;
	ip->i_goal = ip->i_no_addr;

	gfs2_trans_end(sdp);

out_ipreserv:
	gfs2_inplace_release(ip);
out_quota:
	gfs2_quota_unlock(ip);
out:
	return error;
}