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
struct gfs2_sbd {int /*<<< orphan*/  sd_replayed_blocks; int /*<<< orphan*/  sd_found_blocks; } ;
struct gfs2_log_descriptor {int /*<<< orphan*/  ld_type; int /*<<< orphan*/  ld_data1; } ;
struct gfs2_jdesc {int /*<<< orphan*/  jd_inode; } ;
struct gfs2_inode {struct gfs2_glock* i_gl; } ;
struct gfs2_glock {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_size; int /*<<< orphan*/  b_data; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int EIO ; 
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 unsigned int GFS2_LOG_DESC_METADATA ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ ) ; 
 unsigned int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ gfs2_meta_check (struct gfs2_sbd*,struct buffer_head*) ; 
 struct buffer_head* gfs2_meta_new (struct gfs2_glock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_replay_incr_blk (struct gfs2_sbd*,unsigned int*) ; 
 int gfs2_replay_read_block (struct gfs2_jdesc*,unsigned int,struct buffer_head**) ; 
 scalar_t__ gfs2_revoke_check (struct gfs2_sbd*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int buf_lo_scan_elements(struct gfs2_jdesc *jd, unsigned int start,
				struct gfs2_log_descriptor *ld, __be64 *ptr,
				int pass)
{
	struct gfs2_inode *ip = GFS2_I(jd->jd_inode);
	struct gfs2_sbd *sdp = GFS2_SB(jd->jd_inode);
	struct gfs2_glock *gl = ip->i_gl;
	unsigned int blks = be32_to_cpu(ld->ld_data1);
	struct buffer_head *bh_log, *bh_ip;
	u64 blkno;
	int error = 0;

	if (pass != 1 || be32_to_cpu(ld->ld_type) != GFS2_LOG_DESC_METADATA)
		return 0;

	gfs2_replay_incr_blk(sdp, &start);

	for (; blks; gfs2_replay_incr_blk(sdp, &start), blks--) {
		blkno = be64_to_cpu(*ptr++);

		sdp->sd_found_blocks++;

		if (gfs2_revoke_check(sdp, blkno, start))
			continue;

		error = gfs2_replay_read_block(jd, start, &bh_log);
		if (error)
			return error;

		bh_ip = gfs2_meta_new(gl, blkno);
		memcpy(bh_ip->b_data, bh_log->b_data, bh_log->b_size);

		if (gfs2_meta_check(sdp, bh_ip))
			error = -EIO;
		else
			mark_buffer_dirty(bh_ip);

		brelse(bh_log);
		brelse(bh_ip);

		if (error)
			break;

		sdp->sd_replayed_blocks++;
	}

	return error;
}