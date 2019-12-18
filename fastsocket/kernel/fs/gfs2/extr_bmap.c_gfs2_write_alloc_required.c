#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_5__ {int sb_bsize; unsigned int sb_bsize_shift; } ;
struct gfs2_sbd {TYPE_1__ sd_sb; } ;
struct TYPE_6__ {int i_blkbits; } ;
struct gfs2_inode {TYPE_2__ i_inode; } ;
struct gfs2_dinode {int dummy; } ;
struct buffer_head {int b_size; scalar_t__ b_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 struct gfs2_sbd* GFS2_SB (TYPE_2__*) ; 
 int /*<<< orphan*/  buffer_mapped (struct buffer_head*) ; 
 int /*<<< orphan*/  gfs2_block_map (TYPE_2__*,int,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_is_dir (struct gfs2_inode*) ; 
 scalar_t__ gfs2_is_stuffed (struct gfs2_inode*) ; 
 int i_size_read (TYPE_2__*) ; 

int gfs2_write_alloc_required(struct gfs2_inode *ip, u64 offset,
			      unsigned int len, int *alloc_required)
{
	struct gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	struct buffer_head bh;
	unsigned int shift;
	u64 lblock, lblock_stop, size;
	u64 end_of_file;

	*alloc_required = 0;

	if (!len)
		return 0;

	if (gfs2_is_stuffed(ip)) {
		if (offset + len >
		    sdp->sd_sb.sb_bsize - sizeof(struct gfs2_dinode))
			*alloc_required = 1;
		return 0;
	}

	*alloc_required = 1;
	shift = sdp->sd_sb.sb_bsize_shift;
	BUG_ON(gfs2_is_dir(ip));
	end_of_file = (i_size_read(&ip->i_inode) + sdp->sd_sb.sb_bsize - 1) >> shift;
	lblock = offset >> shift;
	lblock_stop = (offset + len + sdp->sd_sb.sb_bsize - 1) >> shift;
	if (lblock_stop > end_of_file)
		return 0;

	size = (lblock_stop - lblock) << shift;
	do {
		bh.b_state = 0;
		bh.b_size = size;
		gfs2_block_map(&ip->i_inode, lblock, &bh, 0);
		if (!buffer_mapped(&bh))
			return 0;
		size -= bh.b_size;
		lblock += (bh.b_size >> ip->i_inode.i_blkbits);
	} while(size > 0);

	*alloc_required = 0;
	return 0;
}