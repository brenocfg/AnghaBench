#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct super_block {int dummy; } ;
struct inode {int i_state; int /*<<< orphan*/  i_mode; } ;
struct gfs2_sbd {int dummy; } ;
struct TYPE_5__ {TYPE_1__* gh_gl; int /*<<< orphan*/  gh_flags; } ;
struct gfs2_inode {struct gfs2_glock* i_gl; TYPE_2__ i_iopen_gh; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  i_no_formal_ino; } ;
struct gfs2_glock {struct gfs2_inode* gl_object; } ;
struct TYPE_4__ {struct gfs2_inode* gl_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE ; 
 int /*<<< orphan*/  DT2IF (unsigned int) ; 
 unsigned int DT_UNKNOWN ; 
 int ENOBUFS ; 
 struct inode* ERR_PTR (int) ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 int /*<<< orphan*/  GIF_INVALID ; 
 int /*<<< orphan*/  GL_EXACT ; 
 int /*<<< orphan*/  GL_NOCACHE ; 
 int I_NEW ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (TYPE_2__*) ; 
 int gfs2_glock_get (struct gfs2_sbd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct gfs2_glock**) ; 
 int gfs2_glock_nq_init (struct gfs2_glock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  gfs2_glock_put (struct gfs2_glock*) ; 
 struct inode* gfs2_iget (struct super_block*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfs2_inode_glops ; 
 int gfs2_inode_refresh (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_iopen_glops ; 
 int /*<<< orphan*/  gfs2_set_iop (struct inode*) ; 
 int /*<<< orphan*/  iget_failed (struct inode*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *gfs2_inode_lookup(struct super_block *sb, unsigned int type,
				u64 no_addr, u64 no_formal_ino, int non_block)
{
	struct inode *inode;
	struct gfs2_inode *ip;
	struct gfs2_glock *io_gl = NULL;
	int error;

	inode = gfs2_iget(sb, no_addr, non_block);
	ip = GFS2_I(inode);

	if (!inode)
		return ERR_PTR(-ENOBUFS);

	if (inode->i_state & I_NEW) {
		struct gfs2_sbd *sdp = GFS2_SB(inode);
		ip->i_no_formal_ino = no_formal_ino;

		error = gfs2_glock_get(sdp, no_addr, &gfs2_inode_glops, CREATE, &ip->i_gl);
		if (unlikely(error))
			goto fail;
		ip->i_gl->gl_object = ip;

		error = gfs2_glock_get(sdp, no_addr, &gfs2_iopen_glops, CREATE, &io_gl);
		if (unlikely(error))
			goto fail_put;

		set_bit(GIF_INVALID, &ip->i_flags);
		error = gfs2_glock_nq_init(io_gl, LM_ST_SHARED, GL_EXACT, &ip->i_iopen_gh);
		if (unlikely(error))
			goto fail_iopen;

		ip->i_iopen_gh.gh_gl->gl_object = ip;
		gfs2_glock_put(io_gl);
		io_gl = NULL;

 		if (type == DT_UNKNOWN) {
			/* Inode glock must be locked already */
			error = gfs2_inode_refresh(GFS2_I(inode));
			if (error)
				goto fail_refresh;
		} else {
			inode->i_mode = DT2IF(type);
		}

		gfs2_set_iop(inode);
		unlock_new_inode(inode);
	}

	return inode;

fail_refresh:
	ip->i_iopen_gh.gh_flags |= GL_NOCACHE;
	ip->i_iopen_gh.gh_gl->gl_object = NULL;
	gfs2_glock_dq_uninit(&ip->i_iopen_gh);
fail_iopen:
	if (io_gl)
		gfs2_glock_put(io_gl);
fail_put:
	ip->i_gl->gl_object = NULL;
	gfs2_glock_put(ip->i_gl);
fail:
	iget_failed(inode);
	return ERR_PTR(error);
}