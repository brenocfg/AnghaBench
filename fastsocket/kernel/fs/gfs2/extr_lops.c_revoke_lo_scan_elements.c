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
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {unsigned int sb_bsize; } ;
struct gfs2_sbd {int /*<<< orphan*/  sd_found_revokes; TYPE_1__ sd_sb; } ;
struct gfs2_meta_header {int dummy; } ;
struct gfs2_log_descriptor {int /*<<< orphan*/  ld_type; int /*<<< orphan*/  ld_data1; int /*<<< orphan*/  ld_length; } ;
struct gfs2_jdesc {int /*<<< orphan*/  jd_inode; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 unsigned int GFS2_LOG_DESC_REVOKE ; 
 int /*<<< orphan*/  GFS2_METATYPE_LB ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ ) ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  gfs2_metatype_check (struct gfs2_sbd*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_replay_incr_blk (struct gfs2_sbd*,unsigned int*) ; 
 int gfs2_replay_read_block (struct gfs2_jdesc*,unsigned int,struct buffer_head**) ; 
 int gfs2_revoke_add (struct gfs2_sbd*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int revoke_lo_scan_elements(struct gfs2_jdesc *jd, unsigned int start,
				   struct gfs2_log_descriptor *ld, __be64 *ptr,
				   int pass)
{
	struct gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	unsigned int blks = be32_to_cpu(ld->ld_length);
	unsigned int revokes = be32_to_cpu(ld->ld_data1);
	struct buffer_head *bh;
	unsigned int offset;
	u64 blkno;
	int first = 1;
	int error;

	if (pass != 0 || be32_to_cpu(ld->ld_type) != GFS2_LOG_DESC_REVOKE)
		return 0;

	offset = sizeof(struct gfs2_log_descriptor);

	for (; blks; gfs2_replay_incr_blk(sdp, &start), blks--) {
		error = gfs2_replay_read_block(jd, start, &bh);
		if (error)
			return error;

		if (!first)
			gfs2_metatype_check(sdp, bh, GFS2_METATYPE_LB);

		while (offset + sizeof(u64) <= sdp->sd_sb.sb_bsize) {
			blkno = be64_to_cpu(*(__be64 *)(bh->b_data + offset));

			error = gfs2_revoke_add(sdp, blkno, start);
			if (error < 0) {
				brelse(bh);
				return error;
			}
			else if (error)
				sdp->sd_found_revokes++;

			if (!--revokes)
				break;
			offset += sizeof(u64);
		}

		brelse(bh);
		offset = sizeof(struct gfs2_meta_header);
		first = 0;
	}

	return 0;
}