#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct qstr {int /*<<< orphan*/  len; int /*<<< orphan*/  name; int /*<<< orphan*/  hash; } ;
struct inode {int dummy; } ;
struct dentry {TYPE_3__* d_op; TYPE_1__* d_inode; } ;
struct cifs_fattr {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* d_hash ) (struct dentry*,struct qstr*) ;} ;
struct TYPE_6__ {scalar_t__ nocase; } ;
struct TYPE_5__ {struct super_block* i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIFS_SB (struct super_block*) ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  cFYI (int,char*,int /*<<< orphan*/ ) ; 
 TYPE_3__ cifs_ci_dentry_ops ; 
 TYPE_3__ cifs_dentry_ops ; 
 struct inode* cifs_iget (struct super_block*,struct cifs_fattr*) ; 
 TYPE_2__* cifs_sb_master_tcon (int /*<<< orphan*/ ) ; 
 struct dentry* d_alloc (struct dentry*,struct qstr*) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 struct dentry* d_lookup (struct dentry*,struct qstr*) ; 
 struct dentry* d_materialise_unique (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  full_name_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct dentry*,struct qstr*) ; 

__attribute__((used)) static struct dentry *
cifs_readdir_lookup(struct dentry *parent, struct qstr *name,
		    struct cifs_fattr *fattr)
{
	struct dentry *dentry, *alias;
	struct inode *inode;
	struct super_block *sb = parent->d_inode->i_sb;

	cFYI(1, "For %s", name->name);

	if (parent->d_op && parent->d_op->d_hash)
		parent->d_op->d_hash(parent, name);
	else
		name->hash = full_name_hash(name->name, name->len);

	dentry = d_lookup(parent, name);
	if (dentry) {
		/* FIXME: check for inode number changes? */
		if (dentry->d_inode != NULL)
			return dentry;
		d_drop(dentry);
		dput(dentry);
	}

	dentry = d_alloc(parent, name);
	if (dentry == NULL)
		return NULL;

	inode = cifs_iget(sb, fattr);
	if (!inode) {
		dput(dentry);
		return NULL;
	}

	if (cifs_sb_master_tcon(CIFS_SB(sb))->nocase)
		dentry->d_op = &cifs_ci_dentry_ops;
	else
		dentry->d_op = &cifs_dentry_ops;

	alias = d_materialise_unique(dentry, inode);
	if (alias != NULL) {
		dput(dentry);
		if (IS_ERR(alias))
			return NULL;
		dentry = alias;
	}

	return dentry;
}