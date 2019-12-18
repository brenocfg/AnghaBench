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
struct ubifs_info {int mst_offs; int mst_node_alsz; int leb_size; TYPE_1__* mst_node; int /*<<< orphan*/  highest_inum; scalar_t__ ro_media; } ;
struct TYPE_2__ {int /*<<< orphan*/  highest_inum; } ;

/* Variables and functions */
 int EROFS ; 
 int UBIFS_MST_LNUM ; 
 int UBIFS_MST_NODE_SZ ; 
 int /*<<< orphan*/  UBI_SHORTTERM ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int ubifs_leb_unmap (struct ubifs_info*,int) ; 
 int ubifs_write_node (struct ubifs_info*,TYPE_1__*,int,int,int,int /*<<< orphan*/ ) ; 

int ubifs_write_master(struct ubifs_info *c)
{
	int err, lnum, offs, len;

	if (c->ro_media)
		return -EROFS;

	lnum = UBIFS_MST_LNUM;
	offs = c->mst_offs + c->mst_node_alsz;
	len = UBIFS_MST_NODE_SZ;

	if (offs + UBIFS_MST_NODE_SZ > c->leb_size) {
		err = ubifs_leb_unmap(c, lnum);
		if (err)
			return err;
		offs = 0;
	}

	c->mst_offs = offs;
	c->mst_node->highest_inum = cpu_to_le64(c->highest_inum);

	err = ubifs_write_node(c, c->mst_node, len, lnum, offs, UBI_SHORTTERM);
	if (err)
		return err;

	lnum += 1;

	if (offs == 0) {
		err = ubifs_leb_unmap(c, lnum);
		if (err)
			return err;
	}
	err = ubifs_write_node(c, c->mst_node, len, lnum, offs, UBI_SHORTTERM);

	return err;
}