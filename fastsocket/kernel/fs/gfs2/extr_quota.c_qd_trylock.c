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
struct gfs2_sbd {int /*<<< orphan*/  sd_quota_list; TYPE_2__* sd_vfs; } ;
struct gfs2_quota_data {int /*<<< orphan*/  qd_flags; int /*<<< orphan*/  qd_change_sync; int /*<<< orphan*/  qd_slot_count; int /*<<< orphan*/  qd_change; int /*<<< orphan*/  qd_count; int /*<<< orphan*/  qd_list; TYPE_1__* qd_gl; } ;
struct TYPE_4__ {int s_flags; } ;
struct TYPE_3__ {struct gfs2_sbd* gl_sbd; } ;

/* Variables and functions */
 int MS_RDONLY ; 
 int /*<<< orphan*/  QDF_CHANGE ; 
 int /*<<< orphan*/  QDF_LOCKED ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ bh_get (struct gfs2_quota_data*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_assert_warn (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  qd_lru_lock ; 
 int /*<<< orphan*/  qd_put (struct gfs2_quota_data*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slot_put (struct gfs2_quota_data*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qd_trylock(struct gfs2_quota_data *qd)
{
	struct gfs2_sbd *sdp = qd->qd_gl->gl_sbd;

	if (sdp->sd_vfs->s_flags & MS_RDONLY)
		return 0;

	spin_lock(&qd_lru_lock);

	if (test_bit(QDF_LOCKED, &qd->qd_flags) ||
	    !test_bit(QDF_CHANGE, &qd->qd_flags)) {
		spin_unlock(&qd_lru_lock);
		return 0;
	}

	list_move_tail(&qd->qd_list, &sdp->sd_quota_list);

	set_bit(QDF_LOCKED, &qd->qd_flags);
	gfs2_assert_warn(sdp, atomic_read(&qd->qd_count));
	atomic_inc(&qd->qd_count);
	qd->qd_change_sync = qd->qd_change;
	gfs2_assert_warn(sdp, qd->qd_slot_count);
	qd->qd_slot_count++;

	spin_unlock(&qd_lru_lock);

	gfs2_assert_warn(sdp, qd->qd_change_sync);
	if (bh_get(qd)) {
		clear_bit(QDF_LOCKED, &qd->qd_flags);
		slot_put(qd);
		qd_put(qd);
		return 0;
	}

	return 1;
}