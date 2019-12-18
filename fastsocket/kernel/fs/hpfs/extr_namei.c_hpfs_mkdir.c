#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct quad_buffer_head {int dummy; } ;
struct TYPE_12__ {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_11__ {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_10__ {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct inode {int i_mode; int i_blocks; int i_size; int i_nlink; scalar_t__ i_uid; scalar_t__ i_gid; int /*<<< orphan*/  i_sb; void* i_ino; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; TYPE_4__ i_atime; TYPE_3__ i_mtime; TYPE_2__ i_ctime; } ;
struct hpfs_dirent {int directory; int read_only; int hidden; int first; void* fnode; void* read_date; void* write_date; void* creation_date; } ;
struct TYPE_15__ {TYPE_6__* external; } ;
struct TYPE_13__ {int n_free_nodes; int n_used_nodes; int first_free; } ;
struct fnode {unsigned int len; int dirflag; TYPE_7__ u; TYPE_5__ btree; void* up; int /*<<< orphan*/  name; } ;
struct dnode {int root_dnode; void* up; } ;
struct TYPE_9__ {char* name; unsigned int len; } ;
struct dentry {TYPE_1__ d_name; } ;
struct buffer_head {int dummy; } ;
typedef  void* fnode_secno ;
typedef  void* dnode_secno ;
struct TYPE_16__ {int /*<<< orphan*/  i_mutex; scalar_t__ i_ea_size; void* i_dno; void* i_parent_dir; } ;
struct TYPE_14__ {int file_secno; void* disk_secno; } ;

/* Variables and functions */
 int EEXIST ; 
 int EINVAL ; 
 int ENOENT ; 
 int ENOSPC ; 
 int S_IFDIR ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ current_fsgid () ; 
 scalar_t__ current_fsuid () ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  get_seconds () ; 
 void* gmt_to_local (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hpfs_dirent* hpfs_add_de (int /*<<< orphan*/ ,struct dnode*,char*,int,int /*<<< orphan*/ ) ; 
 int hpfs_add_dirent (struct inode*,char*,unsigned int,struct hpfs_dirent*,int /*<<< orphan*/ ) ; 
 struct dnode* hpfs_alloc_dnode (int /*<<< orphan*/ ,void*,void**,struct quad_buffer_head*,int) ; 
 struct fnode* hpfs_alloc_fnode (int /*<<< orphan*/ ,void*,void**,struct buffer_head**) ; 
 int /*<<< orphan*/  hpfs_brelse4 (struct quad_buffer_head*) ; 
 int hpfs_chk_name (char*,unsigned int*) ; 
 int /*<<< orphan*/  hpfs_dir_iops ; 
 int /*<<< orphan*/  hpfs_dir_ops ; 
 int /*<<< orphan*/  hpfs_free_dnode (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  hpfs_free_sectors (int /*<<< orphan*/ ,void*,int) ; 
 TYPE_8__* hpfs_i (struct inode*) ; 
 int /*<<< orphan*/  hpfs_init_inode (struct inode*) ; 
 int /*<<< orphan*/  hpfs_mark_4buffers_dirty (struct quad_buffer_head*) ; 
 int /*<<< orphan*/  hpfs_write_inode_nolock (struct inode*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  local_to_gmt (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  lock_kernel () ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  memset (struct hpfs_dirent*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct inode* new_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_kernel () ; 

__attribute__((used)) static int hpfs_mkdir(struct inode *dir, struct dentry *dentry, int mode)
{
	const char *name = dentry->d_name.name;
	unsigned len = dentry->d_name.len;
	struct quad_buffer_head qbh0;
	struct buffer_head *bh;
	struct hpfs_dirent *de;
	struct fnode *fnode;
	struct dnode *dnode;
	struct inode *result;
	fnode_secno fno;
	dnode_secno dno;
	int r;
	struct hpfs_dirent dee;
	int err;
	if ((err = hpfs_chk_name((char *)name, &len))) return err==-ENOENT ? -EINVAL : err;
	lock_kernel();
	err = -ENOSPC;
	fnode = hpfs_alloc_fnode(dir->i_sb, hpfs_i(dir)->i_dno, &fno, &bh);
	if (!fnode)
		goto bail;
	dnode = hpfs_alloc_dnode(dir->i_sb, fno, &dno, &qbh0, 1);
	if (!dnode)
		goto bail1;
	memset(&dee, 0, sizeof dee);
	dee.directory = 1;
	if (!(mode & 0222)) dee.read_only = 1;
	/*dee.archive = 0;*/
	dee.hidden = name[0] == '.';
	dee.fnode = fno;
	dee.creation_date = dee.write_date = dee.read_date = gmt_to_local(dir->i_sb, get_seconds());
	result = new_inode(dir->i_sb);
	if (!result)
		goto bail2;
	hpfs_init_inode(result);
	result->i_ino = fno;
	hpfs_i(result)->i_parent_dir = dir->i_ino;
	hpfs_i(result)->i_dno = dno;
	result->i_ctime.tv_sec = result->i_mtime.tv_sec = result->i_atime.tv_sec = local_to_gmt(dir->i_sb, dee.creation_date);
	result->i_ctime.tv_nsec = 0; 
	result->i_mtime.tv_nsec = 0; 
	result->i_atime.tv_nsec = 0; 
	hpfs_i(result)->i_ea_size = 0;
	result->i_mode |= S_IFDIR;
	result->i_op = &hpfs_dir_iops;
	result->i_fop = &hpfs_dir_ops;
	result->i_blocks = 4;
	result->i_size = 2048;
	result->i_nlink = 2;
	if (dee.read_only)
		result->i_mode &= ~0222;

	mutex_lock(&hpfs_i(dir)->i_mutex);
	r = hpfs_add_dirent(dir, (char *)name, len, &dee, 0);
	if (r == 1)
		goto bail3;
	if (r == -1) {
		err = -EEXIST;
		goto bail3;
	}
	fnode->len = len;
	memcpy(fnode->name, name, len > 15 ? 15 : len);
	fnode->up = dir->i_ino;
	fnode->dirflag = 1;
	fnode->btree.n_free_nodes = 7;
	fnode->btree.n_used_nodes = 1;
	fnode->btree.first_free = 0x14;
	fnode->u.external[0].disk_secno = dno;
	fnode->u.external[0].file_secno = -1;
	dnode->root_dnode = 1;
	dnode->up = fno;
	de = hpfs_add_de(dir->i_sb, dnode, "\001\001", 2, 0);
	de->creation_date = de->write_date = de->read_date = gmt_to_local(dir->i_sb, get_seconds());
	if (!(mode & 0222)) de->read_only = 1;
	de->first = de->directory = 1;
	/*de->hidden = de->system = 0;*/
	de->fnode = fno;
	mark_buffer_dirty(bh);
	brelse(bh);
	hpfs_mark_4buffers_dirty(&qbh0);
	hpfs_brelse4(&qbh0);
	inc_nlink(dir);
	insert_inode_hash(result);

	if (result->i_uid != current_fsuid() ||
	    result->i_gid != current_fsgid() ||
	    result->i_mode != (mode | S_IFDIR)) {
		result->i_uid = current_fsuid();
		result->i_gid = current_fsgid();
		result->i_mode = mode | S_IFDIR;
		hpfs_write_inode_nolock(result);
	}
	d_instantiate(dentry, result);
	mutex_unlock(&hpfs_i(dir)->i_mutex);
	unlock_kernel();
	return 0;
bail3:
	mutex_unlock(&hpfs_i(dir)->i_mutex);
	iput(result);
bail2:
	hpfs_brelse4(&qbh0);
	hpfs_free_dnode(dir->i_sb, dno);
bail1:
	brelse(bh);
	hpfs_free_sectors(dir->i_sb, fno, 1);
bail:
	unlock_kernel();
	return err;
}