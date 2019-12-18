#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct qstr {int len; char* name; int /*<<< orphan*/  hash; } ;
struct nfs_entry {int len; char* name; int /*<<< orphan*/  fattr; int /*<<< orphan*/  fh; } ;
struct inode {int /*<<< orphan*/  d_sb; int /*<<< orphan*/  d_op; struct inode* d_inode; } ;
struct dentry {int /*<<< orphan*/  d_sb; int /*<<< orphan*/  d_op; struct dentry* d_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  dentry_ops; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct inode*) ; 
 TYPE_1__* NFS_PROTO (struct inode*) ; 
 struct inode* d_alloc (struct inode*,struct qstr*) ; 
 int /*<<< orphan*/  d_drop (struct inode*) ; 
 struct inode* d_lookup (struct inode*,struct qstr*) ; 
 struct inode* d_materialise_unique (struct inode*,struct inode*) ; 
 int /*<<< orphan*/  dput (struct inode*) ; 
 int /*<<< orphan*/  full_name_hash (char*,int) ; 
 struct inode* nfs_fhget (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_refresh_inode (struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ nfs_same_file (struct inode*,struct nfs_entry*) ; 
 int /*<<< orphan*/  nfs_save_change_attribute (struct inode*) ; 
 int /*<<< orphan*/  nfs_set_verifier (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void nfs_prime_dcache(struct dentry *parent, struct nfs_entry *entry)
{
	struct qstr filename = {
		.len = entry->len,
		.name = entry->name,
	};
	struct dentry *dentry;
	struct dentry *alias;
	struct inode *dir = parent->d_inode;
	struct inode *inode;

	if (filename.name[0] == '.') {
		if (filename.len == 1)
			return;
		if (filename.len == 2 && filename.name[1] == '.')
			return;
	}
	filename.hash = full_name_hash(filename.name, filename.len);

	dentry = d_lookup(parent, &filename);
	if (dentry != NULL) {
		if (nfs_same_file(dentry, entry)) {
			nfs_set_verifier(dentry, nfs_save_change_attribute(dir));
			nfs_refresh_inode(dentry->d_inode, entry->fattr);
			goto out;
		} else {
			d_drop(dentry);
			dput(dentry);
		}
	}

	dentry = d_alloc(parent, &filename);
	if (dentry == NULL)
		return;

	dentry->d_op = NFS_PROTO(dir)->dentry_ops;
	inode = nfs_fhget(dentry->d_sb, entry->fh, entry->fattr);
	if (IS_ERR(inode))
		goto out;

	alias = d_materialise_unique(dentry, inode);
	if (IS_ERR(alias))
		goto out;
	else if (alias) {
		nfs_set_verifier(alias, nfs_save_change_attribute(dir));
		dput(alias);
	} else
		nfs_set_verifier(dentry, nfs_save_change_attribute(dir));

out:
	dput(dentry);
}