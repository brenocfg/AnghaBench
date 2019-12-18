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
struct ubifs_info {int /*<<< orphan*/  tnc_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int is_idx_node_in_tnc (struct ubifs_info*,union ubifs_key*,int,int,int) ; 
 int is_leaf_node_in_tnc (struct ubifs_info*,union ubifs_key*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ubifs_tnc_has_node(struct ubifs_info *c, union ubifs_key *key, int level,
		       int lnum, int offs, int is_idx)
{
	int err;

	mutex_lock(&c->tnc_mutex);
	if (is_idx) {
		err = is_idx_node_in_tnc(c, key, level, lnum, offs);
		if (err < 0)
			goto out_unlock;
		if (err == 1)
			/* The index node was found but it was dirty */
			err = 0;
		else if (err == 2)
			/* The index node was found and it was clean */
			err = 1;
		else
			BUG_ON(err != 0);
	} else
		err = is_leaf_node_in_tnc(c, key, lnum, offs);

out_unlock:
	mutex_unlock(&c->tnc_mutex);
	return err;
}