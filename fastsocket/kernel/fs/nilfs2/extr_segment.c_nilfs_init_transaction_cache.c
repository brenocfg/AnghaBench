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
struct nilfs_transaction_info {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SLAB_RECLAIM_ACCOUNT ; 
 int /*<<< orphan*/ * kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nilfs_transaction_cachep ; 

int nilfs_init_transaction_cache(void)
{
	nilfs_transaction_cachep =
		kmem_cache_create("nilfs2_transaction_cache",
				  sizeof(struct nilfs_transaction_info),
				  0, SLAB_RECLAIM_ACCOUNT, NULL);
	return (nilfs_transaction_cachep == NULL) ? -ENOMEM : 0;
}