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
struct smb_fattr {void* f_ino; } ;
struct smb_cache_control {scalar_t__ fpos; size_t idx; int ofs; scalar_t__ filled; int /*<<< orphan*/  valid; TYPE_4__* cache; scalar_t__ page; } ;
struct qstr {int /*<<< orphan*/  len; int /*<<< orphan*/  name; int /*<<< orphan*/  hash; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_data; void* i_ino; } ;
struct TYPE_5__ {struct dentry* dentry; } ;
struct file {scalar_t__ f_pos; TYPE_1__ f_path; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; scalar_t__ name; } ;
struct dentry {void* d_fsdata; struct inode* d_inode; TYPE_3__ d_name; TYPE_2__* d_op; } ;
typedef  void* ino_t ;
typedef  scalar_t__ (* filldir_t ) (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,void*,int /*<<< orphan*/ ) ;
struct TYPE_8__ {struct dentry** dentry; } ;
struct TYPE_6__ {scalar_t__ (* d_hash ) (struct dentry*,struct qstr*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DT_UNKNOWN ; 
 size_t SMB_DIRCACHE_SIZE ; 
 int /*<<< orphan*/  SetPageUptodate (scalar_t__) ; 
 struct dentry* d_alloc (struct dentry*,struct qstr*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 struct dentry* d_lookup (struct dentry*,struct qstr*) ; 
 int /*<<< orphan*/  d_rehash (struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 void* find_inode_number (struct dentry*,struct qstr*) ; 
 int /*<<< orphan*/  full_name_hash (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ grab_cache_page (int /*<<< orphan*/ *,int) ; 
 void* iunique (int /*<<< orphan*/ ,int) ; 
 TYPE_4__* kmap (scalar_t__) ; 
 int /*<<< orphan*/  kunmap (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_cache_release (scalar_t__) ; 
 struct inode* smb_iget (int /*<<< orphan*/ ,struct smb_fattr*) ; 
 int /*<<< orphan*/  smb_new_dentry (struct dentry*) ; 
 int /*<<< orphan*/  smb_renew_times (struct dentry*) ; 
 int /*<<< orphan*/  smb_set_inode_attr (struct inode*,struct smb_fattr*) ; 
 scalar_t__ stub1 (struct dentry*,struct qstr*) ; 
 int /*<<< orphan*/  unlock_page (scalar_t__) ; 

int
smb_fill_cache(struct file *filp, void *dirent, filldir_t filldir,
	       struct smb_cache_control *ctrl, struct qstr *qname,
	       struct smb_fattr *entry)
{
	struct dentry *newdent, *dentry = filp->f_path.dentry;
	struct inode *newino, *inode = dentry->d_inode;
	struct smb_cache_control ctl = *ctrl;
	int valid = 0;
	int hashed = 0;
	ino_t ino = 0;

	qname->hash = full_name_hash(qname->name, qname->len);

	if (dentry->d_op && dentry->d_op->d_hash)
		if (dentry->d_op->d_hash(dentry, qname) != 0)
			goto end_advance;

	newdent = d_lookup(dentry, qname);

	if (!newdent) {
		newdent = d_alloc(dentry, qname);
		if (!newdent)
			goto end_advance;
	} else {
		hashed = 1;
		memcpy((char *) newdent->d_name.name, qname->name,
		       newdent->d_name.len);
	}

	if (!newdent->d_inode) {
		smb_renew_times(newdent);
		entry->f_ino = iunique(inode->i_sb, 2);
		newino = smb_iget(inode->i_sb, entry);
		if (newino) {
			smb_new_dentry(newdent);
			d_instantiate(newdent, newino);
			if (!hashed)
				d_rehash(newdent);
		}
	} else
		smb_set_inode_attr(newdent->d_inode, entry);

        if (newdent->d_inode) {
		ino = newdent->d_inode->i_ino;
		newdent->d_fsdata = (void *) ctl.fpos;
		smb_new_dentry(newdent);
	}

	if (ctl.idx >= SMB_DIRCACHE_SIZE) {
		if (ctl.page) {
			kunmap(ctl.page);
			SetPageUptodate(ctl.page);
			unlock_page(ctl.page);
			page_cache_release(ctl.page);
		}
		ctl.cache = NULL;
		ctl.idx  -= SMB_DIRCACHE_SIZE;
		ctl.ofs  += 1;
		ctl.page  = grab_cache_page(&inode->i_data, ctl.ofs);
		if (ctl.page)
			ctl.cache = kmap(ctl.page);
	}
	if (ctl.cache) {
		ctl.cache->dentry[ctl.idx] = newdent;
		valid = 1;
	}
	dput(newdent);

end_advance:
	if (!valid)
		ctl.valid = 0;
	if (!ctl.filled && (ctl.fpos == filp->f_pos)) {
		if (!ino)
			ino = find_inode_number(dentry, qname);
		if (!ino)
			ino = iunique(inode->i_sb, 2);
		ctl.filled = filldir(dirent, qname->name, qname->len,
				     filp->f_pos, ino, DT_UNKNOWN);
		if (!ctl.filled)
			filp->f_pos += 1;
	}
	ctl.fpos += 1;
	ctl.idx  += 1;
	*ctrl = ctl;
	return (ctl.valid || !ctl.filled);
}