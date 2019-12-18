#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_2__* d_inode; TYPE_1__ d_name; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ d_mountpoint (struct dentry*) ; 
 int /*<<< orphan*/  d_move (struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  fsnotify_move (TYPE_2__*,TYPE_2__*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dentry*) ; 
 int /*<<< orphan*/  fsnotify_oldname_free (char const*) ; 
 char* fsnotify_oldname_init (int /*<<< orphan*/ ) ; 
 struct dentry* lock_rename (struct dentry*,struct dentry*) ; 
 struct dentry* lookup_one_len (char const*,struct dentry*,int /*<<< orphan*/ ) ; 
 int simple_rename (TYPE_2__*,struct dentry*,TYPE_2__*,struct dentry*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  unlock_rename (struct dentry*,struct dentry*) ; 

struct dentry *debugfs_rename(struct dentry *old_dir, struct dentry *old_dentry,
		struct dentry *new_dir, const char *new_name)
{
	int error;
	struct dentry *dentry = NULL, *trap;
	const char *old_name;

	trap = lock_rename(new_dir, old_dir);
	/* Source or destination directories don't exist? */
	if (!old_dir->d_inode || !new_dir->d_inode)
		goto exit;
	/* Source does not exist, cyclic rename, or mountpoint? */
	if (!old_dentry->d_inode || old_dentry == trap ||
	    d_mountpoint(old_dentry))
		goto exit;
	dentry = lookup_one_len(new_name, new_dir, strlen(new_name));
	/* Lookup failed, cyclic rename or target exists? */
	if (IS_ERR(dentry) || dentry == trap || dentry->d_inode)
		goto exit;

	old_name = fsnotify_oldname_init(old_dentry->d_name.name);

	error = simple_rename(old_dir->d_inode, old_dentry, new_dir->d_inode,
		dentry);
	if (error) {
		fsnotify_oldname_free(old_name);
		goto exit;
	}
	d_move(old_dentry, dentry);
	fsnotify_move(old_dir->d_inode, new_dir->d_inode, old_name,
		old_dentry->d_name.name, S_ISDIR(old_dentry->d_inode->i_mode),
		NULL, old_dentry);
	fsnotify_oldname_free(old_name);
	unlock_rename(new_dir, old_dir);
	dput(dentry);
	return old_dentry;
exit:
	if (dentry && !IS_ERR(dentry))
		dput(dentry);
	unlock_rename(new_dir, old_dir);
	return NULL;
}