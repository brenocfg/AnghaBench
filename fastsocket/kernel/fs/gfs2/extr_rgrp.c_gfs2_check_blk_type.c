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
struct gfs2_sbd {int dummy; } ;
struct gfs2_rgrpd {int /*<<< orphan*/  rd_gl; } ;
struct gfs2_holder {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ESTALE ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 struct gfs2_rgrpd* gfs2_blk2rgrpd (struct gfs2_sbd*,int /*<<< orphan*/ ,int) ; 
 unsigned int gfs2_get_block_type (struct gfs2_rgrpd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 

int gfs2_check_blk_type(struct gfs2_sbd *sdp, u64 no_addr, unsigned int type)
{
	struct gfs2_rgrpd *rgd;
	struct gfs2_holder rgd_gh;
	int error = -EINVAL;

	rgd = gfs2_blk2rgrpd(sdp, no_addr, 1);
	if (!rgd)
		goto fail;

	error = gfs2_glock_nq_init(rgd->rd_gl, LM_ST_SHARED, 0, &rgd_gh);
	if (error)
		goto fail;

	if (gfs2_get_block_type(rgd, no_addr) != type)
		error = -ESTALE;

	gfs2_glock_dq_uninit(&rgd_gh);
fail:
	return error;
}