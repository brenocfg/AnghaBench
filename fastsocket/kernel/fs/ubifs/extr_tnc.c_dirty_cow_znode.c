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
struct ubifs_znode {int /*<<< orphan*/  flags; } ;
struct ubifs_zbranch {scalar_t__ len; scalar_t__ offs; scalar_t__ lnum; struct ubifs_znode* znode; } ;
struct ubifs_info {int /*<<< orphan*/  clean_zn_cnt; int /*<<< orphan*/  dirty_zn_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  COW_ZNODE ; 
 int /*<<< orphan*/  DIRTY_ZNODE ; 
 struct ubifs_znode* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct ubifs_znode*) ; 
 int add_idx_dirt (struct ubifs_info*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  atomic_long_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 struct ubifs_znode* copy_znode (struct ubifs_info*,struct ubifs_znode*) ; 
 int insert_old_idx (struct ubifs_info*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubifs_clean_zn_cnt ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct ubifs_znode *dirty_cow_znode(struct ubifs_info *c,
					   struct ubifs_zbranch *zbr)
{
	struct ubifs_znode *znode = zbr->znode;
	struct ubifs_znode *zn;
	int err;

	if (!test_bit(COW_ZNODE, &znode->flags)) {
		/* znode is not being committed */
		if (!test_and_set_bit(DIRTY_ZNODE, &znode->flags)) {
			atomic_long_inc(&c->dirty_zn_cnt);
			atomic_long_dec(&c->clean_zn_cnt);
			atomic_long_dec(&ubifs_clean_zn_cnt);
			err = add_idx_dirt(c, zbr->lnum, zbr->len);
			if (unlikely(err))
				return ERR_PTR(err);
		}
		return znode;
	}

	zn = copy_znode(c, znode);
	if (IS_ERR(zn))
		return zn;

	if (zbr->len) {
		err = insert_old_idx(c, zbr->lnum, zbr->offs);
		if (unlikely(err))
			return ERR_PTR(err);
		err = add_idx_dirt(c, zbr->lnum, zbr->len);
	} else
		err = 0;

	zbr->znode = zn;
	zbr->lnum = 0;
	zbr->offs = 0;
	zbr->len = 0;

	if (unlikely(err))
		return ERR_PTR(err);
	return zn;
}