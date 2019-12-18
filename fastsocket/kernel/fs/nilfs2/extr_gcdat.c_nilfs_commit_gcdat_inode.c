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
struct the_nilfs {struct inode* ns_gc_dat; struct inode* ns_dat; } ;
struct address_space {int dummy; } ;
struct nilfs_inode_info {int i_state; struct address_space i_btnode_cache; int /*<<< orphan*/  i_bmap; int /*<<< orphan*/  i_flags; } ;
struct inode {int /*<<< orphan*/  i_blocks; struct address_space* i_mapping; } ;
struct TYPE_2__ {int /*<<< orphan*/  mi_sem; } ;

/* Variables and functions */
 struct nilfs_inode_info* NILFS_I (struct inode*) ; 
 int NILFS_I_GCDAT ; 
 TYPE_1__* NILFS_MDT (struct inode*) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_bmap_commit_gcdat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_clear_dirty_pages (struct address_space*) ; 
 int /*<<< orphan*/  nilfs_copy_back_pages (struct address_space*,struct address_space*) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void nilfs_commit_gcdat_inode(struct the_nilfs *nilfs)
{
	struct inode *dat = nilfs->ns_dat, *gcdat = nilfs->ns_gc_dat;
	struct nilfs_inode_info *dii = NILFS_I(dat), *gii = NILFS_I(gcdat);
	struct address_space *mapping = dat->i_mapping;
	struct address_space *gmapping = gcdat->i_mapping;

	down_write(&NILFS_MDT(dat)->mi_sem);
	dat->i_blocks = gcdat->i_blocks;
	dii->i_flags = gii->i_flags;
	dii->i_state = gii->i_state & ~(1 << NILFS_I_GCDAT);

	nilfs_bmap_commit_gcdat(gii->i_bmap, dii->i_bmap);

	nilfs_clear_dirty_pages(mapping);
	nilfs_copy_back_pages(mapping, gmapping);
	/* note: mdt dirty flags should be cleared by segctor. */

	nilfs_clear_dirty_pages(&dii->i_btnode_cache);
	nilfs_copy_back_pages(&dii->i_btnode_cache, &gii->i_btnode_cache);

	up_write(&NILFS_MDT(dat)->mi_sem);
}