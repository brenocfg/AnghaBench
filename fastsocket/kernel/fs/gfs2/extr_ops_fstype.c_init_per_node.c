#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct TYPE_5__ {scalar_t__ ar_spectator; } ;
struct gfs2_sbd {struct inode* sd_sc_inode; struct inode* sd_qc_inode; int /*<<< orphan*/  sd_sc_gh; int /*<<< orphan*/  sd_qc_gh; TYPE_3__* sd_jdesc; TYPE_2__ sd_args; TYPE_1__* sd_master_dir; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; } ;
struct TYPE_6__ {int jd_jid; } ;
struct TYPE_4__ {struct inode* d_inode; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,int) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (int /*<<< orphan*/ *) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* gfs2_lookup_simple (struct inode*,char*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static int init_per_node(struct gfs2_sbd *sdp, int undo)
{
	struct inode *pn = NULL;
	char buf[30];
	int error = 0;
	struct gfs2_inode *ip;
	struct inode *master = sdp->sd_master_dir->d_inode;

	if (sdp->sd_args.ar_spectator)
		return 0;

	if (undo)
		goto fail_qc_gh;

	pn = gfs2_lookup_simple(master, "per_node");
	if (IS_ERR(pn)) {
		error = PTR_ERR(pn);
		fs_err(sdp, "can't find per_node directory: %d\n", error);
		return error;
	}

	sprintf(buf, "statfs_change%u", sdp->sd_jdesc->jd_jid);
	sdp->sd_sc_inode = gfs2_lookup_simple(pn, buf);
	if (IS_ERR(sdp->sd_sc_inode)) {
		error = PTR_ERR(sdp->sd_sc_inode);
		fs_err(sdp, "can't find local \"sc\" file: %d\n", error);
		goto fail;
	}

	sprintf(buf, "quota_change%u", sdp->sd_jdesc->jd_jid);
	sdp->sd_qc_inode = gfs2_lookup_simple(pn, buf);
	if (IS_ERR(sdp->sd_qc_inode)) {
		error = PTR_ERR(sdp->sd_qc_inode);
		fs_err(sdp, "can't find local \"qc\" file: %d\n", error);
		goto fail_ut_i;
	}

	iput(pn);
	pn = NULL;

	ip = GFS2_I(sdp->sd_sc_inode);
	error = gfs2_glock_nq_init(ip->i_gl, LM_ST_EXCLUSIVE, 0,
				   &sdp->sd_sc_gh);
	if (error) {
		fs_err(sdp, "can't lock local \"sc\" file: %d\n", error);
		goto fail_qc_i;
	}

	ip = GFS2_I(sdp->sd_qc_inode);
	error = gfs2_glock_nq_init(ip->i_gl, LM_ST_EXCLUSIVE, 0,
				   &sdp->sd_qc_gh);
	if (error) {
		fs_err(sdp, "can't lock local \"qc\" file: %d\n", error);
		goto fail_ut_gh;
	}

	return 0;

fail_qc_gh:
	gfs2_glock_dq_uninit(&sdp->sd_qc_gh);
fail_ut_gh:
	gfs2_glock_dq_uninit(&sdp->sd_sc_gh);
fail_qc_i:
	iput(sdp->sd_qc_inode);
fail_ut_i:
	iput(sdp->sd_sc_inode);
fail:
	if (pn)
		iput(pn);
	return error;
}