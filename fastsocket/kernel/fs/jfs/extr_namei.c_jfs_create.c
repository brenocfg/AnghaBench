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
struct TYPE_6__ {int /*<<< orphan*/  ixpxd; } ;
struct tblock {TYPE_2__ u; int /*<<< orphan*/  ino; int /*<<< orphan*/  xflag; } ;
struct nameidata {int dummy; } ;
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_ctime; TYPE_3__* i_mapping; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/ * i_op; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;
struct component_name {int dummy; } ;
struct btstack {int dummy; } ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_8__ {int /*<<< orphan*/  commit_mutex; int /*<<< orphan*/  ixpxd; } ;
struct TYPE_7__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_CREATE ; 
 int /*<<< orphan*/  COMMIT_MUTEX_CHILD ; 
 int /*<<< orphan*/  COMMIT_MUTEX_PARENT ; 
 int /*<<< orphan*/  CURRENT_TIME ; 
 int EIO ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  JFS_CREATE ; 
 TYPE_4__* JFS_IP (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int dtInsert (int /*<<< orphan*/ ,struct inode*,struct component_name*,int /*<<< orphan*/ *,struct btstack*) ; 
 int dtSearch (struct inode*,struct component_name*,int /*<<< orphan*/ *,struct btstack*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_UCSname (struct component_name*) ; 
 int /*<<< orphan*/  free_ea_wmap (struct inode*) ; 
 int get_UCSname (struct component_name*,struct dentry*) ; 
 struct inode* ialloc (struct inode*,int) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  jfs_aops ; 
 int /*<<< orphan*/  jfs_err (char*,...) ; 
 int /*<<< orphan*/  jfs_file_inode_operations ; 
 int /*<<< orphan*/  jfs_file_operations ; 
 int /*<<< orphan*/  jfs_info (char*,...) ; 
 int jfs_init_acl (int /*<<< orphan*/ ,struct inode*,struct inode*) ; 
 int jfs_init_security (int /*<<< orphan*/ ,struct inode*,struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct tblock* tid_to_tblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txAbort (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  txBegin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int txCommit (int /*<<< orphan*/ ,int,struct inode**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txEnd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 
 int /*<<< orphan*/  xtInitRoot (int /*<<< orphan*/ ,struct inode*) ; 

__attribute__((used)) static int jfs_create(struct inode *dip, struct dentry *dentry, int mode,
		struct nameidata *nd)
{
	int rc = 0;
	tid_t tid;		/* transaction id */
	struct inode *ip = NULL;	/* child directory inode */
	ino_t ino;
	struct component_name dname;	/* child directory name */
	struct btstack btstack;
	struct inode *iplist[2];
	struct tblock *tblk;

	jfs_info("jfs_create: dip:0x%p name:%s", dip, dentry->d_name.name);

	/*
	 * search parent directory for entry/freespace
	 * (dtSearch() returns parent directory page pinned)
	 */
	if ((rc = get_UCSname(&dname, dentry)))
		goto out1;

	/*
	 * Either iAlloc() or txBegin() may block.  Deadlock can occur if we
	 * block there while holding dtree page, so we allocate the inode &
	 * begin the transaction before we search the directory.
	 */
	ip = ialloc(dip, mode);
	if (IS_ERR(ip)) {
		rc = PTR_ERR(ip);
		goto out2;
	}

	tid = txBegin(dip->i_sb, 0);

	mutex_lock_nested(&JFS_IP(dip)->commit_mutex, COMMIT_MUTEX_PARENT);
	mutex_lock_nested(&JFS_IP(ip)->commit_mutex, COMMIT_MUTEX_CHILD);

	rc = jfs_init_acl(tid, ip, dip);
	if (rc)
		goto out3;

	rc = jfs_init_security(tid, ip, dip);
	if (rc) {
		txAbort(tid, 0);
		goto out3;
	}

	if ((rc = dtSearch(dip, &dname, &ino, &btstack, JFS_CREATE))) {
		jfs_err("jfs_create: dtSearch returned %d", rc);
		txAbort(tid, 0);
		goto out3;
	}

	tblk = tid_to_tblock(tid);
	tblk->xflag |= COMMIT_CREATE;
	tblk->ino = ip->i_ino;
	tblk->u.ixpxd = JFS_IP(ip)->ixpxd;

	iplist[0] = dip;
	iplist[1] = ip;

	/*
	 * initialize the child XAD tree root in-line in inode
	 */
	xtInitRoot(tid, ip);

	/*
	 * create entry in parent directory for child directory
	 * (dtInsert() releases parent directory page)
	 */
	ino = ip->i_ino;
	if ((rc = dtInsert(tid, dip, &dname, &ino, &btstack))) {
		if (rc == -EIO) {
			jfs_err("jfs_create: dtInsert returned -EIO");
			txAbort(tid, 1);	/* Marks Filesystem dirty */
		} else
			txAbort(tid, 0);	/* Filesystem full */
		goto out3;
	}

	ip->i_op = &jfs_file_inode_operations;
	ip->i_fop = &jfs_file_operations;
	ip->i_mapping->a_ops = &jfs_aops;

	mark_inode_dirty(ip);

	dip->i_ctime = dip->i_mtime = CURRENT_TIME;

	mark_inode_dirty(dip);

	rc = txCommit(tid, 2, &iplist[0], 0);

      out3:
	txEnd(tid);
	mutex_unlock(&JFS_IP(ip)->commit_mutex);
	mutex_unlock(&JFS_IP(dip)->commit_mutex);
	if (rc) {
		free_ea_wmap(ip);
		ip->i_nlink = 0;
		unlock_new_inode(ip);
		iput(ip);
	} else {
		d_instantiate(dentry, ip);
		unlock_new_inode(ip);
	}

      out2:
	free_UCSname(&dname);

      out1:

	jfs_info("jfs_create: rc:%d", rc);
	return rc;
}