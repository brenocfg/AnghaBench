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
struct jffs2_xattr_ref {struct jffs2_xattr_ref* next; struct jffs2_xattr_datum* xd; struct jffs2_inode_cache* ic; } ;
struct jffs2_xattr_datum {int xprefix; int value_len; int /*<<< orphan*/  xvalue; int /*<<< orphan*/  xname; } ;
struct jffs2_sb_info {int /*<<< orphan*/  xattr_sem; } ;
struct jffs2_inode_info {struct jffs2_inode_cache* inocache; } ;
struct jffs2_inode_cache {struct jffs2_xattr_ref* xref; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENODATA ; 
 int ERANGE ; 
 struct jffs2_inode_info* JFFS2_INODE_INFO (struct inode*) ; 
 struct jffs2_sb_info* JFFS2_SB_INFO (int /*<<< orphan*/ ) ; 
 int check_xattr_ref_inode (struct jffs2_sb_info*,struct jffs2_inode_cache*) ; 
 int /*<<< orphan*/  delete_xattr_ref (struct jffs2_sb_info*,struct jffs2_xattr_ref*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int load_xattr_datum (struct jffs2_sb_info*,struct jffs2_xattr_datum*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int do_jffs2_getxattr(struct inode *inode, int xprefix, const char *xname,
		      char *buffer, size_t size)
{
	struct jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
	struct jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
	struct jffs2_inode_cache *ic = f->inocache;
	struct jffs2_xattr_datum *xd;
	struct jffs2_xattr_ref *ref, **pref;
	int rc, retry = 0;

	rc = check_xattr_ref_inode(c, ic);
	if (unlikely(rc))
		return rc;

	down_read(&c->xattr_sem);
 retry:
	for (ref=ic->xref, pref=&ic->xref; ref; pref=&ref->next, ref=ref->next) {
		BUG_ON(ref->ic!=ic);

		xd = ref->xd;
		if (xd->xprefix != xprefix)
			continue;
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
				} else if (unlikely(rc < 0)) {
					goto out;
				}
			}
		}
		if (!strcmp(xname, xd->xname)) {
			rc = xd->value_len;
			if (buffer) {
				if (size < rc) {
					rc = -ERANGE;
				} else {
					memcpy(buffer, xd->xvalue, rc);
				}
			}
			goto out;
		}
	}
	rc = -ENODATA;
 out:
	if (!retry) {
		up_read(&c->xattr_sem);
	} else {
		up_write(&c->xattr_sem);
	}
	return rc;
}