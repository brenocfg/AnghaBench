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
struct ubifs_znode {int dummy; } ;
struct ubifs_info {int /*<<< orphan*/  tnc_mutex; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct ubifs_znode*) ; 
 int PTR_ERR (struct ubifs_znode*) ; 
 struct ubifs_znode* dirty_cow_bottom_up (struct ubifs_info*,struct ubifs_znode*) ; 
 struct ubifs_znode* lookup_znode (struct ubifs_info*,union ubifs_key*,int,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ubifs_dirty_idx_node(struct ubifs_info *c, union ubifs_key *key, int level,
			 int lnum, int offs)
{
	struct ubifs_znode *znode;
	int err = 0;

	mutex_lock(&c->tnc_mutex);
	znode = lookup_znode(c, key, level, lnum, offs);
	if (!znode)
		goto out_unlock;
	if (IS_ERR(znode)) {
		err = PTR_ERR(znode);
		goto out_unlock;
	}
	znode = dirty_cow_bottom_up(c, znode);
	if (IS_ERR(znode)) {
		err = PTR_ERR(znode);
		goto out_unlock;
	}

out_unlock:
	mutex_unlock(&c->tnc_mutex);
	return err;
}