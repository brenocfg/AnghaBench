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
struct ubifs_zbranch {scalar_t__ len; scalar_t__ leaf; int /*<<< orphan*/  key; } ;
struct ubifs_info {int dummy; } ;

/* Variables and functions */
 int is_hash_key (struct ubifs_info*,int /*<<< orphan*/ *) ; 
 int lnc_add (struct ubifs_info*,struct ubifs_zbranch*,void*) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 int ubifs_tnc_read_node (struct ubifs_info*,struct ubifs_zbranch*,void*) ; 

__attribute__((used)) static int tnc_read_node_nm(struct ubifs_info *c, struct ubifs_zbranch *zbr,
			    void *node)
{
	int err;

	ubifs_assert(is_hash_key(c, &zbr->key));

	if (zbr->leaf) {
		/* Read from the leaf node cache */
		ubifs_assert(zbr->len != 0);
		memcpy(node, zbr->leaf, zbr->len);
		return 0;
	}

	err = ubifs_tnc_read_node(c, zbr, node);
	if (err)
		return err;

	/* Add the node to the leaf node cache */
	err = lnc_add(c, zbr, node);
	return err;
}