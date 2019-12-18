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
struct the_nilfs {struct inode* ns_gc_dat; } ;
struct nilfs_inode_info {int /*<<< orphan*/  i_btnode_cache; scalar_t__ i_flags; } ;
struct inode {int /*<<< orphan*/ * i_mapping; int /*<<< orphan*/  i_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_CLEAR ; 
 struct nilfs_inode_info* NILFS_I (struct inode*) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void nilfs_clear_gcdat_inode(struct the_nilfs *nilfs)
{
	struct inode *gcdat = nilfs->ns_gc_dat;
	struct nilfs_inode_info *gii = NILFS_I(gcdat);

	gcdat->i_state = I_CLEAR;
	gii->i_flags = 0;

	truncate_inode_pages(gcdat->i_mapping, 0);
	truncate_inode_pages(&gii->i_btnode_cache, 0);
}