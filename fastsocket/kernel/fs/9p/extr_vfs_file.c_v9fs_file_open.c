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
struct v9fs_session_info {scalar_t__ cache; } ;
struct TYPE_4__ {scalar_t__ version; } ;
struct p9_fid {TYPE_2__ qid; } ;
struct inode {scalar_t__ i_blocks; } ;
struct TYPE_3__ {int /*<<< orphan*/  dentry; } ;
struct file {int f_flags; int /*<<< orphan*/ * f_op; struct p9_fid* private_data; TYPE_1__ f_path; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct p9_fid*) ; 
 int O_APPEND ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*,...) ; 
 int P9_OTRUNC ; 
 int PTR_ERR (struct p9_fid*) ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  generic_file_llseek (struct file*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_client_clunk (struct p9_fid*) ; 
 int p9_client_open (struct p9_fid*,int) ; 
 int /*<<< orphan*/  v9fs_cache_inode_set_cookie (struct inode*,struct file*) ; 
 int /*<<< orphan*/  v9fs_cached_file_operations ; 
 int /*<<< orphan*/  v9fs_extended (struct v9fs_session_info*) ; 
 struct p9_fid* v9fs_fid_clone (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v9fs_file_operations ; 
 struct v9fs_session_info* v9fs_inode2v9ses (struct inode*) ; 
 int v9fs_uflags2omode (int,int /*<<< orphan*/ ) ; 

int v9fs_file_open(struct inode *inode, struct file *file)
{
	int err;
	struct v9fs_session_info *v9ses;
	struct p9_fid *fid;
	int omode;

	P9_DPRINTK(P9_DEBUG_VFS, "inode: %p file: %p \n", inode, file);
	v9ses = v9fs_inode2v9ses(inode);
	omode = v9fs_uflags2omode(file->f_flags, v9fs_extended(v9ses));
	fid = file->private_data;
	if (!fid) {
		fid = v9fs_fid_clone(file->f_path.dentry);
		if (IS_ERR(fid))
			return PTR_ERR(fid);

		err = p9_client_open(fid, omode);
		if (err < 0) {
			p9_client_clunk(fid);
			return err;
		}
		if (omode & P9_OTRUNC) {
			i_size_write(inode, 0);
			inode->i_blocks = 0;
		}
		if ((file->f_flags & O_APPEND) && (!v9fs_extended(v9ses)))
			generic_file_llseek(file, 0, SEEK_END);
	}

	file->private_data = fid;
	if ((fid->qid.version) && (v9ses->cache)) {
		P9_DPRINTK(P9_DEBUG_VFS, "cached");
		/* enable cached file options */
		if(file->f_op == &v9fs_file_operations)
			file->f_op = &v9fs_cached_file_operations;

#ifdef CONFIG_9P_FSCACHE
		v9fs_cache_inode_set_cookie(inode, file);
#endif
	}

	return 0;
}