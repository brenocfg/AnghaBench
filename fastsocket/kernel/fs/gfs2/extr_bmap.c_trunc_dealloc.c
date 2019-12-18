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
typedef  int u64 ;
struct strip_mine {int sm_first; unsigned int sm_height; } ;
struct metapath {int dummy; } ;
struct TYPE_2__ {int sb_bsize_shift; } ;
struct gfs2_sbd {TYPE_1__ sd_sb; } ;
struct gfs2_inode {unsigned int i_height; int /*<<< orphan*/  i_inode; } ;

/* Variables and functions */
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NO_QUOTA_CHANGE ; 
 int /*<<< orphan*/  find_metapath (struct gfs2_sbd*,int,struct metapath*,unsigned int) ; 
 int gfs2_quota_hold (struct gfs2_inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_quota_unhold (struct gfs2_inode*) ; 
 int gfs2_rindex_update (struct gfs2_sbd*) ; 
 int recursive_scan (struct gfs2_inode*,int /*<<< orphan*/ *,struct metapath*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct strip_mine*) ; 

__attribute__((used)) static int trunc_dealloc(struct gfs2_inode *ip, u64 size)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	unsigned int height = ip->i_height;
	u64 lblock;
	struct metapath mp;
	int error;

	if (!size)
		lblock = 0;
	else
		lblock = (size - 1) >> sdp->sd_sb.sb_bsize_shift;

	find_metapath(sdp, lblock, &mp, ip->i_height);
	error = gfs2_rindex_update(sdp);
	if (error)
		return error;

	error = gfs2_quota_hold(ip, NO_QUOTA_CHANGE, NO_QUOTA_CHANGE);
	if (error)
		return error;

	while (height--) {
		struct strip_mine sm;
		sm.sm_first = !!size;
		sm.sm_height = height;

		error = recursive_scan(ip, NULL, &mp, 0, 0, 1, &sm);
		if (error)
			break;
	}

	gfs2_quota_unhold(ip);

	return error;
}