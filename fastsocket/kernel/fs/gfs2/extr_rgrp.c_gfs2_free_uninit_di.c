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
typedef  int /*<<< orphan*/  u64 ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_rgrpd {TYPE_1__* rd_bits; int /*<<< orphan*/  rd_gl; int /*<<< orphan*/  rd_free; int /*<<< orphan*/  rd_dinodes; struct gfs2_sbd* rd_sbd; } ;
struct TYPE_4__ {int /*<<< orphan*/  b_data; } ;
struct TYPE_3__ {TYPE_2__* bi_bh; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFS2_BLKST_FREE ; 
 int /*<<< orphan*/  gfs2_assert_withdraw (struct gfs2_sbd*,int) ; 
 int /*<<< orphan*/  gfs2_consist_rgrpd (struct gfs2_rgrpd*) ; 
 int /*<<< orphan*/  gfs2_rgrp_out (struct gfs2_rgrpd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_statfs_change (struct gfs2_sbd*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,TYPE_2__*) ; 
 struct gfs2_rgrpd* rgblk_free (struct gfs2_sbd*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gfs2_free_uninit_di(struct gfs2_rgrpd *rgd, u64 blkno)
{
	struct gfs2_sbd *sdp = rgd->rd_sbd;
	struct gfs2_rgrpd *tmp_rgd;

	tmp_rgd = rgblk_free(sdp, blkno, 1, GFS2_BLKST_FREE);
	if (!tmp_rgd)
		return;
	gfs2_assert_withdraw(sdp, rgd == tmp_rgd);

	if (!rgd->rd_dinodes)
		gfs2_consist_rgrpd(rgd);
	rgd->rd_dinodes--;
	rgd->rd_free++;

	gfs2_trans_add_meta(rgd->rd_gl, rgd->rd_bits[0].bi_bh);
	gfs2_rgrp_out(rgd, rgd->rd_bits[0].bi_bh->b_data);

	gfs2_statfs_change(sdp, 0, +1, -1);
}