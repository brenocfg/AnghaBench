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
struct nilfs_inode_info {int /*<<< orphan*/  i_btnode_cache; int /*<<< orphan*/  i_bmap; } ;
struct inode {int /*<<< orphan*/  i_mapping; } ;

/* Variables and functions */
 struct nilfs_inode_info* NILFS_I (struct inode*) ; 
 int /*<<< orphan*/  invalidate_mapping_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nilfs_bmap_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_btnode_cache_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_inode_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void nilfs_mdt_clear(struct inode *inode)
{
	struct nilfs_inode_info *ii = NILFS_I(inode);

	invalidate_mapping_pages(inode->i_mapping, 0, -1);
	truncate_inode_pages(inode->i_mapping, 0);

	nilfs_bmap_clear(ii->i_bmap);
	nilfs_btnode_cache_clear(&ii->i_btnode_cache);
}