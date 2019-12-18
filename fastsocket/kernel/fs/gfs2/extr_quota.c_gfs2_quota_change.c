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
typedef  scalar_t__ u32 ;
struct gfs2_quota_data {scalar_t__ qd_id; int /*<<< orphan*/  qd_flags; } ;
struct gfs2_inode {int i_diskflags; TYPE_1__* i_res; int /*<<< orphan*/  i_inode; } ;
typedef  int /*<<< orphan*/  s64 ;
struct TYPE_2__ {unsigned int rs_qa_qd_num; struct gfs2_quota_data** rs_qa_qd; } ;

/* Variables and functions */
 int GFS2_DIF_SYSTEM ; 
 int /*<<< orphan*/  GFS2_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QDF_USER ; 
 int /*<<< orphan*/  do_qc (struct gfs2_quota_data*,int /*<<< orphan*/ ) ; 
 scalar_t__ gfs2_assert_warn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void gfs2_quota_change(struct gfs2_inode *ip, s64 change,
		       u32 uid, u32 gid)
{
	struct gfs2_quota_data *qd;
	unsigned int x;

	if (gfs2_assert_warn(GFS2_SB(&ip->i_inode), change))
		return;
	if (ip->i_diskflags & GFS2_DIF_SYSTEM)
		return;

	for (x = 0; x < ip->i_res->rs_qa_qd_num; x++) {
		qd = ip->i_res->rs_qa_qd[x];

		if ((qd->qd_id == uid && test_bit(QDF_USER, &qd->qd_flags)) ||
		    (qd->qd_id == gid && !test_bit(QDF_USER, &qd->qd_flags))) {
			do_qc(qd, change);
		}
	}
}