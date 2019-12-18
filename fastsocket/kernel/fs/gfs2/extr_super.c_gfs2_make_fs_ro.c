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
struct gfs2_sbd {int /*<<< orphan*/  sd_flags; int /*<<< orphan*/  sd_trans_gl; int /*<<< orphan*/  sd_vfs; } ;
struct gfs2_holder {scalar_t__ gh_gl; } ;

/* Variables and functions */
 int /*<<< orphan*/  GL_NOCACHE ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 int /*<<< orphan*/  SDF_JOURNAL_LIVE ; 
 int /*<<< orphan*/  SDF_SHUTDOWN ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_delete_workqueue ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_log_shutdown (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_meta_syncfs (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_quota_cleanup (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_quota_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_statfs_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gfs2_make_fs_ro(struct gfs2_sbd *sdp)
{
	struct gfs2_holder t_gh;
	int error;

	flush_workqueue(gfs2_delete_workqueue);
	gfs2_quota_sync(sdp->sd_vfs, 0);
	gfs2_statfs_sync(sdp->sd_vfs, 0);

	error = gfs2_glock_nq_init(sdp->sd_trans_gl, LM_ST_SHARED, GL_NOCACHE,
				   &t_gh);
	if (error && !test_bit(SDF_SHUTDOWN, &sdp->sd_flags))
		return error;

	gfs2_meta_syncfs(sdp);
	gfs2_log_shutdown(sdp);

	clear_bit(SDF_JOURNAL_LIVE, &sdp->sd_flags);

	if (t_gh.gh_gl)
		gfs2_glock_dq_uninit(&t_gh);

	gfs2_quota_cleanup(sdp);

	return error;
}