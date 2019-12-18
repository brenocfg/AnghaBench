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
typedef  int /*<<< orphan*/  tid_t ;
struct TYPE_4__ {int /*<<< orphan*/  ixpxd; } ;
struct tblock {TYPE_2__ u; int /*<<< orphan*/  ino; int /*<<< orphan*/  xflag; } ;
struct jfs_inode_info {int /*<<< orphan*/  commit_mutex; int /*<<< orphan*/  dev; int /*<<< orphan*/  ixpxd; } ;
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_mode; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct TYPE_3__ {int name; } ;
struct dentry {TYPE_1__ d_name; } ;
struct component_name {int dummy; } ;
struct btstack {int dummy; } ;
typedef  int /*<<< orphan*/  ino_t ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_CREATE ; 
 int /*<<< orphan*/  COMMIT_MUTEX_CHILD ; 
 int /*<<< orphan*/  COMMIT_MUTEX_PARENT ; 
 int /*<<< orphan*/  CURRENT_TIME ; 
 int EINVAL ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  JFS_CREATE ; 
 struct jfs_inode_info* JFS_IP (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int dtInsert (int /*<<< orphan*/ ,struct inode*,struct component_name*,int /*<<< orphan*/ *,struct btstack*) ; 
 int dtSearch (struct inode*,struct component_name*,int /*<<< orphan*/ *,struct btstack*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_UCSname (struct component_name*) ; 
 int /*<<< orphan*/  free_ea_wmap (struct inode*) ; 
 int get_UCSname (struct component_name*,struct dentry*) ; 
 struct inode* ialloc (struct inode*,int) ; 
 int /*<<< orphan*/  init_special_inode (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  jfs_file_inode_operations ; 
 int /*<<< orphan*/  jfs_info (char*,int) ; 
 int jfs_init_acl (int /*<<< orphan*/ ,struct inode*,struct inode*) ; 
 int jfs_init_security (int /*<<< orphan*/ ,struct inode*,struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  new_encode_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  new_valid_dev (int /*<<< orphan*/ ) ; 
 struct tblock* tid_to_tblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txAbort (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txBegin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int txCommit (int /*<<< orphan*/ ,int,struct inode**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txEnd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

__attribute__((used)) static int jfs_mknod(struct inode *dir, struct dentry *dentry,
		int mode, dev_t rdev)
{
	struct jfs_inode_info *jfs_ip;
	struct btstack btstack;
	struct component_name dname;
	ino_t ino;
	struct inode *ip;
	struct inode *iplist[2];
	int rc;
	tid_t tid;
	struct tblock *tblk;

	if (!new_valid_dev(rdev))
		return -EINVAL;

	jfs_info("jfs_mknod: %s", dentry->d_name.name);

	if ((rc = get_UCSname(&dname, dentry)))
		goto out;

	ip = ialloc(dir, mode);
	if (IS_ERR(ip)) {
		rc = PTR_ERR(ip);
		goto out1;
	}
	jfs_ip = JFS_IP(ip);

	tid = txBegin(dir->i_sb, 0);

	mutex_lock_nested(&JFS_IP(dir)->commit_mutex, COMMIT_MUTEX_PARENT);
	mutex_lock_nested(&JFS_IP(ip)->commit_mutex, COMMIT_MUTEX_CHILD);

	rc = jfs_init_acl(tid, ip, dir);
	if (rc)
		goto out3;

	rc = jfs_init_security(tid, ip, dir);
	if (rc) {
		txAbort(tid, 0);
		goto out3;
	}

	if ((rc = dtSearch(dir, &dname, &ino, &btstack, JFS_CREATE))) {
		txAbort(tid, 0);
		goto out3;
	}

	tblk = tid_to_tblock(tid);
	tblk->xflag |= COMMIT_CREATE;
	tblk->ino = ip->i_ino;
	tblk->u.ixpxd = JFS_IP(ip)->ixpxd;

	ino = ip->i_ino;
	if ((rc = dtInsert(tid, dir, &dname, &ino, &btstack))) {
		txAbort(tid, 0);
		goto out3;
	}

	ip->i_op = &jfs_file_inode_operations;
	jfs_ip->dev = new_encode_dev(rdev);
	init_special_inode(ip, ip->i_mode, rdev);

	mark_inode_dirty(ip);

	dir->i_ctime = dir->i_mtime = CURRENT_TIME;

	mark_inode_dirty(dir);

	iplist[0] = dir;
	iplist[1] = ip;
	rc = txCommit(tid, 2, iplist, 0);

      out3:
	txEnd(tid);
	mutex_unlock(&JFS_IP(ip)->commit_mutex);
	mutex_unlock(&JFS_IP(dir)->commit_mutex);
	if (rc) {
		free_ea_wmap(ip);
		ip->i_nlink = 0;
		unlock_new_inode(ip);
		iput(ip);
	} else {
		d_instantiate(dentry, ip);
		unlock_new_inode(ip);
	}

      out1:
	free_UCSname(&dname);

      out:
	jfs_info("jfs_mknod: returning %d", rc);
	return rc;
}