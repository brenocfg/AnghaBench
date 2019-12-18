#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct inode {int dummy; } ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_inode {TYPE_1__* i_gl; } ;
struct gfs2_holder {int dummy; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
struct TYPE_6__ {int /*<<< orphan*/ * journal_info; } ;
struct TYPE_5__ {scalar_t__ gl_state; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 scalar_t__ LM_ST_EXCLUSIVE ; 
 int /*<<< orphan*/  RES_DINODE ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 TYPE_4__* current ; 
 int /*<<< orphan*/  fs_err (struct gfs2_sbd*,char*,int) ; 
 int /*<<< orphan*/  gfs2_dinode_out (struct gfs2_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_glock_is_locked_by_me (TYPE_1__*) ; 
 int gfs2_glock_nq_init (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int gfs2_meta_inode_buffer (struct gfs2_inode*,struct buffer_head**) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (TYPE_1__*,struct buffer_head*) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 

__attribute__((used)) static void gfs2_dirty_inode(struct inode *inode)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct buffer_head *bh;
	struct gfs2_holder gh;
	int need_unlock = 0;
	int need_endtrans = 0;
	int ret;

	if (!gfs2_glock_is_locked_by_me(ip->i_gl)) {
		ret = gfs2_glock_nq_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, &gh);
		if (ret) {
			fs_err(sdp, "dirty_inode: glock %d\n", ret);
			return;
		}
		need_unlock = 1;
	} else if (WARN_ON_ONCE(ip->i_gl->gl_state != LM_ST_EXCLUSIVE))
		return;

	if (current->journal_info == NULL) {
		ret = gfs2_trans_begin(sdp, RES_DINODE, 0);
		if (ret) {
			fs_err(sdp, "dirty_inode: gfs2_trans_begin %d\n", ret);
			goto out;
		}
		need_endtrans = 1;
	}

	ret = gfs2_meta_inode_buffer(ip, &bh);
	if (ret == 0) {
		gfs2_trans_add_meta(ip->i_gl, bh);
		gfs2_dinode_out(ip, bh->b_data);
		brelse(bh);
	}

	if (need_endtrans)
		gfs2_trans_end(sdp);
out:
	if (need_unlock)
		gfs2_glock_dq_uninit(&gh);
}