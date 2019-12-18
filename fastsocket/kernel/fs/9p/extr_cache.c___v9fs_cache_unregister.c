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
 int /*<<< orphan*/  fscache_unregister_netfs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v9fs_cache_netfs ; 
 int /*<<< orphan*/  v9fs_destroy_vcookiecache () ; 

void __v9fs_cache_unregister(void)
{
	v9fs_destroy_vcookiecache();
	fscache_unregister_netfs(&v9fs_cache_netfs);
}