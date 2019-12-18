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
typedef  union ubifs_key {int dummy; } ubifs_key ;
struct ubifs_znode {struct ubifs_zbranch* zbranch; scalar_t__ cnext; } ;
struct ubifs_zbranch {int lnum; int len; int offs; int /*<<< orphan*/  key; int /*<<< orphan*/ * znode; } ;
struct ubifs_info {int /*<<< orphan*/  tnc_mutex; scalar_t__ replaying; } ;
struct qstr {char* name; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGKEY (union ubifs_key const*) ; 
 scalar_t__ IS_ERR (struct ubifs_znode*) ; 
 int PTR_ERR (struct ubifs_znode*) ; 
 int dbg_check_tnc (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_tnc (char*,int,...) ; 
 struct ubifs_znode* dirty_cow_bottom_up (struct ubifs_info*,struct ubifs_znode*) ; 
 int fallible_resolve_collision (struct ubifs_info*,union ubifs_key const*,struct ubifs_znode**,int*,struct qstr const*,int) ; 
 int /*<<< orphan*/  key_copy (struct ubifs_info*,union ubifs_key const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lnc_free (struct ubifs_zbranch*) ; 
 int lookup_level0_dirty (struct ubifs_info*,union ubifs_key const*,struct ubifs_znode**,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int resolve_collision (struct ubifs_info*,union ubifs_key const*,struct ubifs_znode**,int*,struct qstr const*) ; 
 int tnc_insert (struct ubifs_info*,struct ubifs_znode*,struct ubifs_zbranch*,int) ; 
 int ubifs_add_dirt (struct ubifs_info*,int,int) ; 
 int ubifs_tnc_remove_nm (struct ubifs_info*,union ubifs_key const*,struct qstr*) ; 
 int /*<<< orphan*/  ubifs_zn_dirty (struct ubifs_znode*) ; 

int ubifs_tnc_add_nm(struct ubifs_info *c, const union ubifs_key *key,
		     int lnum, int offs, int len, const struct qstr *nm)
{
	int found, n, err = 0;
	struct ubifs_znode *znode;

	mutex_lock(&c->tnc_mutex);
	dbg_tnc("LEB %d:%d, name '%.*s', key %s", lnum, offs, nm->len, nm->name,
		DBGKEY(key));
	found = lookup_level0_dirty(c, key, &znode, &n);
	if (found < 0) {
		err = found;
		goto out_unlock;
	}

	if (found == 1) {
		if (c->replaying)
			found = fallible_resolve_collision(c, key, &znode, &n,
							   nm, 1);
		else
			found = resolve_collision(c, key, &znode, &n, nm);
		dbg_tnc("rc returned %d, znode %p, n %d", found, znode, n);
		if (found < 0) {
			err = found;
			goto out_unlock;
		}

		/* Ensure the znode is dirtied */
		if (znode->cnext || !ubifs_zn_dirty(znode)) {
			znode = dirty_cow_bottom_up(c, znode);
			if (IS_ERR(znode)) {
				err = PTR_ERR(znode);
				goto out_unlock;
			}
		}

		if (found == 1) {
			struct ubifs_zbranch *zbr = &znode->zbranch[n];

			lnc_free(zbr);
			err = ubifs_add_dirt(c, zbr->lnum, zbr->len);
			zbr->lnum = lnum;
			zbr->offs = offs;
			zbr->len = len;
			goto out_unlock;
		}
	}

	if (!found) {
		struct ubifs_zbranch zbr;

		zbr.znode = NULL;
		zbr.lnum = lnum;
		zbr.offs = offs;
		zbr.len = len;
		key_copy(c, key, &zbr.key);
		err = tnc_insert(c, znode, &zbr, n + 1);
		if (err)
			goto out_unlock;
		if (c->replaying) {
			/*
			 * We did not find it in the index so there may be a
			 * dangling branch still in the index. So we remove it
			 * by passing 'ubifs_tnc_remove_nm()' the same key but
			 * an unmatchable name.
			 */
			struct qstr noname = { .len = 0, .name = "" };

			err = dbg_check_tnc(c, 0);
			mutex_unlock(&c->tnc_mutex);
			if (err)
				return err;
			return ubifs_tnc_remove_nm(c, key, &noname);
		}
	}

out_unlock:
	if (!err)
		err = dbg_check_tnc(c, 0);
	mutex_unlock(&c->tnc_mutex);
	return err;
}