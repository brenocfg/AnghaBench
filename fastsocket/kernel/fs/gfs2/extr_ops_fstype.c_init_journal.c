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
struct gfs2_holder {int dummy; } ;
struct TYPE_6__ {scalar_t__ ar_spectator; } ;
struct TYPE_5__ {int ls_jid; scalar_t__ ls_first; } ;
struct gfs2_sbd {unsigned int sd_journals; int /*<<< orphan*/  sd_jindex; struct gfs2_holder sd_journal_gh; TYPE_3__ sd_args; struct gfs2_holder sd_jinode_gh; int /*<<< orphan*/  sd_flags; struct gfs2_jdesc* sd_jdesc; TYPE_2__ sd_lockstruct; int /*<<< orphan*/  sd_log_blks_free; TYPE_1__* sd_master_dir; } ;
struct gfs2_jdesc {int /*<<< orphan*/  jd_blocks; int /*<<< orphan*/  jd_jid; int /*<<< orphan*/  jd_inode; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; } ;
struct TYPE_4__ {struct inode* d_inode; } ;

/* Variables and functions */
 int EUSERS ; 
 struct gfs2_inode* GFS2_I (int /*<<< orphan*/ ) ; 
 int GL_EXACT ; 
 int GL_NOCACHE ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int LM_FLAG_NOEXP ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDF_JOURNAL_CHECKED ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int check_journal_clean (struct gfs2_sbd*,struct gfs2_jdesc*) ; 
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,...) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct gfs2_holder*) ; 
 int gfs2_glock_nq_num (struct gfs2_sbd*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,struct gfs2_holder*) ; 
 int gfs2_jdesc_check (struct gfs2_jdesc*) ; 
 void* gfs2_jdesc_find (struct gfs2_sbd*,unsigned int) ; 
 int /*<<< orphan*/  gfs2_jindex_free (struct gfs2_sbd*) ; 
 int gfs2_jindex_hold (struct gfs2_sbd*,struct gfs2_holder*) ; 
 int gfs2_jindex_size (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  gfs2_journal_glops ; 
 int /*<<< orphan*/  gfs2_lookup_simple (struct inode*,char*) ; 
 int /*<<< orphan*/  gfs2_others_may_mount (struct gfs2_sbd*) ; 
 int gfs2_recover_journal (struct gfs2_jdesc*) ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_journal_extents (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_gfs2_log_blocks (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_journal(struct gfs2_sbd *sdp, int undo)
{
	struct inode *master = sdp->sd_master_dir->d_inode;
	struct gfs2_holder ji_gh;
	struct gfs2_inode *ip;
	int jindex = 1;
	int error = 0;

	if (undo) {
		jindex = 0;
		goto fail_jinode_gh;
	}

	sdp->sd_jindex = gfs2_lookup_simple(master, "jindex");
	if (IS_ERR(sdp->sd_jindex)) {
		fs_err(sdp, "can't lookup journal index: %d\n", error);
		return PTR_ERR(sdp->sd_jindex);
	}

	/* Load in the journal index special file */

	error = gfs2_jindex_hold(sdp, &ji_gh);
	if (error) {
		fs_err(sdp, "can't read journal index: %d\n", error);
		goto fail;
	}

	error = -EUSERS;
	if (!gfs2_jindex_size(sdp)) {
		fs_err(sdp, "no journals!\n");
		goto fail_jindex;
	}

	if (sdp->sd_args.ar_spectator) {
		sdp->sd_jdesc = gfs2_jdesc_find(sdp, 0);
		atomic_set(&sdp->sd_log_blks_free, sdp->sd_jdesc->jd_blocks);
	} else {
		if (sdp->sd_lockstruct.ls_jid >= gfs2_jindex_size(sdp)) {
			fs_err(sdp, "can't mount journal #%u\n",
			       sdp->sd_lockstruct.ls_jid);
			fs_err(sdp, "there are only %u journals (0 - %u)\n",
			       gfs2_jindex_size(sdp),
			       gfs2_jindex_size(sdp) - 1);
			goto fail_jindex;
		}
		sdp->sd_jdesc = gfs2_jdesc_find(sdp, sdp->sd_lockstruct.ls_jid);

		error = gfs2_glock_nq_num(sdp, sdp->sd_lockstruct.ls_jid,
					  &gfs2_journal_glops,
					  LM_ST_EXCLUSIVE, LM_FLAG_NOEXP,
					  &sdp->sd_journal_gh);
		if (error) {
			fs_err(sdp, "can't acquire journal glock: %d\n", error);
			goto fail_jindex;
		}

		ip = GFS2_I(sdp->sd_jdesc->jd_inode);
		error = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED,
					   LM_FLAG_NOEXP | GL_EXACT | GL_NOCACHE,
					   &sdp->sd_jinode_gh);
		if (error) {
			fs_err(sdp, "can't acquire journal inode glock: %d\n",
			       error);
			goto fail_journal_gh;
		}

		error = gfs2_jdesc_check(sdp->sd_jdesc);
		if (error) {
			fs_err(sdp, "my journal (%u) is bad: %d\n",
			       sdp->sd_jdesc->jd_jid, error);
			goto fail_jinode_gh;
		}
		atomic_set(&sdp->sd_log_blks_free, sdp->sd_jdesc->jd_blocks);

		/* Map the extents for this journal's blocks */
		map_journal_extents(sdp);
	}
	trace_gfs2_log_blocks(sdp, atomic_read(&sdp->sd_log_blks_free));

	if (sdp->sd_lockstruct.ls_first) {
		unsigned int x;
		for (x = 0; x < sdp->sd_journals; x++) {
			struct gfs2_jdesc *jd = gfs2_jdesc_find(sdp, x);

			if (sdp->sd_args.ar_spectator) {
				error = check_journal_clean(sdp, jd);
				if (error)
					goto fail_jinode_gh;
				continue;
			}
			error = gfs2_recover_journal(jd);
			if (error) {
				fs_err(sdp, "error recovering journal %u: %d\n",
				       x, error);
				goto fail_jinode_gh;
			}
		}

		gfs2_others_may_mount(sdp);
	} else if (!sdp->sd_args.ar_spectator) {
		error = gfs2_recover_journal(sdp->sd_jdesc);
		if (error) {
			fs_err(sdp, "error recovering my journal: %d\n", error);
			goto fail_jinode_gh;
		}
	}

	set_bit(SDF_JOURNAL_CHECKED, &sdp->sd_flags);
	gfs2_glock_dq_uninit(&ji_gh);
	jindex = 0;

	return 0;

fail_jinode_gh:
	if (!sdp->sd_args.ar_spectator)
		gfs2_glock_dq_uninit(&sdp->sd_jinode_gh);
fail_journal_gh:
	if (!sdp->sd_args.ar_spectator)
		gfs2_glock_dq_uninit(&sdp->sd_journal_gh);
fail_jindex:
	gfs2_jindex_free(sdp);
	if (jindex)
		gfs2_glock_dq_uninit(&ji_gh);
fail:
	iput(sdp->sd_jindex);
	return error;
}