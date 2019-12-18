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
struct dlm_lock {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 int /*<<< orphan*/ * dlm_lock_cache ; 
 int /*<<< orphan*/ * kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int dlm_init_lock_cache(void)
{
	dlm_lock_cache = kmem_cache_create("o2dlm_lock",
					   sizeof(struct dlm_lock),
					   0, SLAB_HWCACHE_ALIGN, NULL);
	if (dlm_lock_cache == NULL)
		return -ENOMEM;
	return 0;
}