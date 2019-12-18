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
struct exofs_i_info {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int SLAB_MEM_SPREAD ; 
 int SLAB_RECLAIM_ACCOUNT ; 
 int /*<<< orphan*/  exofs_init_once ; 
 int /*<<< orphan*/ * exofs_inode_cachep ; 
 int /*<<< orphan*/ * kmem_cache_create (char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int init_inodecache(void)
{
	exofs_inode_cachep = kmem_cache_create("exofs_inode_cache",
				sizeof(struct exofs_i_info), 0,
				SLAB_RECLAIM_ACCOUNT | SLAB_MEM_SPREAD,
				exofs_init_once);
	if (exofs_inode_cachep == NULL)
		return -ENOMEM;
	return 0;
}