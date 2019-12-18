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
struct nilfs_inode_info {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SLAB_RECLAIM_ACCOUNT ; 
 int /*<<< orphan*/  init_once ; 
 int /*<<< orphan*/ * kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nilfs_inode_cachep ; 

__attribute__((used)) static int nilfs_init_inode_cache(void)
{
	nilfs_inode_cachep = kmem_cache_create("nilfs2_inode_cache",
					       sizeof(struct nilfs_inode_info),
					       0, SLAB_RECLAIM_ACCOUNT,
					       init_once);

	return (nilfs_inode_cachep == NULL) ? -ENOMEM : 0;
}