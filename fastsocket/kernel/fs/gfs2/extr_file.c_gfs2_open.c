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
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_mode; } ;
struct gfs2_inode {int /*<<< orphan*/  i_gl; TYPE_1__ i_inode; } ;
struct gfs2_holder {int dummy; } ;
struct gfs2_file {int /*<<< orphan*/  f_fl_mutex; } ;
struct file {int f_flags; struct gfs2_file* private_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int /*<<< orphan*/  GFS2_SB (struct inode*) ; 
 int /*<<< orphan*/  LM_FLAG_ANY ; 
 int /*<<< orphan*/  LM_ST_SHARED ; 
 scalar_t__ MAX_NON_LFS ; 
 int O_LARGEFILE ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfs2_assert_warn (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gfs2_glock_dq_uninit (struct gfs2_holder*) ; 
 int gfs2_glock_nq_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct gfs2_holder*) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct gfs2_file*) ; 
 struct gfs2_file* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gfs2_open(struct inode *inode, struct file *file)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	struct gfs2_holder i_gh;
	struct gfs2_file *fp;
	int error;

	fp = kzalloc(sizeof(struct gfs2_file), GFP_KERNEL);
	if (!fp)
		return -ENOMEM;

	mutex_init(&fp->f_fl_mutex);

	gfs2_assert_warn(GFS2_SB(inode), !file->private_data);
	file->private_data = fp;

	if (S_ISREG(ip->i_inode.i_mode)) {
		error = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED, LM_FLAG_ANY,
					   &i_gh);
		if (error)
			goto fail;

		if (!(file->f_flags & O_LARGEFILE) &&
		    i_size_read(inode) > MAX_NON_LFS) {
			error = -EOVERFLOW;
			goto fail_gunlock;
		}

		gfs2_glock_dq_uninit(&i_gh);
	}

	return 0;

fail_gunlock:
	gfs2_glock_dq_uninit(&i_gh);
fail:
	file->private_data = NULL;
	kfree(fp);
	return error;
}