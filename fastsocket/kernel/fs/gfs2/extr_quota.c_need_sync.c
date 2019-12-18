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
struct gfs2_tune {unsigned int gt_quota_scale_num; unsigned int gt_quota_scale_den; int /*<<< orphan*/  gt_spin; } ;
struct gfs2_sbd {struct gfs2_tune sd_tune; } ;
struct TYPE_4__ {int /*<<< orphan*/  qb_limit; int /*<<< orphan*/  qb_value; } ;
struct gfs2_quota_data {scalar_t__ qd_change; TYPE_2__ qd_qb; TYPE_1__* qd_gl; } ;
typedef  scalar_t__ s64 ;
struct TYPE_3__ {struct gfs2_sbd* gl_sbd; } ;

/* Variables and functions */
 scalar_t__ be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ div_s64 (scalar_t__,unsigned int) ; 
 unsigned int gfs2_jindex_size (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  qd_lru_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int need_sync(struct gfs2_quota_data *qd)
{
	struct gfs2_sbd *sdp = qd->qd_gl->gl_sbd;
	struct gfs2_tune *gt = &sdp->sd_tune;
	s64 value;
	unsigned int num, den;
	int do_sync = 1;

	if (!qd->qd_qb.qb_limit)
		return 0;

	spin_lock(&qd_lru_lock);
	value = qd->qd_change;
	spin_unlock(&qd_lru_lock);

	spin_lock(&gt->gt_spin);
	num = gt->gt_quota_scale_num;
	den = gt->gt_quota_scale_den;
	spin_unlock(&gt->gt_spin);

	if (value < 0)
		do_sync = 0;
	else if ((s64)be64_to_cpu(qd->qd_qb.qb_value) >=
		 (s64)be64_to_cpu(qd->qd_qb.qb_limit))
		do_sync = 0;
	else {
		value *= gfs2_jindex_size(sdp) * num;
		value = div_s64(value, den);
		value += (s64)be64_to_cpu(qd->qd_qb.qb_value);
		if (value < (s64)be64_to_cpu(qd->qd_qb.qb_limit))
			do_sync = 0;
	}

	return do_sync;
}