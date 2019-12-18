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
struct gfs2_quota_data {int dummy; } ;
struct gfs2_inode {TYPE_1__* i_res; int /*<<< orphan*/  i_flags; } ;
struct TYPE_2__ {unsigned int rs_qa_qd_num; int /*<<< orphan*/ * rs_qa_qd_ghs; struct gfs2_quota_data** rs_qa_qd; } ;

/* Variables and functions */
 int /*<<< orphan*/  GIF_QD_LOCKED ; 
 int /*<<< orphan*/  do_sync (unsigned int,struct gfs2_quota_data**) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_quota_unhold (struct gfs2_inode*) ; 
 int need_sync (struct gfs2_quota_data*) ; 
 scalar_t__ qd_trylock (struct gfs2_quota_data*) ; 
 int /*<<< orphan*/  qd_unlock (struct gfs2_quota_data*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void gfs2_quota_unlock(struct gfs2_inode *ip)
{
	struct gfs2_quota_data *qda[4];
	unsigned int count = 0;
	unsigned int x;

	if (!test_and_clear_bit(GIF_QD_LOCKED, &ip->i_flags))
		goto out;

	for (x = 0; x < ip->i_res->rs_qa_qd_num; x++) {
		struct gfs2_quota_data *qd;
		int sync;

		qd = ip->i_res->rs_qa_qd[x];
		sync = need_sync(qd);

		gfs2_glock_dq_uninit(&ip->i_res->rs_qa_qd_ghs[x]);

		if (sync && qd_trylock(qd))
			qda[count++] = qd;
	}

	if (count) {
		do_sync(count, qda);
		for (x = 0; x < count; x++)
			qd_unlock(qda[x]);
	}

out:
	gfs2_quota_unhold(ip);
}