#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tid_t ;
struct tlock {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {struct inode* ip; } ;
struct tblock {TYPE_1__ u; int /*<<< orphan*/  xflag; } ;
struct metapage {int dummy; } ;
struct lv {int length; scalar_t__ offset; } ;
struct inode {scalar_t__ i_ino; scalar_t__ i_nlink; int i_size; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_sb; void* i_mtime; void* i_ctime; } ;
struct dt_lock {scalar_t__ index; struct lv* lv; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct dentry {struct inode* d_inode; TYPE_4__ d_name; } ;
struct component_name {int dummy; } ;
struct btstack {int dummy; } ;
typedef  int s64 ;
typedef  scalar_t__ ino_t ;
struct TYPE_7__ {int /*<<< orphan*/  idotdot; } ;
struct TYPE_8__ {TYPE_2__ header; } ;
struct TYPE_10__ {int /*<<< orphan*/  commit_mutex; int /*<<< orphan*/  bxflag; TYPE_3__ i_dtroot; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  COMMIT_DELETE ; 
 int /*<<< orphan*/  COMMIT_MUTEX_CHILD ; 
 int /*<<< orphan*/  COMMIT_MUTEX_PARENT ; 
 int /*<<< orphan*/  COMMIT_MUTEX_SECOND_PARENT ; 
 int /*<<< orphan*/  COMMIT_MUTEX_VICTIM ; 
 int /*<<< orphan*/  COMMIT_Nolink ; 
 int COMMIT_SYNC ; 
 int /*<<< orphan*/  COMMIT_Stale ; 
 void* CURRENT_TIME ; 
 int EIO ; 
 int EMLINK ; 
 int ENOENT ; 
 int ENOTEMPTY ; 
 int ESTALE ; 
 int /*<<< orphan*/  IWRITE_LOCK (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IWRITE_UNLOCK (struct inode*) ; 
 int /*<<< orphan*/  JFS_CREATE ; 
 TYPE_5__* JFS_IP (struct inode*) ; 
 scalar_t__ JFS_LINK_MAX ; 
 int /*<<< orphan*/  JFS_LOOKUP ; 
 int /*<<< orphan*/  JFS_REMOVE ; 
 int /*<<< orphan*/  JFS_RENAME ; 
 int /*<<< orphan*/  RDWRLOCK_NORMAL ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clear_cflag (int /*<<< orphan*/ ,struct inode*) ; 
 int commitZeroLink (int /*<<< orphan*/ ,struct inode*) ; 
 int /*<<< orphan*/  cpu_to_le32 (scalar_t__) ; 
 void* current_fs_time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drop_nlink (struct inode*) ; 
 int dtDelete (int /*<<< orphan*/ ,struct inode*,struct component_name*,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtEmpty (struct inode*) ; 
 int dtInsert (int /*<<< orphan*/ ,struct inode*,struct component_name*,scalar_t__*,struct btstack*) ; 
 int dtModify (int /*<<< orphan*/ ,struct inode*,struct component_name*,scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int dtSearch (struct inode*,struct component_name*,scalar_t__*,struct btstack*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_UCSname (struct component_name*) ; 
 int get_UCSname (struct component_name*,struct dentry*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  jfs_err (char*,...) ; 
 int /*<<< orphan*/  jfs_error (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  jfs_info (char*,int,...) ; 
 int /*<<< orphan*/  jfs_truncate_nolock (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_cflag (int /*<<< orphan*/ ,struct inode*) ; 
 scalar_t__ test_cflag (int /*<<< orphan*/ ,struct inode*) ; 
 struct tblock* tid_to_tblock (int /*<<< orphan*/ ) ; 
 int tlckBTROOT ; 
 int tlckDTREE ; 
 int tlckRELINK ; 
 int /*<<< orphan*/  txAbort (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  txBegin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int txCommit (int /*<<< orphan*/ ,int,struct inode**,int) ; 
 int /*<<< orphan*/  txEnd (int /*<<< orphan*/ ) ; 
 struct tlock* txLock (int /*<<< orphan*/ ,struct inode*,struct metapage*,int) ; 
 int /*<<< orphan*/  vfs_dq_init (struct inode*) ; 
 int xtTruncate_pmap (int /*<<< orphan*/ ,struct inode*,int) ; 

__attribute__((used)) static int jfs_rename(struct inode *old_dir, struct dentry *old_dentry,
	       struct inode *new_dir, struct dentry *new_dentry)
{
	struct btstack btstack;
	ino_t ino;
	struct component_name new_dname;
	struct inode *new_ip;
	struct component_name old_dname;
	struct inode *old_ip;
	int rc;
	tid_t tid;
	struct tlock *tlck;
	struct dt_lock *dtlck;
	struct lv *lv;
	int ipcount;
	struct inode *iplist[4];
	struct tblock *tblk;
	s64 new_size = 0;
	int commit_flag;


	jfs_info("jfs_rename: %s %s", old_dentry->d_name.name,
		 new_dentry->d_name.name);

	old_ip = old_dentry->d_inode;
	new_ip = new_dentry->d_inode;

	if ((rc = get_UCSname(&old_dname, old_dentry)))
		goto out1;

	if ((rc = get_UCSname(&new_dname, new_dentry)))
		goto out2;

	/*
	 * Make sure source inode number is what we think it is
	 */
	rc = dtSearch(old_dir, &old_dname, &ino, &btstack, JFS_LOOKUP);
	if (rc || (ino != old_ip->i_ino)) {
		rc = -ENOENT;
		goto out3;
	}

	/*
	 * Make sure dest inode number (if any) is what we think it is
	 */
	rc = dtSearch(new_dir, &new_dname, &ino, &btstack, JFS_LOOKUP);
	if (!rc) {
		if ((!new_ip) || (ino != new_ip->i_ino)) {
			rc = -ESTALE;
			goto out3;
		}
	} else if (rc != -ENOENT)
		goto out3;
	else if (new_ip) {
		/* no entry exists, but one was expected */
		rc = -ESTALE;
		goto out3;
	}

	if (S_ISDIR(old_ip->i_mode)) {
		if (new_ip) {
			if (!dtEmpty(new_ip)) {
				rc = -ENOTEMPTY;
				goto out3;
			}
		} else if ((new_dir != old_dir) &&
			   (new_dir->i_nlink == JFS_LINK_MAX)) {
			rc = -EMLINK;
			goto out3;
		}
	} else if (new_ip) {
		IWRITE_LOCK(new_ip, RDWRLOCK_NORMAL);
		/* Init inode for quota operations. */
		vfs_dq_init(new_ip);
	}

	/*
	 * The real work starts here
	 */
	tid = txBegin(new_dir->i_sb, 0);

	/*
	 * How do we know the locking is safe from deadlocks?
	 * The vfs does the hard part for us.  Any time we are taking nested
	 * commit_mutexes, the vfs already has i_mutex held on the parent.
	 * Here, the vfs has already taken i_mutex on both old_dir and new_dir.
	 */
	mutex_lock_nested(&JFS_IP(new_dir)->commit_mutex, COMMIT_MUTEX_PARENT);
	mutex_lock_nested(&JFS_IP(old_ip)->commit_mutex, COMMIT_MUTEX_CHILD);
	if (old_dir != new_dir)
		mutex_lock_nested(&JFS_IP(old_dir)->commit_mutex,
				  COMMIT_MUTEX_SECOND_PARENT);

	if (new_ip) {
		mutex_lock_nested(&JFS_IP(new_ip)->commit_mutex,
				  COMMIT_MUTEX_VICTIM);
		/*
		 * Change existing directory entry to new inode number
		 */
		ino = new_ip->i_ino;
		rc = dtModify(tid, new_dir, &new_dname, &ino,
			      old_ip->i_ino, JFS_RENAME);
		if (rc)
			goto out4;
		drop_nlink(new_ip);
		if (S_ISDIR(new_ip->i_mode)) {
			drop_nlink(new_ip);
			if (new_ip->i_nlink) {
				mutex_unlock(&JFS_IP(new_ip)->commit_mutex);
				if (old_dir != new_dir)
					mutex_unlock(&JFS_IP(old_dir)->commit_mutex);
				mutex_unlock(&JFS_IP(old_ip)->commit_mutex);
				mutex_unlock(&JFS_IP(new_dir)->commit_mutex);
				if (!S_ISDIR(old_ip->i_mode) && new_ip)
					IWRITE_UNLOCK(new_ip);
				jfs_error(new_ip->i_sb,
					  "jfs_rename: new_ip->i_nlink != 0");
				return -EIO;
			}
			tblk = tid_to_tblock(tid);
			tblk->xflag |= COMMIT_DELETE;
			tblk->u.ip = new_ip;
		} else if (new_ip->i_nlink == 0) {
			assert(!test_cflag(COMMIT_Nolink, new_ip));
			/* free block resources */
			if ((new_size = commitZeroLink(tid, new_ip)) < 0) {
				txAbort(tid, 1);	/* Marks FS Dirty */
				rc = new_size;
				goto out4;
			}
			tblk = tid_to_tblock(tid);
			tblk->xflag |= COMMIT_DELETE;
			tblk->u.ip = new_ip;
		} else {
			new_ip->i_ctime = CURRENT_TIME;
			mark_inode_dirty(new_ip);
		}
	} else {
		/*
		 * Add new directory entry
		 */
		rc = dtSearch(new_dir, &new_dname, &ino, &btstack,
			      JFS_CREATE);
		if (rc) {
			jfs_err("jfs_rename didn't expect dtSearch to fail "
				"w/rc = %d", rc);
			goto out4;
		}

		ino = old_ip->i_ino;
		rc = dtInsert(tid, new_dir, &new_dname, &ino, &btstack);
		if (rc) {
			if (rc == -EIO)
				jfs_err("jfs_rename: dtInsert returned -EIO");
			goto out4;
		}
		if (S_ISDIR(old_ip->i_mode))
			inc_nlink(new_dir);
	}
	/*
	 * Remove old directory entry
	 */

	ino = old_ip->i_ino;
	rc = dtDelete(tid, old_dir, &old_dname, &ino, JFS_REMOVE);
	if (rc) {
		jfs_err("jfs_rename did not expect dtDelete to return rc = %d",
			rc);
		txAbort(tid, 1);	/* Marks Filesystem dirty */
		goto out4;
	}
	if (S_ISDIR(old_ip->i_mode)) {
		drop_nlink(old_dir);
		if (old_dir != new_dir) {
			/*
			 * Change inode number of parent for moved directory
			 */

			JFS_IP(old_ip)->i_dtroot.header.idotdot =
				cpu_to_le32(new_dir->i_ino);

			/* Linelock header of dtree */
			tlck = txLock(tid, old_ip,
				    (struct metapage *) &JFS_IP(old_ip)->bxflag,
				      tlckDTREE | tlckBTROOT | tlckRELINK);
			dtlck = (struct dt_lock *) & tlck->lock;
			ASSERT(dtlck->index == 0);
			lv = & dtlck->lv[0];
			lv->offset = 0;
			lv->length = 1;
			dtlck->index++;
		}
	}

	/*
	 * Update ctime on changed/moved inodes & mark dirty
	 */
	old_ip->i_ctime = CURRENT_TIME;
	mark_inode_dirty(old_ip);

	new_dir->i_ctime = new_dir->i_mtime = current_fs_time(new_dir->i_sb);
	mark_inode_dirty(new_dir);

	/* Build list of inodes modified by this transaction */
	ipcount = 0;
	iplist[ipcount++] = old_ip;
	if (new_ip)
		iplist[ipcount++] = new_ip;
	iplist[ipcount++] = old_dir;

	if (old_dir != new_dir) {
		iplist[ipcount++] = new_dir;
		old_dir->i_ctime = old_dir->i_mtime = CURRENT_TIME;
		mark_inode_dirty(old_dir);
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

	rc = txCommit(tid, ipcount, iplist, commit_flag);

      out4:
	txEnd(tid);
	if (new_ip)
		mutex_unlock(&JFS_IP(new_ip)->commit_mutex);
	if (old_dir != new_dir)
		mutex_unlock(&JFS_IP(old_dir)->commit_mutex);
	mutex_unlock(&JFS_IP(old_ip)->commit_mutex);
	mutex_unlock(&JFS_IP(new_dir)->commit_mutex);

	while (new_size && (rc == 0)) {
		tid = txBegin(new_ip->i_sb, 0);
		mutex_lock(&JFS_IP(new_ip)->commit_mutex);
		new_size = xtTruncate_pmap(tid, new_ip, new_size);
		if (new_size < 0) {
			txAbort(tid, 1);
			rc = new_size;
		} else
			rc = txCommit(tid, 1, &new_ip, COMMIT_SYNC);
		txEnd(tid);
		mutex_unlock(&JFS_IP(new_ip)->commit_mutex);
	}
	if (new_ip && (new_ip->i_nlink == 0))
		set_cflag(COMMIT_Nolink, new_ip);
      out3:
	free_UCSname(&new_dname);
      out2:
	free_UCSname(&old_dname);
      out1:
	if (new_ip && !S_ISDIR(new_ip->i_mode))
		IWRITE_UNLOCK(new_ip);
	/*
	 * Truncating the directory index table is not guaranteed.  It
	 * may need to be done iteratively
	 */
	if (test_cflag(COMMIT_Stale, old_dir)) {
		if (old_dir->i_size > 1)
			jfs_truncate_nolock(old_dir, 0);

		clear_cflag(COMMIT_Stale, old_dir);
	}

	jfs_info("jfs_rename: returning %d", rc);
	return rc;
}