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
typedef  int /*<<< orphan*/  tid_t ;
struct TYPE_6__ {struct inode* ip; } ;
struct tblock {TYPE_2__ u; int /*<<< orphan*/  xflag; } ;
struct inode {int i_size; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; struct inode* d_inode; } ;
struct component_name {int dummy; } ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_7__ {int flag; } ;
struct TYPE_8__ {int /*<<< orphan*/  commit_mutex; TYPE_3__ acl; TYPE_3__ ea; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_DELETE ; 
 int /*<<< orphan*/  COMMIT_MUTEX_CHILD ; 
 int /*<<< orphan*/  COMMIT_MUTEX_PARENT ; 
 int /*<<< orphan*/  COMMIT_Stale ; 
 int /*<<< orphan*/  CURRENT_TIME ; 
 int DXD_EXTENT ; 
 int EIO ; 
 int ENOTEMPTY ; 
 TYPE_4__* JFS_IP (struct inode*) ; 
 int /*<<< orphan*/  JFS_REMOVE ; 
 int /*<<< orphan*/  clear_cflag (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int dtDelete (int /*<<< orphan*/ ,struct inode*,struct component_name*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtEmpty (struct inode*) ; 
 int /*<<< orphan*/  free_UCSname (struct component_name*) ; 
 int get_UCSname (struct component_name*,struct dentry*) ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 int /*<<< orphan*/  jfs_err (char*,int) ; 
 int /*<<< orphan*/  jfs_info (char*,...) ; 
 int /*<<< orphan*/  jfs_truncate_nolock (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_cflag (int /*<<< orphan*/ ,struct inode*) ; 
 struct tblock* tid_to_tblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txAbort (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  txBegin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int txCommit (int /*<<< orphan*/ ,int,struct inode**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txEA (int /*<<< orphan*/ ,struct inode*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txEnd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_dq_init (struct inode*) ; 

__attribute__((used)) static int jfs_rmdir(struct inode *dip, struct dentry *dentry)
{
	int rc;
	tid_t tid;		/* transaction id */
	struct inode *ip = dentry->d_inode;
	ino_t ino;
	struct component_name dname;
	struct inode *iplist[2];
	struct tblock *tblk;

	jfs_info("jfs_rmdir: dip:0x%p name:%s", dip, dentry->d_name.name);

	/* Init inode for quota operations. */
	vfs_dq_init(ip);

	/* directory must be empty to be removed */
	if (!dtEmpty(ip)) {
		rc = -ENOTEMPTY;
		goto out;
	}

	if ((rc = get_UCSname(&dname, dentry))) {
		goto out;
	}

	tid = txBegin(dip->i_sb, 0);

	mutex_lock_nested(&JFS_IP(dip)->commit_mutex, COMMIT_MUTEX_PARENT);
	mutex_lock_nested(&JFS_IP(ip)->commit_mutex, COMMIT_MUTEX_CHILD);

	iplist[0] = dip;
	iplist[1] = ip;

	tblk = tid_to_tblock(tid);
	tblk->xflag |= COMMIT_DELETE;
	tblk->u.ip = ip;

	/*
	 * delete the entry of target directory from parent directory
	 */
	ino = ip->i_ino;
	if ((rc = dtDelete(tid, dip, &dname, &ino, JFS_REMOVE))) {
		jfs_err("jfs_rmdir: dtDelete returned %d", rc);
		if (rc == -EIO)
			txAbort(tid, 1);
		txEnd(tid);
		mutex_unlock(&JFS_IP(ip)->commit_mutex);
		mutex_unlock(&JFS_IP(dip)->commit_mutex);

		goto out2;
	}

	/* update parent directory's link count corresponding
	 * to ".." entry of the target directory deleted
	 */
	dip->i_ctime = dip->i_mtime = CURRENT_TIME;
	inode_dec_link_count(dip);

	/*
	 * OS/2 could have created EA and/or ACL
	 */
	/* free EA from both persistent and working map */
	if (JFS_IP(ip)->ea.flag & DXD_EXTENT) {
		/* free EA pages */
		txEA(tid, ip, &JFS_IP(ip)->ea, NULL);
	}
	JFS_IP(ip)->ea.flag = 0;

	/* free ACL from both persistent and working map */
	if (JFS_IP(ip)->acl.flag & DXD_EXTENT) {
		/* free ACL pages */
		txEA(tid, ip, &JFS_IP(ip)->acl, NULL);
	}
	JFS_IP(ip)->acl.flag = 0;

	/* mark the target directory as deleted */
	clear_nlink(ip);
	mark_inode_dirty(ip);

	rc = txCommit(tid, 2, &iplist[0], 0);

	txEnd(tid);

	mutex_unlock(&JFS_IP(ip)->commit_mutex);
	mutex_unlock(&JFS_IP(dip)->commit_mutex);

	/*
	 * Truncating the directory index table is not guaranteed.  It
	 * may need to be done iteratively
	 */
	if (test_cflag(COMMIT_Stale, dip)) {
		if (dip->i_size > 1)
			jfs_truncate_nolock(dip, 0);

		clear_cflag(COMMIT_Stale, dip);
	}

      out2:
	free_UCSname(&dname);

      out:
	jfs_info("jfs_rmdir: rc:%d", rc);
	return rc;
}