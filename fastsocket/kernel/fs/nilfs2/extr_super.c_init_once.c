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
struct nilfs_inode_info {int /*<<< orphan*/  vfs_inode; int /*<<< orphan*/  i_bmap_union; struct nilfs_bmap* i_bmap; int /*<<< orphan*/  i_btnode_cache; int /*<<< orphan*/  xattr_sem; int /*<<< orphan*/  i_dirty; } ;
struct nilfs_bmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_init_once (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nilfs_btnode_cache_init_once (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_once(void *obj)
{
	struct nilfs_inode_info *ii = obj;

	INIT_LIST_HEAD(&ii->i_dirty);
#ifdef CONFIG_NILFS_XATTR
	init_rwsem(&ii->xattr_sem);
#endif
	nilfs_btnode_cache_init_once(&ii->i_btnode_cache);
	ii->i_bmap = (struct nilfs_bmap *)&ii->i_bmap_union;
	inode_init_once(&ii->vfs_inode);
}