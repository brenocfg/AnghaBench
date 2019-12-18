#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct qstr {int len; char* name; int /*<<< orphan*/  hash; } ;
struct inode {int i_mode; int /*<<< orphan*/  i_sb; } ;
struct fuse_inode {int /*<<< orphan*/  nlookup; } ;
struct TYPE_5__ {int mode; } ;
struct fuse_entry_out {scalar_t__ nodeid; TYPE_2__ attr; int /*<<< orphan*/  generation; } ;
struct fuse_dirent {int namelen; char* name; } ;
struct fuse_direntplus {struct fuse_dirent dirent; struct fuse_entry_out entry_out; } ;
struct fuse_conn {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {struct dentry* dentry; } ;
struct file {TYPE_1__ f_path; } ;
struct dentry {int /*<<< orphan*/ * d_op; struct inode* d_inode; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int S_IFMT ; 
 struct dentry* d_alloc (struct dentry*,struct qstr*) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int d_invalidate (struct dentry*) ; 
 struct dentry* d_lookup (struct dentry*,struct qstr*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  entry_attr_timeout (struct fuse_entry_out*) ; 
 int /*<<< orphan*/  full_name_hash (char*,int) ; 
 int /*<<< orphan*/  fuse_change_attributes (struct inode*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fuse_change_entry_timeout (struct dentry*,struct fuse_entry_out*) ; 
 int /*<<< orphan*/  fuse_dentry_operations ; 
 struct inode* fuse_iget (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct dentry* fuse_materialise_dentry (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  fuse_valid_type (int) ; 
 struct fuse_conn* get_fuse_conn (struct inode*) ; 
 struct fuse_inode* get_fuse_inode (struct inode*) ; 
 scalar_t__ get_node_id (struct inode*) ; 
 scalar_t__ invalid_nodeid (scalar_t__) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fuse_direntplus_link(struct file *file,
				struct fuse_direntplus *direntplus,
				u64 attr_version)
{
	int err;
	struct fuse_entry_out *o = &direntplus->entry_out;
	struct fuse_dirent *dirent = &direntplus->dirent;
	struct dentry *parent = file->f_path.dentry;
	struct qstr name = { .len = dirent->namelen, .name = dirent->name };
	struct dentry *dentry;
	struct dentry *alias;
	struct inode *dir = parent->d_inode;
	struct fuse_conn *fc;
	struct inode *inode;

	if (!o->nodeid) {
		/*
		 * Unlike in the case of fuse_lookup, zero nodeid does not mean
		 * ENOENT. Instead, it only means the userspace filesystem did
		 * not want to return attributes/handle for this entry.
		 *
		 * So do nothing.
		 */
		return 0;
	}

	if (name.name[0] == '.') {
		/*
		 * We could potentially refresh the attributes of the directory
		 * and its parent?
		 */
		if (name.len == 1)
			return 0;
		if (name.name[1] == '.' && name.len == 2)
			return 0;
	}

	if (invalid_nodeid(o->nodeid))
		return -EIO;
	if (!fuse_valid_type(o->attr.mode))
		return -EIO;

	fc = get_fuse_conn(dir);

	name.hash = full_name_hash(name.name, name.len);
	dentry = d_lookup(parent, &name);
	if (dentry) {
		inode = dentry->d_inode;
		if (!inode) {
			d_drop(dentry);
		} else if (get_node_id(inode) != o->nodeid ||
			   ((o->attr.mode ^ inode->i_mode) & S_IFMT)) {
			err = d_invalidate(dentry);
			if (err)
				goto out;
		} else if (is_bad_inode(inode)) {
			err = -EIO;
			goto out;
		} else {
			struct fuse_inode *fi;
			fi = get_fuse_inode(inode);
			spin_lock(&fc->lock);
			fi->nlookup++;
			spin_unlock(&fc->lock);

			fuse_change_attributes(inode, &o->attr,
					       entry_attr_timeout(o),
					       attr_version);

			/*
			 * The other branch to 'found' comes via fuse_iget()
			 * which bumps nlookup inside
			 */
			goto found;
		}
		dput(dentry);
	}

	dentry = d_alloc(parent, &name);
	err = -ENOMEM;
	if (!dentry)
		goto out;
	dentry->d_op = &fuse_dentry_operations;

	inode = fuse_iget(dir->i_sb, o->nodeid, o->generation,
			  &o->attr, entry_attr_timeout(o), attr_version);
	if (!inode)
		goto out;

	alias = fuse_materialise_dentry(dentry, inode);
	err = PTR_ERR(alias);
	if (IS_ERR(alias))
		goto out;

	if (alias) {
		dput(dentry);
		dentry = alias;
	}

found:
	fuse_change_entry_timeout(dentry, o);

	err = 0;
out:
	dput(dentry);
	return err;
}