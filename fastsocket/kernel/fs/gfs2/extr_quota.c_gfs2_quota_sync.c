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
struct super_block {struct gfs2_sbd* s_fs_info; } ;
struct gfs2_sbd {scalar_t__ sd_quota_sync_gen; } ;
struct gfs2_quota_data {scalar_t__ qd_sync_gen; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int do_sync (unsigned int,struct gfs2_quota_data**) ; 
 unsigned int gfs2_tune_get (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gt_quota_simul_sync ; 
 struct gfs2_quota_data** kcalloc (unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct gfs2_quota_data**) ; 
 int qd_fish (struct gfs2_sbd*,struct gfs2_quota_data**) ; 
 int /*<<< orphan*/  qd_unlock (struct gfs2_quota_data*) ; 

int gfs2_quota_sync(struct super_block *sb, int type)
{
	struct gfs2_sbd *sdp = sb->s_fs_info;
	struct gfs2_quota_data **qda;
	unsigned int max_qd = gfs2_tune_get(sdp, gt_quota_simul_sync);
	unsigned int num_qd;
	unsigned int x;
	int error = 0;

	sdp->sd_quota_sync_gen++;

	qda = kcalloc(max_qd, sizeof(struct gfs2_quota_data *), GFP_KERNEL);
	if (!qda)
		return -ENOMEM;

	do {
		num_qd = 0;

		for (;;) {
			error = qd_fish(sdp, qda + num_qd);
			if (error || !qda[num_qd])
				break;
			if (++num_qd == max_qd)
				break;
		}

		if (num_qd) {
			if (!error)
				error = do_sync(num_qd, qda);
			if (!error)
				for (x = 0; x < num_qd; x++)
					qda[x]->qd_sync_gen =
						sdp->sd_quota_sync_gen;

			for (x = 0; x < num_qd; x++)
				qd_unlock(qda[x]);
		}
	} while (!error && num_qd == max_qd);

	kfree(qda);

	return error;
}