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
struct nilfs_bmap {scalar_t__ b_state; int /*<<< orphan*/  b_last_allocated_ptr; scalar_t__ b_last_allocated_key; int /*<<< orphan*/  b_ptr_type; int /*<<< orphan*/ * b_inode; int /*<<< orphan*/  b_sem; int /*<<< orphan*/  b_u; } ;
struct TYPE_2__ {int /*<<< orphan*/  vfs_inode; } ;

/* Variables and functions */
 TYPE_1__* NILFS_BMAP_I (struct nilfs_bmap*) ; 
 int /*<<< orphan*/  NILFS_BMAP_INVALID_PTR ; 
 int /*<<< orphan*/  NILFS_BMAP_PTR_U ; 
 int /*<<< orphan*/  NILFS_BMAP_SIZE ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_btree_init_gc (struct nilfs_bmap*) ; 

void nilfs_bmap_init_gc(struct nilfs_bmap *bmap)
{
	memset(&bmap->b_u, 0, NILFS_BMAP_SIZE);
	init_rwsem(&bmap->b_sem);
	bmap->b_inode = &NILFS_BMAP_I(bmap)->vfs_inode;
	bmap->b_ptr_type = NILFS_BMAP_PTR_U;
	bmap->b_last_allocated_key = 0;
	bmap->b_last_allocated_ptr = NILFS_BMAP_INVALID_PTR;
	bmap->b_state = 0;
	nilfs_btree_init_gc(bmap);
}