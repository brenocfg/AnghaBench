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
struct gfs2_sbd {int /*<<< orphan*/  sd_flags; scalar_t__ sd_log_sequence; TYPE_2__* sd_jdesc; int /*<<< orphan*/  sd_trans_gl; } ;
struct gfs2_log_header_host {int lh_flags; int /*<<< orphan*/  lh_blkno; scalar_t__ lh_sequence; } ;
struct gfs2_inode {struct gfs2_glock* i_gl; } ;
struct gfs2_holder {int /*<<< orphan*/  gh_flags; } ;
struct gfs2_glock {TYPE_1__* gl_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  jd_inode; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* go_inval ) (struct gfs2_glock*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DIO_METADATA ; 
 int EIO ; 
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 int GFS2_LOG_HEAD_UNMOUNT ; 
 int /*<<< orphan*/  GL_NOCACHE ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 int /*<<< orphan*/  SDF_JOURNAL_LIVE ; 
 int /*<<< orphan*/  gfs2_consist (struct gfs2_sbd*) ; 
 int gfs2_find_jhead (TYPE_2__*,struct gfs2_log_header_host*) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_log_pointers_init (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 
 int gfs2_quota_init (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct gfs2_glock*,int /*<<< orphan*/ ) ; 

int gfs2_make_fs_rw(struct gfs2_sbd *sdp)
{
	struct gfs2_inode *ip = GFS2_I(sdp->sd_jdesc->jd_inode);
	struct gfs2_glock *j_gl = ip->i_gl;
	struct gfs2_holder t_gh;
	struct gfs2_log_header_host head;
	int error;

	error = gfs2_glock_nq_init(sdp->sd_trans_gl, LM_ST_SHARED, 0, &t_gh);
	if (error)
		return error;

	j_gl->gl_ops->go_inval(j_gl, DIO_METADATA);

	error = gfs2_find_jhead(sdp->sd_jdesc, &head);
	if (error)
		goto fail;

	if (!(head.lh_flags & GFS2_LOG_HEAD_UNMOUNT)) {
		gfs2_consist(sdp);
		error = -EIO;
		goto fail;
	}

	/*  Initialize some head of the log stuff  */
	sdp->sd_log_sequence = head.lh_sequence + 1;
	gfs2_log_pointers_init(sdp, head.lh_blkno);

	error = gfs2_quota_init(sdp);
	if (error)
		goto fail;

	set_bit(SDF_JOURNAL_LIVE, &sdp->sd_flags);

	gfs2_glock_dq_uninit(&t_gh);

	return 0;

fail:
	t_gh.gh_flags |= GL_NOCACHE;
	gfs2_glock_dq_uninit(&t_gh);

	return error;
}