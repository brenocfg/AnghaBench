#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct xattr_handler {scalar_t__ (* list ) (struct inode*,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct jffs2_xattr_ref {struct jffs2_xattr_ref* next; struct jffs2_xattr_datum* xd; struct jffs2_inode_cache* ic; } ;
struct jffs2_xattr_datum {int /*<<< orphan*/  name_len; int /*<<< orphan*/  xname; int /*<<< orphan*/  xprefix; } ;
struct jffs2_sb_info {int /*<<< orphan*/  xattr_sem; } ;
struct jffs2_inode_info {struct jffs2_inode_cache* inocache; } ;
struct jffs2_inode_cache {struct jffs2_xattr_ref* xref; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {struct inode* d_inode; } ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct jffs2_inode_info* JFFS2_INODE_INFO (struct inode*) ; 
 struct jffs2_sb_info* JFFS2_SB_INFO (int /*<<< orphan*/ ) ; 
 scalar_t__ check_xattr_ref_inode (struct jffs2_sb_info*,struct jffs2_inode_cache*) ; 
 int /*<<< orphan*/  delete_xattr_ref (struct jffs2_sb_info*,struct jffs2_xattr_ref*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 scalar_t__ load_xattr_datum (struct jffs2_sb_info*,struct jffs2_xattr_datum*) ; 
 scalar_t__ stub1 (struct inode*,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (struct inode*,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 struct xattr_handler* xprefix_to_handler (int /*<<< orphan*/ ) ; 

ssize_t jffs2_listxattr(struct dentry *dentry, char *buffer, size_t size)
{
	struct inode *inode = dentry->d_inode;
	struct jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
	struct jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
	struct jffs2_inode_cache *ic = f->inocache;
	struct jffs2_xattr_ref *ref, **pref;
	struct jffs2_xattr_datum *xd;
	struct xattr_handler *xhandle;
	ssize_t len, rc;
	int retry = 0;

	rc = check_xattr_ref_inode(c, ic);
	if (unlikely(rc))
		return rc;

	down_read(&c->xattr_sem);
 retry:
	len = 0;
	for (ref=ic->xref, pref=&ic->xref; ref; pref=&ref->next, ref=ref->next) {
		BUG_ON(ref->ic != ic);
		xd = ref->xd;
		if (!xd->xname) {
			/* xdatum is unchached */
			if (!retry) {
				retry = 1;
				up_read(&c->xattr_sem);
				down_write(&c->xattr_sem);
				goto retry;
			} else {
				rc = load_xattr_datum(c, xd);
				if (unlikely(rc > 0)) {
					*pref = ref->next;
					delete_xattr_ref(c, ref);
					goto retry;
				} else if (unlikely(rc < 0))
					goto out;
			}
		}
		xhandle = xprefix_to_handler(xd->xprefix);
		if (!xhandle)
			continue;
		if (buffer) {
			rc = xhandle->list(inode, buffer+len, size-len, xd->xname, xd->name_len);
		} else {
			rc = xhandle->list(inode, NULL, 0, xd->xname, xd->name_len);
		}
		if (rc < 0)
			goto out;
		len += rc;
	}
	rc = len;
 out:
	if (!retry) {
		up_read(&c->xattr_sem);
	} else {
		up_write(&c->xattr_sem);
	}
	return rc;
}