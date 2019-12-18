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
typedef  int uint ;
struct nameidata {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; scalar_t__ i_ino; } ;
struct TYPE_3__ {char* name; int len; } ;
struct dentry {int /*<<< orphan*/ * d_op; TYPE_1__ d_name; } ;
struct component_name {int dummy; } ;
struct btstack {int dummy; } ;
typedef  scalar_t__ ino_t ;
struct TYPE_4__ {int mntflag; } ;

/* Variables and functions */
 int ENOENT ; 
 struct dentry* ERR_CAST (struct inode*) ; 
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  JFS_LOOKUP ; 
 int JFS_OS2 ; 
 TYPE_2__* JFS_SBI (int /*<<< orphan*/ ) ; 
 scalar_t__ PARENT (struct inode*) ; 
 int /*<<< orphan*/  d_add (struct dentry*,int /*<<< orphan*/ *) ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 int dtSearch (struct inode*,struct component_name*,scalar_t__*,struct btstack*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_UCSname (struct component_name*) ; 
 int get_UCSname (struct component_name*,struct dentry*) ; 
 int /*<<< orphan*/  jfs_ci_dentry_operations ; 
 int /*<<< orphan*/  jfs_err (char*,int) ; 
 struct inode* jfs_iget (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  jfs_info (char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static struct dentry *jfs_lookup(struct inode *dip, struct dentry *dentry, struct nameidata *nd)
{
	struct btstack btstack;
	ino_t inum;
	struct inode *ip;
	struct component_name key;
	const char *name = dentry->d_name.name;
	int len = dentry->d_name.len;
	int rc;

	jfs_info("jfs_lookup: name = %s", name);

	if (JFS_SBI(dip->i_sb)->mntflag & JFS_OS2)
		dentry->d_op = &jfs_ci_dentry_operations;

	if ((name[0] == '.') && (len == 1))
		inum = dip->i_ino;
	else if (strcmp(name, "..") == 0)
		inum = PARENT(dip);
	else {
		if ((rc = get_UCSname(&key, dentry)))
			return ERR_PTR(rc);
		rc = dtSearch(dip, &key, &inum, &btstack, JFS_LOOKUP);
		free_UCSname(&key);
		if (rc == -ENOENT) {
			d_add(dentry, NULL);
			return NULL;
		} else if (rc) {
			jfs_err("jfs_lookup: dtSearch returned %d", rc);
			return ERR_PTR(rc);
		}
	}

	ip = jfs_iget(dip->i_sb, inum);
	if (IS_ERR(ip)) {
		jfs_err("jfs_lookup: iget failed on inum %d", (uint) inum);
		return ERR_CAST(ip);
	}

	dentry = d_splice_alias(ip, dentry);

	if (dentry && (JFS_SBI(dip->i_sb)->mntflag & JFS_OS2))
		dentry->d_op = &jfs_ci_dentry_operations;

	return dentry;
}