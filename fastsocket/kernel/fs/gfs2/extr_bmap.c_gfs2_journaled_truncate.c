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
typedef  scalar_t__ u64 ;
struct inode {int dummy; } ;
struct gfs2_sbd {TYPE_1__* sd_vfs; } ;
struct TYPE_2__ {scalar_t__ s_blocksize; } ;

/* Variables and functions */
 scalar_t__ GFS2_JTRUNC_REVOKES ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 int /*<<< orphan*/  RES_DINODE ; 
 int gfs2_trans_begin (struct gfs2_sbd*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  truncate_pagecache (struct inode*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int gfs2_journaled_truncate(struct inode *inode, u64 oldsize, u64 newsize)
{
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	u64 max_chunk = GFS2_JTRUNC_REVOKES * sdp->sd_vfs->s_blocksize;
	u64 chunk;
	int error;

	while (oldsize != newsize) {
		chunk = oldsize - newsize;
		if (chunk > max_chunk)
			chunk = max_chunk;
		truncate_pagecache(inode, oldsize, oldsize - chunk);
		oldsize -= chunk;
		gfs2_trans_end(sdp);
		error = gfs2_trans_begin(sdp, RES_DINODE, GFS2_JTRUNC_REVOKES);
		if (error)
			return error;
	}

	return 0;
}