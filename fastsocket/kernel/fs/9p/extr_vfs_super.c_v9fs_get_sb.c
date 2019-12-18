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
struct vfsmount {int dummy; } ;
struct v9fs_session_info {int /*<<< orphan*/  qid; struct dentry* s_root; } ;
struct super_block {int /*<<< orphan*/  qid; struct dentry* s_root; } ;
struct p9_wstat {int /*<<< orphan*/  qid; struct dentry* s_root; } ;
struct p9_fid {int /*<<< orphan*/  qid; struct dentry* s_root; } ;
struct inode {int /*<<< orphan*/  qid; struct dentry* s_root; } ;
struct file_system_type {int dummy; } ;
struct dentry {TYPE_1__* d_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_ino; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct v9fs_session_info*) ; 
 int /*<<< orphan*/  P9_DEBUG_VFS ; 
 int /*<<< orphan*/  P9_DPRINTK (int /*<<< orphan*/ ,char*) ; 
 int PTR_ERR (struct v9fs_session_info*) ; 
 int S_IFDIR ; 
 int S_IRWXUGO ; 
 int S_ISVTX ; 
 struct dentry* d_alloc_root (struct v9fs_session_info*) ; 
 int /*<<< orphan*/  deactivate_locked_super (struct v9fs_session_info*) ; 
 int /*<<< orphan*/  iput (struct v9fs_session_info*) ; 
 int /*<<< orphan*/  kfree (struct v9fs_session_info*) ; 
 struct v9fs_session_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p9_client_clunk (struct v9fs_session_info*) ; 
 struct v9fs_session_info* p9_client_stat (struct v9fs_session_info*) ; 
 int /*<<< orphan*/  p9stat_free (struct v9fs_session_info*) ; 
 struct v9fs_session_info* sget (struct file_system_type*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct v9fs_session_info*) ; 
 int /*<<< orphan*/  simple_set_mnt (struct vfsmount*,struct v9fs_session_info*) ; 
 int /*<<< orphan*/  v9fs_fid_add (struct dentry*,struct v9fs_session_info*) ; 
 int /*<<< orphan*/  v9fs_fill_super (struct v9fs_session_info*,struct v9fs_session_info*,int,void*) ; 
 struct v9fs_session_info* v9fs_get_inode (struct v9fs_session_info*,int) ; 
 int /*<<< orphan*/  v9fs_qid2ino (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v9fs_session_close (struct v9fs_session_info*) ; 
 struct v9fs_session_info* v9fs_session_init (struct v9fs_session_info*,char const*,void*) ; 
 int /*<<< orphan*/  v9fs_set_super ; 
 int /*<<< orphan*/  v9fs_stat2inode (struct v9fs_session_info*,TYPE_1__*,struct v9fs_session_info*) ; 

__attribute__((used)) static int v9fs_get_sb(struct file_system_type *fs_type, int flags,
		       const char *dev_name, void *data,
		       struct vfsmount *mnt)
{
	struct super_block *sb = NULL;
	struct inode *inode = NULL;
	struct dentry *root = NULL;
	struct v9fs_session_info *v9ses = NULL;
	struct p9_wstat *st = NULL;
	int mode = S_IRWXUGO | S_ISVTX;
	struct p9_fid *fid;
	int retval = 0;

	P9_DPRINTK(P9_DEBUG_VFS, " \n");

	v9ses = kzalloc(sizeof(struct v9fs_session_info), GFP_KERNEL);
	if (!v9ses)
		return -ENOMEM;

	fid = v9fs_session_init(v9ses, dev_name, data);
	if (IS_ERR(fid)) {
		retval = PTR_ERR(fid);
		goto close_session;
	}

	st = p9_client_stat(fid);
	if (IS_ERR(st)) {
		retval = PTR_ERR(st);
		goto clunk_fid;
	}

	sb = sget(fs_type, NULL, v9fs_set_super, v9ses);
	if (IS_ERR(sb)) {
		retval = PTR_ERR(sb);
		goto free_stat;
	}
	v9fs_fill_super(sb, v9ses, flags, data);

	inode = v9fs_get_inode(sb, S_IFDIR | mode);
	if (IS_ERR(inode)) {
		retval = PTR_ERR(inode);
		goto release_sb;
	}

	root = d_alloc_root(inode);
	if (!root) {
		iput(inode);
		retval = -ENOMEM;
		goto release_sb;
	}

	sb->s_root = root;
	root->d_inode->i_ino = v9fs_qid2ino(&st->qid);

	v9fs_stat2inode(st, root->d_inode, sb);

	v9fs_fid_add(root, fid);
	p9stat_free(st);
	kfree(st);

P9_DPRINTK(P9_DEBUG_VFS, " simple set mount, return 0\n");
	simple_set_mnt(mnt, sb);
	return 0;

free_stat:
	p9stat_free(st);
	kfree(st);

clunk_fid:
	p9_client_clunk(fid);

close_session:
	v9fs_session_close(v9ses);
	kfree(v9ses);
	return retval;

release_sb:
	p9stat_free(st);
	kfree(st);
	deactivate_locked_super(sb);
	return retval;
}