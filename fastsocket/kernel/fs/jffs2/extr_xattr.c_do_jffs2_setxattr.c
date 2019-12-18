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
typedef  int /*<<< orphan*/  uint32_t ;
struct jffs2_xattr_ref {int xprefix; struct jffs2_xattr_ref* next; int /*<<< orphan*/  xseqno; struct jffs2_xattr_ref* xd; struct jffs2_inode_cache* ic; int /*<<< orphan*/  xid; int /*<<< orphan*/  ino; int /*<<< orphan*/  xname; } ;
struct jffs2_xattr_datum {int xprefix; struct jffs2_xattr_datum* next; int /*<<< orphan*/  xseqno; struct jffs2_xattr_datum* xd; struct jffs2_inode_cache* ic; int /*<<< orphan*/  xid; int /*<<< orphan*/  ino; int /*<<< orphan*/  xname; } ;
struct jffs2_sb_info {int /*<<< orphan*/  xattr_sem; int /*<<< orphan*/  erase_completion_lock; struct jffs2_xattr_ref* xref_dead_list; } ;
struct jffs2_raw_xref {int dummy; } ;
struct jffs2_raw_xattr {int dummy; } ;
struct jffs2_inode_info {struct jffs2_inode_cache* inocache; } ;
struct jffs2_inode_cache {struct jffs2_xattr_ref* xref; int /*<<< orphan*/  ino; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_NORMAL ; 
 int EEXIST ; 
 int ENODATA ; 
 scalar_t__ IS_ERR (struct jffs2_xattr_ref*) ; 
 struct jffs2_inode_info* JFFS2_INODE_INFO (struct inode*) ; 
 struct jffs2_sb_info* JFFS2_SB_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JFFS2_SUMMARY_XATTR_SIZE ; 
 int /*<<< orphan*/  JFFS2_SUMMARY_XREF_SIZE ; 
 int /*<<< orphan*/  JFFS2_WARNING (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAD (int) ; 
 int PTR_ERR (struct jffs2_xattr_ref*) ; 
 int XATTR_CREATE ; 
 int XATTR_REPLACE ; 
 int /*<<< orphan*/  XREF_DELETE_MARKER ; 
 int check_xattr_ref_inode (struct jffs2_sb_info*,struct jffs2_inode_cache*) ; 
 struct jffs2_xattr_ref* create_xattr_datum (struct jffs2_sb_info*,int,char const*,char const*,size_t) ; 
 struct jffs2_xattr_ref* create_xattr_ref (struct jffs2_sb_info*,struct jffs2_inode_cache*,struct jffs2_xattr_ref*) ; 
 int /*<<< orphan*/  delete_xattr_ref (struct jffs2_sb_info*,struct jffs2_xattr_ref*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jffs2_complete_reservation (struct jffs2_sb_info*) ; 
 int jffs2_reserve_space (struct jffs2_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int load_xattr_datum (struct jffs2_sb_info*,struct jffs2_xattr_ref*) ; 
 int save_xattr_ref (struct jffs2_sb_info*,struct jffs2_xattr_ref*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  unrefer_xattr_datum (struct jffs2_sb_info*,struct jffs2_xattr_ref*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

int do_jffs2_setxattr(struct inode *inode, int xprefix, const char *xname,
		      const char *buffer, size_t size, int flags)
{
	struct jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
	struct jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
	struct jffs2_inode_cache *ic = f->inocache;
	struct jffs2_xattr_datum *xd;
	struct jffs2_xattr_ref *ref, *newref, **pref;
	uint32_t length, request;
	int rc;

	rc = check_xattr_ref_inode(c, ic);
	if (unlikely(rc))
		return rc;

	request = PAD(sizeof(struct jffs2_raw_xattr) + strlen(xname) + 1 + size);
	rc = jffs2_reserve_space(c, request, &length,
				 ALLOC_NORMAL, JFFS2_SUMMARY_XATTR_SIZE);
	if (rc) {
		JFFS2_WARNING("jffs2_reserve_space()=%d, request=%u\n", rc, request);
		return rc;
	}

	/* Find existing xattr */
	down_write(&c->xattr_sem);
 retry:
	for (ref=ic->xref, pref=&ic->xref; ref; pref=&ref->next, ref=ref->next) {
		xd = ref->xd;
		if (xd->xprefix != xprefix)
			continue;
		if (!xd->xname) {
			rc = load_xattr_datum(c, xd);
			if (unlikely(rc > 0)) {
				*pref = ref->next;
				delete_xattr_ref(c, ref);
				goto retry;
			} else if (unlikely(rc < 0))
				goto out;
		}
		if (!strcmp(xd->xname, xname)) {
			if (flags & XATTR_CREATE) {
				rc = -EEXIST;
				goto out;
			}
			if (!buffer) {
				ref->ino = ic->ino;
				ref->xid = xd->xid;
				ref->xseqno |= XREF_DELETE_MARKER;
				rc = save_xattr_ref(c, ref);
				if (!rc) {
					*pref = ref->next;
					spin_lock(&c->erase_completion_lock);
					ref->next = c->xref_dead_list;
					c->xref_dead_list = ref;
					spin_unlock(&c->erase_completion_lock);
					unrefer_xattr_datum(c, xd);
				} else {
					ref->ic = ic;
					ref->xd = xd;
					ref->xseqno &= ~XREF_DELETE_MARKER;
				}
				goto out;
			}
			goto found;
		}
	}
	/* not found */
	if (flags & XATTR_REPLACE) {
		rc = -ENODATA;
		goto out;
	}
	if (!buffer) {
		rc = -ENODATA;
		goto out;
	}
 found:
	xd = create_xattr_datum(c, xprefix, xname, buffer, size);
	if (IS_ERR(xd)) {
		rc = PTR_ERR(xd);
		goto out;
	}
	up_write(&c->xattr_sem);
	jffs2_complete_reservation(c);

	/* create xattr_ref */
	request = PAD(sizeof(struct jffs2_raw_xref));
	rc = jffs2_reserve_space(c, request, &length,
				 ALLOC_NORMAL, JFFS2_SUMMARY_XREF_SIZE);
	down_write(&c->xattr_sem);
	if (rc) {
		JFFS2_WARNING("jffs2_reserve_space()=%d, request=%u\n", rc, request);
		unrefer_xattr_datum(c, xd);
		up_write(&c->xattr_sem);
		return rc;
	}
	if (ref)
		*pref = ref->next;
	newref = create_xattr_ref(c, ic, xd);
	if (IS_ERR(newref)) {
		if (ref) {
			ref->next = ic->xref;
			ic->xref = ref;
		}
		rc = PTR_ERR(newref);
		unrefer_xattr_datum(c, xd);
	} else if (ref) {
		delete_xattr_ref(c, ref);
	}
 out:
	up_write(&c->xattr_sem);
	jffs2_complete_reservation(c);
	return rc;
}