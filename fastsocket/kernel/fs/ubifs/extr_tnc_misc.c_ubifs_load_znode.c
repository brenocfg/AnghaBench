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
struct ubifs_znode {int iip; int /*<<< orphan*/  time; struct ubifs_znode* parent; } ;
struct ubifs_zbranch {struct ubifs_znode* znode; int /*<<< orphan*/  len; int /*<<< orphan*/  offs; int /*<<< orphan*/  lnum; } ;
struct ubifs_info {int /*<<< orphan*/  clean_zn_cnt; int /*<<< orphan*/  max_znode_sz; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct ubifs_znode* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_seconds () ; 
 int /*<<< orphan*/  kfree (struct ubifs_znode*) ; 
 struct ubifs_znode* kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read_znode (struct ubifs_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ubifs_znode*) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 int /*<<< orphan*/  ubifs_clean_zn_cnt ; 

struct ubifs_znode *ubifs_load_znode(struct ubifs_info *c,
				     struct ubifs_zbranch *zbr,
				     struct ubifs_znode *parent, int iip)
{
	int err;
	struct ubifs_znode *znode;

	ubifs_assert(!zbr->znode);
	/*
	 * A slab cache is not presently used for znodes because the znode size
	 * depends on the fanout which is stored in the superblock.
	 */
	znode = kzalloc(c->max_znode_sz, GFP_NOFS);
	if (!znode)
		return ERR_PTR(-ENOMEM);

	err = read_znode(c, zbr->lnum, zbr->offs, zbr->len, znode);
	if (err)
		goto out;

	atomic_long_inc(&c->clean_zn_cnt);

	/*
	 * Increment the global clean znode counter as well. It is OK that
	 * global and per-FS clean znode counters may be inconsistent for some
	 * short time (because we might be preempted at this point), the global
	 * one is only used in shrinker.
	 */
	atomic_long_inc(&ubifs_clean_zn_cnt);

	zbr->znode = znode;
	znode->parent = parent;
	znode->time = get_seconds();
	znode->iip = iip;

	return znode;

out:
	kfree(znode);
	return ERR_PTR(err);
}