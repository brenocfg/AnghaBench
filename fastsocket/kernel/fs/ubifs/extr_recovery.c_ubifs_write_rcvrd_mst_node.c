#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ubifs_info {TYPE_2__* rcvrd_mst_node; TYPE_1__* mst_node; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  UBIFS_MST_DIRTY ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int write_rcvrd_mst_node (struct ubifs_info*,TYPE_2__*) ; 

int ubifs_write_rcvrd_mst_node(struct ubifs_info *c)
{
	int err;

	if (!c->rcvrd_mst_node)
		return 0;
	c->rcvrd_mst_node->flags |= cpu_to_le32(UBIFS_MST_DIRTY);
	c->mst_node->flags |= cpu_to_le32(UBIFS_MST_DIRTY);
	err = write_rcvrd_mst_node(c, c->rcvrd_mst_node);
	if (err)
		return err;
	kfree(c->rcvrd_mst_node);
	c->rcvrd_mst_node = NULL;
	return 0;
}