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

/* Variables and functions */
 int fscache_register_netfs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v9fs_cache_netfs ; 
 int v9fs_init_vcookiecache () ; 

int __v9fs_cache_register(void)
{
	int ret;
	ret = v9fs_init_vcookiecache();
	if (ret < 0)
		return ret;

	return fscache_register_netfs(&v9fs_cache_netfs);
}