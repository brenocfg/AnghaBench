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
 int /*<<< orphan*/  dprintk (char*) ; 
 int /*<<< orphan*/  svc_expkey_cache ; 
 int /*<<< orphan*/  svc_export_cache ; 

int
nfsd_export_init(void)
{
	int rv;
	dprintk("nfsd: initializing export module.\n");

	rv = cache_register(&svc_export_cache);
	if (rv)
		return rv;
	rv = cache_register(&svc_expkey_cache);
	if (rv)
		cache_unregister(&svc_export_cache);
	return rv;

}