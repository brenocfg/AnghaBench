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
struct inode {int dummy; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; } ;
struct gfs2_holder {int dummy; } ;
struct file {int /*<<< orphan*/  f_pos; int /*<<< orphan*/  f_ra; TYPE_1__* f_mapping; } ;
typedef  int /*<<< orphan*/  filldir_t ;
struct TYPE_2__ {struct inode* host; } ;

/* Variables and functions */
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 int gfs2_dir_read (struct inode*,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_glock_nq (struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 int /*<<< orphan*/  gfs2_holder_uninit (struct gfs2_holder*) ; 

__attribute__((used)) static int gfs2_readdir(struct file *file, void *dirent, filldir_t filldir)
{
	struct inode *dir = file->f_mapping->host;
	struct gfs2_inode *dip = GFS2_I(dir);
	struct gfs2_holder d_gh;
	u64 offset = file->f_pos;
	int error;

	gfs2_holder_init(dip->i_gl, LM_ST_SHARED, 0, &d_gh);
	error = gfs2_glock_nq(&d_gh);
	if (error) {
		gfs2_holder_uninit(&d_gh);
		return error;
	}

	error = gfs2_dir_read(dir, &offset, dirent, filldir, &file->f_ra);

	gfs2_glock_dq_uninit(&d_gh);

	file->f_pos = offset;

	return error;
}