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
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_count; void* i_mtime; void* i_ctime; int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; struct inode* d_inode; } ;
struct component_name {int dummy; } ;
struct btstack {int dummy; } ;
typedef  int /*<<< orphan*/  ino_t ;
struct TYPE_4__ {int /*<<< orphan*/  commit_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_MUTEX_CHILD ; 
 int /*<<< orphan*/  COMMIT_MUTEX_PARENT ; 
 void* CURRENT_TIME ; 
 int EMLINK ; 
 int ENOENT ; 
 int /*<<< orphan*/  JFS_CREATE ; 
 TYPE_2__* JFS_IP (struct inode*) ; 
 scalar_t__ JFS_LINK_MAX ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int dtInsert (int /*<<< orphan*/ ,struct inode*,struct component_name*,int /*<<< orphan*/ *,struct btstack*) ; 
 int dtSearch (struct inode*,struct component_name*,int /*<<< orphan*/ *,struct btstack*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_UCSname (struct component_name*) ; 
 int get_UCSname (struct component_name*,struct dentry*) ; 
 int /*<<< orphan*/  inc_nlink (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  jfs_info (char*,int,...) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txBegin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int txCommit (int /*<<< orphan*/ ,int,struct inode**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txEnd (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int jfs_link(struct dentry *old_dentry,
	     struct inode *dir, struct dentry *dentry)
{
	int rc;
	tid_t tid;
	struct inode *ip = old_dentry->d_inode;
	ino_t ino;
	struct component_name dname;
	struct btstack btstack;
	struct inode *iplist[2];

	jfs_info("jfs_link: %s %s", old_dentry->d_name.name,
		 dentry->d_name.name);

	if (ip->i_nlink == JFS_LINK_MAX)
		return -EMLINK;

	if (ip->i_nlink == 0)
		return -ENOENT;

	tid = txBegin(ip->i_sb, 0);

	mutex_lock_nested(&JFS_IP(dir)->commit_mutex, COMMIT_MUTEX_PARENT);
	mutex_lock_nested(&JFS_IP(ip)->commit_mutex, COMMIT_MUTEX_CHILD);

	/*
	 * scan parent directory for entry/freespace
	 */
	if ((rc = get_UCSname(&dname, dentry)))
		goto out;

	if ((rc = dtSearch(dir, &dname, &ino, &btstack, JFS_CREATE)))
		goto free_dname;

	/*
	 * create entry for new link in parent directory
	 */
	ino = ip->i_ino;
	if ((rc = dtInsert(tid, dir, &dname, &ino, &btstack)))
		goto free_dname;

	/* update object inode */
	inc_nlink(ip);		/* for new link */
	ip->i_ctime = CURRENT_TIME;
	dir->i_ctime = dir->i_mtime = CURRENT_TIME;
	mark_inode_dirty(dir);
	atomic_inc(&ip->i_count);

	iplist[0] = ip;
	iplist[1] = dir;
	rc = txCommit(tid, 2, &iplist[0], 0);

	if (rc) {
		ip->i_nlink--; /* never instantiated */
		iput(ip);
	} else
		d_instantiate(dentry, ip);

      free_dname:
	free_UCSname(&dname);

      out:
	txEnd(tid);

	mutex_unlock(&JFS_IP(ip)->commit_mutex);
	mutex_unlock(&JFS_IP(dir)->commit_mutex);

	jfs_info("jfs_link: rc:%d", rc);
	return rc;
}