#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tid_t ;
struct TYPE_5__ {struct inode* ip; } ;
struct tblock {TYPE_2__ u; int /*<<< orphan*/  xflag; } ;
struct inode {scalar_t__ i_nlink; int i_size; int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_ino; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; struct inode* d_inode; } ;
struct component_name {int dummy; } ;
typedef  int s64 ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_6__ {int /*<<< orphan*/  commit_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (scalar_t__) ; 
 int /*<<< orphan*/  COMMIT_DELETE ; 
 int /*<<< orphan*/  COMMIT_MUTEX_CHILD ; 
 int /*<<< orphan*/  COMMIT_MUTEX_PARENT ; 
 int /*<<< orphan*/  COMMIT_Nolink ; 
 int COMMIT_SYNC ; 
 int /*<<< orphan*/  COMMIT_Stale ; 
 int /*<<< orphan*/  CURRENT_TIME ; 
 int EIO ; 
 int /*<<< orphan*/  IWRITE_LOCK (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWRITE_UNLOCK (struct inode*) ; 
 TYPE_3__* JFS_IP (struct inode*) ; 
 int /*<<< orphan*/  JFS_REMOVE ; 
 int /*<<< orphan*/  RDWRLOCK_NORMAL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clear_cflag (int /*<<< orphan*/ ,struct inode*) ; 
 int commitZeroLink (int /*<<< orphan*/ ,struct inode*) ; 
 int dtDelete (int /*<<< orphan*/ ,struct inode*,struct component_name*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_UCSname (struct component_name*) ; 
 int get_UCSname (struct component_name*,struct dentry*) ; 
 int /*<<< orphan*/  inode_dec_link_count (struct inode*) ; 
 int /*<<< orphan*/  jfs_err (char*,int) ; 
 int /*<<< orphan*/  jfs_info (char*,...) ; 
 int /*<<< orphan*/  jfs_truncate_nolock (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_cflag (int /*<<< orphan*/ ,struct inode*) ; 
 scalar_t__ test_cflag (int /*<<< orphan*/ ,struct inode*) ; 
 struct tblock* tid_to_tblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txAbort (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  txBegin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int txCommit (int /*<<< orphan*/ ,int,struct inode**,int) ; 
 int /*<<< orphan*/  txEnd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfs_dq_init (struct inode*) ; 
 int xtTruncate_pmap (int /*<<< orphan*/ ,struct inode*,int) ; 

__attribute__((used)) static int jfs_unlink(struct inode *dip, struct dentry *dentry)
{
	int rc;
	tid_t tid;		/* transaction id */
	struct inode *ip = dentry->d_inode;
	ino_t ino;
	struct component_name dname;	/* object name */
	struct inode *iplist[2];
	struct tblock *tblk;
	s64 new_size = 0;
	int commit_flag;

	jfs_info("jfs_unlink: dip:0x%p name:%s", dip, dentry->d_name.name);

	/* Init inode for quota operations. */
	vfs_dq_init(ip);

	if ((rc = get_UCSname(&dname, dentry)))
		goto out;

	IWRITE_LOCK(ip, RDWRLOCK_NORMAL);

	tid = txBegin(dip->i_sb, 0);

	mutex_lock_nested(&JFS_IP(dip)->commit_mutex, COMMIT_MUTEX_PARENT);
	mutex_lock_nested(&JFS_IP(ip)->commit_mutex, COMMIT_MUTEX_CHILD);

	iplist[0] = dip;
	iplist[1] = ip;

	/*
	 * delete the entry of target file from parent directory
	 */
	ino = ip->i_ino;
	if ((rc = dtDelete(tid, dip, &dname, &ino, JFS_REMOVE))) {
		jfs_err("jfs_unlink: dtDelete returned %d", rc);
		if (rc == -EIO)
			txAbort(tid, 1);	/* Marks FS Dirty */
		txEnd(tid);
		mutex_unlock(&JFS_IP(ip)->commit_mutex);
		mutex_unlock(&JFS_IP(dip)->commit_mutex);
		IWRITE_UNLOCK(ip);
		goto out1;
	}

	ASSERT(ip->i_nlink);

	ip->i_ctime = dip->i_ctime = dip->i_mtime = CURRENT_TIME;
	mark_inode_dirty(dip);

	/* update target's inode */
	inode_dec_link_count(ip);

	/*
	 *	commit zero link count object
	 */
	if (ip->i_nlink == 0) {
		assert(!test_cflag(COMMIT_Nolink, ip));
		/* free block resources */
		if ((new_size = commitZeroLink(tid, ip)) < 0) {
			txAbort(tid, 1);	/* Marks FS Dirty */
			txEnd(tid);
			mutex_unlock(&JFS_IP(ip)->commit_mutex);
			mutex_unlock(&JFS_IP(dip)->commit_mutex);
			IWRITE_UNLOCK(ip);
			rc = new_size;
			goto out1;
		}
		tblk = tid_to_tblock(tid);
		tblk->xflag |= COMMIT_DELETE;
		tblk->u.ip = ip;
	}

	/*
	 * Incomplete truncate of file data can
	 * result in timing problems unless we synchronously commit the
	 * transaction.
	 */
	if (new_size)
		commit_flag = COMMIT_SYNC;
	else
		commit_flag = 0;

	/*
	 * If xtTruncate was incomplete, commit synchronously to avoid
	 * timing complications
	 */
	rc = txCommit(tid, 2, &iplist[0], commit_flag);

	txEnd(tid);

	mutex_unlock(&JFS_IP(ip)->commit_mutex);
	mutex_unlock(&JFS_IP(dip)->commit_mutex);

	while (new_size && (rc == 0)) {
		tid = txBegin(dip->i_sb, 0);
		mutex_lock(&JFS_IP(ip)->commit_mutex);
		new_size = xtTruncate_pmap(tid, ip, new_size);
		if (new_size < 0) {
			txAbort(tid, 1);	/* Marks FS Dirty */
			rc = new_size;
		} else
			rc = txCommit(tid, 2, &iplist[0], COMMIT_SYNC);
		txEnd(tid);
		mutex_unlock(&JFS_IP(ip)->commit_mutex);
	}

	if (ip->i_nlink == 0)
		set_cflag(COMMIT_Nolink, ip);

	IWRITE_UNLOCK(ip);

	/*
	 * Truncating the directory index table is not guaranteed.  It
	 * may need to be done iteratively
	 */
	if (test_cflag(COMMIT_Stale, dip)) {
		if (dip->i_size > 1)
			jfs_truncate_nolock(dip, 0);

		clear_cflag(COMMIT_Stale, dip);
	}

      out1:
	free_UCSname(&dname);
      out:
	jfs_info("jfs_unlink: rc:%d", rc);
	return rc;
}