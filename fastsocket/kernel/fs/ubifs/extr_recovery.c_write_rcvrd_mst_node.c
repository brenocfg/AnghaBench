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
struct ubifs_mst_node {int /*<<< orphan*/  flags; } ;
struct ubifs_info {int mst_node_alsz; int /*<<< orphan*/  ubi; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int UBIFS_MST_LNUM ; 
 int /*<<< orphan*/  UBIFS_MST_NODE_SZ ; 
 int /*<<< orphan*/  UBIFS_MST_RCVRY ; 
 int /*<<< orphan*/  UBI_SHORTTERM ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbg_rcvry (char*) ; 
 int ubi_leb_change (int /*<<< orphan*/ ,int,struct ubifs_mst_node*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_prepare_node (struct ubifs_info*,struct ubifs_mst_node*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int write_rcvrd_mst_node(struct ubifs_info *c,
				struct ubifs_mst_node *mst)
{
	int err = 0, lnum = UBIFS_MST_LNUM, sz = c->mst_node_alsz;
	__le32 save_flags;

	dbg_rcvry("recovery");

	save_flags = mst->flags;
	mst->flags |= cpu_to_le32(UBIFS_MST_RCVRY);

	ubifs_prepare_node(c, mst, UBIFS_MST_NODE_SZ, 1);
	err = ubi_leb_change(c->ubi, lnum, mst, sz, UBI_SHORTTERM);
	if (err)
		goto out;
	err = ubi_leb_change(c->ubi, lnum + 1, mst, sz, UBI_SHORTTERM);
	if (err)
		goto out;
out:
	mst->flags = save_flags;
	return err;
}