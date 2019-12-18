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
typedef  union ubifs_key {int dummy; } ubifs_key ;
struct ubifs_znode {int child_cnt; TYPE_1__* zbranch; scalar_t__ cnext; } ;
struct ubifs_info {int /*<<< orphan*/  tnc_mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  len; int /*<<< orphan*/  lnum; union ubifs_key key; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGKEY (union ubifs_key*) ; 
 int ENOENT ; 
 scalar_t__ IS_ERR (struct ubifs_znode*) ; 
 int PTR_ERR (struct ubifs_znode*) ; 
 int dbg_check_tnc (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_dump_znode (struct ubifs_info*,struct ubifs_znode*) ; 
 int /*<<< orphan*/  dbg_tnc (char*,int /*<<< orphan*/ ) ; 
 struct ubifs_znode* dirty_cow_bottom_up (struct ubifs_info*,struct ubifs_znode*) ; 
 int /*<<< orphan*/  key_in_range (struct ubifs_info*,union ubifs_key*,union ubifs_key*,union ubifs_key*) ; 
 int /*<<< orphan*/  lnc_free (TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int tnc_delete (struct ubifs_info*,struct ubifs_znode*,int) ; 
 int tnc_next (struct ubifs_info*,struct ubifs_znode**,int*) ; 
 int ubifs_add_dirt (struct ubifs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ubifs_lookup_level0 (struct ubifs_info*,union ubifs_key*,struct ubifs_znode**,int*) ; 
 int /*<<< orphan*/  ubifs_zn_dirty (struct ubifs_znode*) ; 

int ubifs_tnc_remove_range(struct ubifs_info *c, union ubifs_key *from_key,
			   union ubifs_key *to_key)
{
	int i, n, k, err = 0;
	struct ubifs_znode *znode;
	union ubifs_key *key;

	mutex_lock(&c->tnc_mutex);
	while (1) {
		/* Find first level 0 znode that contains keys to remove */
		err = ubifs_lookup_level0(c, from_key, &znode, &n);
		if (err < 0)
			goto out_unlock;

		if (err)
			key = from_key;
		else {
			err = tnc_next(c, &znode, &n);
			if (err == -ENOENT) {
				err = 0;
				goto out_unlock;
			}
			if (err < 0)
				goto out_unlock;
			key = &znode->zbranch[n].key;
			if (!key_in_range(c, key, from_key, to_key)) {
				err = 0;
				goto out_unlock;
			}
		}

		/* Ensure the znode is dirtied */
		if (znode->cnext || !ubifs_zn_dirty(znode)) {
			znode = dirty_cow_bottom_up(c, znode);
			if (IS_ERR(znode)) {
				err = PTR_ERR(znode);
				goto out_unlock;
			}
		}

		/* Remove all keys in range except the first */
		for (i = n + 1, k = 0; i < znode->child_cnt; i++, k++) {
			key = &znode->zbranch[i].key;
			if (!key_in_range(c, key, from_key, to_key))
				break;
			lnc_free(&znode->zbranch[i]);
			err = ubifs_add_dirt(c, znode->zbranch[i].lnum,
					     znode->zbranch[i].len);
			if (err) {
				dbg_dump_znode(c, znode);
				goto out_unlock;
			}
			dbg_tnc("removing %s", DBGKEY(key));
		}
		if (k) {
			for (i = n + 1 + k; i < znode->child_cnt; i++)
				znode->zbranch[i - k] = znode->zbranch[i];
			znode->child_cnt -= k;
		}

		/* Now delete the first */
		err = tnc_delete(c, znode, n);
		if (err)
			goto out_unlock;
	}

out_unlock:
	if (!err)
		err = dbg_check_tnc(c, 0);
	mutex_unlock(&c->tnc_mutex);
	return err;
}