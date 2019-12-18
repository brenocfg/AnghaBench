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
struct gfs2_sbd {unsigned int sd_qc_per_block; int /*<<< orphan*/  sd_quota_mutex; int /*<<< orphan*/  sd_qc_inode; } ;
struct gfs2_quota_data {unsigned int qd_slot; int /*<<< orphan*/  qd_bh_count; struct gfs2_quota_change* qd_bh_qc; struct buffer_head* qd_bh; TYPE_1__* qd_gl; } ;
struct gfs2_quota_change {int dummy; } ;
struct gfs2_meta_header {int dummy; } ;
struct TYPE_4__ {int i_blkbits; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; TYPE_2__ i_inode; } ;
struct buffer_head {int b_size; scalar_t__ b_data; int /*<<< orphan*/  b_blocknr; int /*<<< orphan*/  b_state; } ;
struct TYPE_3__ {struct gfs2_sbd* gl_sbd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIO_WAIT ; 
 int EIO ; 
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFS2_METATYPE_QC ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int gfs2_block_map (TYPE_2__*,unsigned int,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int gfs2_meta_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**) ; 
 scalar_t__ gfs2_metatype_check (struct gfs2_sbd*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bh_get(struct gfs2_quota_data *qd)
{
	struct gfs2_sbd *sdp = qd->qd_gl->gl_sbd;
	struct gfs2_inode *ip = GFS2_I(sdp->sd_qc_inode);
	unsigned int block, offset;
	struct buffer_head *bh;
	int error;
	struct buffer_head bh_map = { .b_state = 0, .b_blocknr = 0 };

	mutex_lock(&sdp->sd_quota_mutex);

	if (qd->qd_bh_count++) {
		mutex_unlock(&sdp->sd_quota_mutex);
		return 0;
	}

	block = qd->qd_slot / sdp->sd_qc_per_block;
	offset = qd->qd_slot % sdp->sd_qc_per_block;

	bh_map.b_size = 1 << ip->i_inode.i_blkbits;
	error = gfs2_block_map(&ip->i_inode, block, &bh_map, 0);
	if (error)
		goto fail;
	error = gfs2_meta_read(ip->i_gl, bh_map.b_blocknr, DIO_WAIT, &bh);
	if (error)
		goto fail;
	error = -EIO;
	if (gfs2_metatype_check(sdp, bh, GFS2_METATYPE_QC))
		goto fail_brelse;

	qd->qd_bh = bh;
	qd->qd_bh_qc = (struct gfs2_quota_change *)
		(bh->b_data + sizeof(struct gfs2_meta_header) +
		 offset * sizeof(struct gfs2_quota_change));

	mutex_unlock(&sdp->sd_quota_mutex);

	return 0;

fail_brelse:
	brelse(bh);
fail:
	qd->qd_bh_count--;
	mutex_unlock(&sdp->sd_quota_mutex);
	return error;
}