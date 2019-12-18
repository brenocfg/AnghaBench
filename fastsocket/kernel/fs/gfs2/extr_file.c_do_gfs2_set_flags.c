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
typedef  int u32 ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct gfs2_sbd {int dummy; } ;
struct gfs2_inode {int i_diskflags; int /*<<< orphan*/  i_gl; } ;
struct gfs2_holder {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  mnt; TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; } ;
struct buffer_head {int /*<<< orphan*/  b_data; } ;
struct TYPE_3__ {struct inode* d_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_LINUX_IMMUTABLE ; 
 int EACCES ; 
 int EINVAL ; 
 int EPERM ; 
 int GFS2_DIF_APPENDONLY ; 
 int GFS2_DIF_IMMUTABLE ; 
 int GFS2_DIF_JDATA ; 
 int GFS2_FLAGS_USER_SET ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 struct gfs2_sbd* GFS2_SB (struct inode*) ; 
 scalar_t__ IS_APPEND (struct inode*) ; 
 scalar_t__ IS_IMMUTABLE (struct inode*) ; 
 int /*<<< orphan*/  LM_ST_EXCLUSIVE ; 
 int /*<<< orphan*/  MAY_WRITE ; 
 int /*<<< orphan*/  RES_DINODE ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int filemap_fdatawait (int /*<<< orphan*/ ) ; 
 int filemap_fdatawrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_dinode_out (struct gfs2_inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_log_flush (struct gfs2_sbd*,int /*<<< orphan*/ ) ; 
 int gfs2_meta_inode_buffer (struct gfs2_inode*,struct buffer_head**) ; 
 int gfs2_permission (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_set_aops (struct inode*) ; 
 int /*<<< orphan*/  gfs2_set_inode_flags (struct inode*) ; 
 int /*<<< orphan*/  gfs2_trans_add_meta (int /*<<< orphan*/ ,struct buffer_head*) ; 
 int gfs2_trans_begin (struct gfs2_sbd*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_trans_end (struct gfs2_sbd*) ; 
 int /*<<< orphan*/  is_owner_or_cap (struct inode*) ; 
 int /*<<< orphan*/  mnt_drop_write (int /*<<< orphan*/ ) ; 
 int mnt_want_write (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_gfs2_set_flags(struct file *filp, u32 reqflags, u32 mask)
{
	struct inode *inode = filp->f_path.dentry->d_inode;
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_sbd *sdp = GFS2_SB(inode);
	struct buffer_head *bh;
	struct gfs2_holder gh;
	int error;
	u32 new_flags, flags;

	error = mnt_want_write(filp->f_path.mnt);
	if (error)
		return error;

	error = gfs2_glock_nq_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, &gh);
	if (error)
		goto out_drop_write;

	error = -EACCES;
	if (!is_owner_or_cap(inode))
		goto out;

	error = 0;
	flags = ip->i_diskflags;
	new_flags = (flags & ~mask) | (reqflags & mask);
	if ((new_flags ^ flags) == 0)
		goto out;

	error = -EINVAL;
	if ((new_flags ^ flags) & ~GFS2_FLAGS_USER_SET)
		goto out;

	error = -EPERM;
	if (IS_IMMUTABLE(inode) && (new_flags & GFS2_DIF_IMMUTABLE))
		goto out;
	if (IS_APPEND(inode) && (new_flags & GFS2_DIF_APPENDONLY))
		goto out;
	if (((new_flags ^ flags) & GFS2_DIF_IMMUTABLE) &&
	    !capable(CAP_LINUX_IMMUTABLE))
		goto out;
	if (!IS_IMMUTABLE(inode)) {
		error = gfs2_permission(inode, MAY_WRITE);
		if (error)
			goto out;
	}
	if ((flags ^ new_flags) & GFS2_DIF_JDATA) {
		if (flags & GFS2_DIF_JDATA)
			gfs2_log_flush(sdp, ip->i_gl);
		error = filemap_fdatawrite(inode->i_mapping);
		if (error)
			goto out;
		error = filemap_fdatawait(inode->i_mapping);
		if (error)
			goto out;
	}
	error = gfs2_trans_begin(sdp, RES_DINODE, 0);
	if (error)
		goto out;
	error = gfs2_meta_inode_buffer(ip, &bh);
	if (error)
		goto out_trans_end;
	gfs2_trans_add_meta(ip->i_gl, bh);
	ip->i_diskflags = new_flags;
	gfs2_dinode_out(ip, bh->b_data);
	brelse(bh);
	gfs2_set_inode_flags(inode);
	gfs2_set_aops(inode);
out_trans_end:
	gfs2_trans_end(sdp);
out:
	gfs2_glock_dq_uninit(&gh);
out_drop_write:
	mnt_drop_write(filp->f_path.mnt);
	return error;
}