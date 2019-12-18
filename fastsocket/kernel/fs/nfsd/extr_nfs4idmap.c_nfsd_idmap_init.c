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
 int cache_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idtoname_cache ; 
 int /*<<< orphan*/  nametoid_cache ; 

int
nfsd_idmap_init(void)
{
	int rv;

	rv = cache_register(&idtoname_cache);
	if (rv)
		return rv;
	rv = cache_register(&nametoid_cache);
	if (rv)
		cache_unregister(&idtoname_cache);
	return rv;
}