#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct qstr {scalar_t__ len; } ;
struct inode {unsigned int i_mode; unsigned int i_size; TYPE_4__* i_sb; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_rdev; } ;
struct gfs2_sbd {TYPE_1__* sd_root_dir; int /*<<< orphan*/  sd_vfs; } ;
struct gfs2_holder {TYPE_2__* gh_gl; } ;
struct gfs2_inode {int i_diskflags; int /*<<< orphan*/  i_flags; struct gfs2_glock* i_gl; struct gfs2_holder i_iopen_gh; int /*<<< orphan*/  i_no_addr; scalar_t__ i_entries; scalar_t__ i_depth; scalar_t__ i_height; scalar_t__ i_eattr; int /*<<< orphan*/  i_goal; int /*<<< orphan*/  i_inode; } ;
struct gfs2_glock {struct gfs2_inode* gl_object; } ;
struct dentry {struct qstr d_name; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_8__ {TYPE_3__* s_op; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* destroy_inode ) (struct inode*) ;} ;
struct TYPE_6__ {struct gfs2_inode* gl_object; } ;
struct TYPE_5__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE ; 
 int /*<<< orphan*/  CURRENT_TIME ; 
 int EEXIST ; 
 int ENAMETOOLONG ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFS2_AF_ORLOV ; 
 int GFS2_DIF_TOPDIR ; 
 scalar_t__ GFS2_FNAMESIZE ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GIF_ALLOC_FAILED ; 
 int /*<<< orphan*/  GIF_INVALID ; 
 int /*<<< orphan*/  GL_EXACT ; 
 int /*<<< orphan*/  GL_SKIP ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  RES_DINODE ; 
 scalar_t__ S_ISREG (unsigned int) ; 
 int alloc_dinode (struct gfs2_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int create_ok (struct gfs2_inode*,struct qstr const*,unsigned int) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int gfs2_acl_create (struct gfs2_inode*,struct inode*) ; 
 int gfs2_diradd_alloc_required (struct inode*,struct qstr const*) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit_m (int,struct gfs2_holder*) ; 
 int gfs2_glock_get (struct gfs2_sbd*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct gfs2_glock**) ; 
 int gfs2_glock_nq_init (struct gfs2_glock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_glock_put (struct gfs2_glock*) ; 
 int /*<<< orphan*/  gfs2_inode_glops ; 
 int gfs2_inode_refresh (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_inplace_release (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_iopen_glops ; 
 struct inode* gfs2_lookupi (struct inode*,struct qstr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_quota_unlock (struct gfs2_inode*) ; 
 int gfs2_rindex_update (struct gfs2_sbd*) ; 
 int gfs2_rs_alloc (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_rs_delete (struct gfs2_inode*) ; 
 int gfs2_security_init (struct gfs2_inode*,struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_set_inode_blocks (struct inode*,int) ; 
 int /*<<< orphan*/  gfs2_set_iop (struct inode*) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  init_dinode (struct gfs2_inode*,struct gfs2_inode*,char const*,struct buffer_head**) ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int link_dinode (struct gfs2_inode*,struct qstr const*,struct gfs2_inode*,int) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  munge_mode_uid_gid (struct gfs2_inode*,struct inode*) ; 
 struct inode* new_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct inode*) ; 

int gfs2_create_inode(struct inode *dir, struct dentry *dentry,
		      unsigned int mode, dev_t dev, const char *symname,
		      unsigned int size, int excl)
{
	const struct qstr *name = &dentry->d_name;
	struct gfs2_holder ghs[2];
	struct inode *inode = NULL;
	struct gfs2_inode *dip = GFS2_I(dir), *ip;
	struct gfs2_sbd *sdp = GFS2_SB(&dip->i_inode);
	struct gfs2_glock *io_gl;
	int error;
	struct buffer_head *bh = NULL;
	u32 aflags = 0;
	int arq;

	if (!name->len || name->len > GFS2_FNAMESIZE)
		return -ENAMETOOLONG;

	error = gfs2_rs_alloc(dip);
	if (error)
		return error;

	error = gfs2_rindex_update(sdp);
	if (error)
		return error;

	error = gfs2_glock_nq_init(dip->i_gl, LM_ST_EXCLUSIVE, 0, ghs);
	if (error)
		goto fail;

	error = create_ok(dip, name, mode);
	if ((error == -EEXIST) && S_ISREG(mode) && !excl) {
		inode = gfs2_lookupi(dir, &dentry->d_name, 0);
		if (inode)
			gfs2_glock_dq_uninit(ghs);
		if (!IS_ERR(inode))
			d_instantiate(dentry, inode);
		return IS_ERR(inode) ? PTR_ERR(inode) : 0;
	}
	if (error)
		goto fail_gunlock;

	arq = error = gfs2_diradd_alloc_required(dir, name);
	if (error < 0)
		goto fail_gunlock;

	inode = new_inode(sdp->sd_vfs);
	if (!inode) {
		gfs2_glock_dq_uninit(ghs);
		return -ENOMEM;
	}
	ip = GFS2_I(inode);
	error = gfs2_rs_alloc(ip);
	if (error)
		goto fail_free_inode;

	set_bit(GIF_INVALID, &ip->i_flags);
	inode->i_mode = mode;
	inode->i_rdev = dev;
	inode->i_size = size;
	inode->i_atime = inode->i_mtime = inode->i_ctime = CURRENT_TIME;
	gfs2_set_inode_blocks(inode, 1);
	munge_mode_uid_gid(dip, inode);
	ip->i_goal = dip->i_goal;
	ip->i_diskflags = 0;
	ip->i_eattr = 0;
	ip->i_height = 0;
	ip->i_depth = 0;
	ip->i_entries = 0;

	if ((GFS2_I(sdp->sd_root_dir->d_inode) == dip) ||
	    (dip->i_diskflags & GFS2_DIF_TOPDIR))
		aflags |= GFS2_AF_ORLOV;

	error = alloc_dinode(ip, aflags);
	if (error)
		goto fail_free_inode;

	error = gfs2_glock_get(sdp, ip->i_no_addr, &gfs2_inode_glops, CREATE, &ip->i_gl);
	if (error)
		goto fail_free_inode;

	ip->i_gl->gl_object = ip;
	error = gfs2_glock_nq_init(ip->i_gl, LM_ST_EXCLUSIVE, GL_SKIP, ghs + 1);
	if (error)
		goto fail_free_inode;

	error = gfs2_trans_begin(sdp, RES_DINODE, 0);
	if (error)
		goto fail_gunlock2;

	init_dinode(dip, ip, symname, &bh);
	gfs2_trans_end(sdp);

	error = gfs2_glock_get(sdp, ip->i_no_addr, &gfs2_iopen_glops, CREATE, &io_gl);
	if (error)
		goto fail_gunlock2;

	error = gfs2_glock_nq_init(io_gl, LM_ST_SHARED, GL_EXACT, &ip->i_iopen_gh);
	if (error)
		goto fail_gunlock2;

	ip->i_iopen_gh.gh_gl->gl_object = ip;
	gfs2_glock_put(io_gl);
	gfs2_set_iop(inode);
	insert_inode_hash(inode);

	error = gfs2_inode_refresh(ip);
	if (error)
		goto fail_gunlock3;

	error = gfs2_acl_create(dip, inode);
	if (error)
		goto fail_gunlock3;

	error = gfs2_security_init(dip, ip);
	if (error)
		goto fail_gunlock3;

	error = link_dinode(dip, name, ip, arq);
	if (error)
		goto fail_gunlock3;

	if (bh)
		brelse(bh);

	gfs2_trans_end(sdp);
	gfs2_inplace_release(dip);
	gfs2_quota_unlock(dip);
	mark_inode_dirty(inode);
	gfs2_glock_dq_uninit_m(2, ghs);
	d_instantiate(dentry, inode);
	return 0;

fail_gunlock3:
	gfs2_glock_dq_uninit(ghs + 1);
	if (ip->i_gl)
		gfs2_glock_put(ip->i_gl);
	goto fail_gunlock;

fail_gunlock2:
	gfs2_glock_dq_uninit(ghs + 1);
fail_free_inode:
	if (ip->i_gl)
		gfs2_glock_put(ip->i_gl);
	gfs2_rs_delete(ip);
	inode->i_sb->s_op->destroy_inode(inode);
	inode = NULL;
fail_gunlock:
	gfs2_glock_dq_uninit(ghs);
	if (inode && !IS_ERR(inode)) {
		set_bit(GIF_ALLOC_FAILED, &GFS2_I(inode)->i_flags);
		iput(inode);
	}
fail:
	if (bh)
		brelse(bh);
	return error;
}