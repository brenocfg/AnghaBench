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
struct efs_inode_info {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int SLAB_MEM_SPREAD ; 
 int SLAB_RECLAIM_ACCOUNT ; 
 int /*<<< orphan*/ * efs_inode_cachep ; 
 int /*<<< orphan*/  init_once ; 
 int /*<<< orphan*/ * kmem_cache_create (char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_inodecache(void)
{
	efs_inode_cachep = kmem_cache_create("efs_inode_cache",
				sizeof(struct efs_inode_info),
				0, SLAB_RECLAIM_ACCOUNT|SLAB_MEM_SPREAD,
				init_once);
	if (efs_inode_cachep == NULL)
		return -ENOMEM;
	return 0;
}