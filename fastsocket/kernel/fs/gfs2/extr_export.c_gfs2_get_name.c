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
typedef  int /*<<< orphan*/  u64 ;
struct inode {int /*<<< orphan*/  i_mode; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; int /*<<< orphan*/  i_no_formal_ino; int /*<<< orphan*/  i_no_addr; } ;
struct gfs2_holder {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  no_formal_ino; int /*<<< orphan*/  no_addr; } ;
struct get_name_filldir {char* name; TYPE_1__ inum; } ;
struct dentry {struct inode* d_inode; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOENT ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_name_filldir ; 
 int gfs2_dir_read (struct inode*,int /*<<< orphan*/ *,struct get_name_filldir*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 

__attribute__((used)) static int gfs2_get_name(struct dentry *parent, char *name,
			 struct dentry *child)
{
	struct inode *dir = parent->d_inode;
	struct inode *inode = child->d_inode;
	struct gfs2_inode *dip, *ip;
	struct get_name_filldir gnfd;
	struct gfs2_holder gh;
	u64 offset = 0;
	int error;

	if (!dir)
		return -EINVAL;

	if (!S_ISDIR(dir->i_mode) || !inode)
		return -EINVAL;

	dip = GFS2_I(dir);
	ip = GFS2_I(inode);

	*name = 0;
	gnfd.inum.no_addr = ip->i_no_addr;
	gnfd.inum.no_formal_ino = ip->i_no_formal_ino;
	gnfd.name = name;

	error = gfs2_glock_nq_init(dip->i_gl, LM_ST_SHARED, 0, &gh);
	if (error)
		return error;

	error = gfs2_dir_read(dir, &offset, &gnfd, get_name_filldir, NULL);

	gfs2_glock_dq_uninit(&gh);

	if (!error && !*name)
		error = -ENOENT;

	return error;
}