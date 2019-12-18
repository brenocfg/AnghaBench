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
struct ubifs_zbranch {int /*<<< orphan*/  len; int /*<<< orphan*/  offs; int /*<<< orphan*/  lnum; } ;
struct ubifs_info {scalar_t__ replaying; } ;
struct ubifs_dent_node {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBGKEY (union ubifs_key const*) ; 
 int /*<<< orphan*/  dbg_mnt (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_tnc (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  key_read (struct ubifs_info*,int /*<<< orphan*/ *,union ubifs_key*) ; 
 int /*<<< orphan*/  key_type (struct ubifs_info*,union ubifs_key const*) ; 
 scalar_t__ keys_cmp (struct ubifs_info*,union ubifs_key const*,union ubifs_key*) ; 
 int try_read_node (struct ubifs_info*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fallible_read_node(struct ubifs_info *c, const union ubifs_key *key,
			      struct ubifs_zbranch *zbr, void *node)
{
	int ret;

	dbg_tnc("LEB %d:%d, key %s", zbr->lnum, zbr->offs, DBGKEY(key));

	ret = try_read_node(c, node, key_type(c, key), zbr->len, zbr->lnum,
			    zbr->offs);
	if (ret == 1) {
		union ubifs_key node_key;
		struct ubifs_dent_node *dent = node;

		/* All nodes have key in the same place */
		key_read(c, &dent->key, &node_key);
		if (keys_cmp(c, key, &node_key) != 0)
			ret = 0;
	}
	if (ret == 0 && c->replaying)
		dbg_mnt("dangling branch LEB %d:%d len %d, key %s",
			zbr->lnum, zbr->offs, zbr->len, DBGKEY(key));
	return ret;
}