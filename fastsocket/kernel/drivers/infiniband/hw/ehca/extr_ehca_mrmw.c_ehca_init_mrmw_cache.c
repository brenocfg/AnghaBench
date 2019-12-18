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
struct ehca_mw {int dummy; } ;
struct ehca_mr {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 void* kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mr_cache ; 
 void* mw_cache ; 

int ehca_init_mrmw_cache(void)
{
	mr_cache = kmem_cache_create("ehca_cache_mr",
				     sizeof(struct ehca_mr), 0,
				     SLAB_HWCACHE_ALIGN,
				     NULL);
	if (!mr_cache)
		return -ENOMEM;
	mw_cache = kmem_cache_create("ehca_cache_mw",
				     sizeof(struct ehca_mw), 0,
				     SLAB_HWCACHE_ALIGN,
				     NULL);
	if (!mw_cache) {
		kmem_cache_destroy(mr_cache);
		mr_cache = NULL;
		return -ENOMEM;
	}
	return 0;
}