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
struct ubifs_znode {struct ubifs_znode* parent; scalar_t__ iip; } ;

/* Variables and functions */
 int /*<<< orphan*/  ubifs_assert (struct ubifs_znode*) ; 
 struct ubifs_znode* ubifs_tnc_find_child (struct ubifs_znode*,scalar_t__) ; 
 struct ubifs_znode* ubifs_tnc_postorder_first (struct ubifs_znode*) ; 
 scalar_t__ unlikely (int) ; 

struct ubifs_znode *ubifs_tnc_postorder_next(struct ubifs_znode *znode)
{
	struct ubifs_znode *zn;

	ubifs_assert(znode);
	if (unlikely(!znode->parent))
		return NULL;

	/* Switch to the next index in the parent */
	zn = ubifs_tnc_find_child(znode->parent, znode->iip + 1);
	if (!zn)
		/* This is in fact the last child, return parent */
		return znode->parent;

	/* Go to the first znode in this new subtree */
	return ubifs_tnc_postorder_first(zn);
}