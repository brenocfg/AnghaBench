#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct TYPE_4__ {scalar_t__ ar_discard; } ;
struct gfs2_sbd {TYPE_2__ sd_args; struct super_block* sd_vfs; } ;
struct gfs2_bitmap {unsigned int bi_len; int* bi_clone; int bi_offset; unsigned int bi_start; TYPE_1__* bi_bh; } ;
struct buffer_head {int* b_data; } ;
typedef  scalar_t__ sector_t ;
struct TYPE_3__ {int* b_data; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 unsigned int GFS2_NBBY ; 
 int /*<<< orphan*/  fs_warn (struct gfs2_sbd*,char*,int) ; 
 int sb_issue_discard (struct super_block*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int gfs2_rgrp_send_discards(struct gfs2_sbd *sdp, u64 offset,
			     struct buffer_head *bh,
			     const struct gfs2_bitmap *bi, unsigned minlen, u64 *ptrimmed)
{
	struct super_block *sb = sdp->sd_vfs;
	u64 blk;
	sector_t start = 0;
	sector_t nr_blks = 0;
	int rv;
	unsigned int x;
	u32 trimmed = 0;
	u8 diff;

	for (x = 0; x < bi->bi_len; x++) {
		const u8 *clone = bi->bi_clone ? bi->bi_clone : bi->bi_bh->b_data;
		clone += bi->bi_offset;
		clone += x;
		if (bh) {
			const u8 *orig = bh->b_data + bi->bi_offset + x;
			diff = ~(*orig | (*orig >> 1)) & (*clone | (*clone >> 1));
		} else {
			diff = ~(*clone | (*clone >> 1));
		}
		diff &= 0x55;
		if (diff == 0)
			continue;
		blk = offset + ((bi->bi_start + x) * GFS2_NBBY);
		while(diff) {
			if (diff & 1) {
				if (nr_blks == 0)
					goto start_new_extent;
				if ((start + nr_blks) != blk) {
					if (nr_blks >= minlen) {
						rv = sb_issue_discard(sb,
							start, nr_blks,
							GFP_NOFS, 0);
						if (rv)
							goto fail;
						trimmed += nr_blks;
					}
					nr_blks = 0;
start_new_extent:
					start = blk;
				}
				nr_blks++;
			}
			diff >>= 2;
			blk++;
		}
	}
	if (nr_blks >= minlen) {
		rv = sb_issue_discard(sb, start, nr_blks, GFP_NOFS, 0);
		if (rv)
			goto fail;
		trimmed += nr_blks;
	}
	if (ptrimmed)
		*ptrimmed = trimmed;
	return 0;

fail:
	if (sdp->sd_args.ar_discard)
		fs_warn(sdp, "error %d on discard request, turning discards off for this filesystem", rv);
	sdp->sd_args.ar_discard = 0;
	return -EIO;
}