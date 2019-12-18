#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct writeback_control {int range_cyclic; int /*<<< orphan*/  nr_to_write; int /*<<< orphan*/  sync_mode; } ;
struct TYPE_3__ {struct address_space* i_mapping; } ;
struct afs_vnode {TYPE_1__ vfs_inode; } ;
struct address_space {int /*<<< orphan*/  host; TYPE_2__* a_ops; } ;
struct TYPE_4__ {int (* writepages ) (struct address_space*,struct writeback_control*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  I_DIRTY_PAGES ; 
 int /*<<< orphan*/  LONG_MAX ; 
 int /*<<< orphan*/  WB_SYNC_ALL ; 
 int /*<<< orphan*/  __mark_inode_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,int) ; 
 int stub1 (struct address_space*,struct writeback_control*) ; 

int afs_writeback_all(struct afs_vnode *vnode)
{
	struct address_space *mapping = vnode->vfs_inode.i_mapping;
	struct writeback_control wbc = {
		.sync_mode	= WB_SYNC_ALL,
		.nr_to_write	= LONG_MAX,
		.range_cyclic	= 1,
	};
	int ret;

	_enter("");

	ret = mapping->a_ops->writepages(mapping, &wbc);
	__mark_inode_dirty(mapping->host, I_DIRTY_PAGES);

	_leave(" = %d", ret);
	return ret;
}