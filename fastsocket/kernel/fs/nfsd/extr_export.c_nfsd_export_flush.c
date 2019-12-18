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
 int /*<<< orphan*/  cache_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exp_writelock () ; 
 int /*<<< orphan*/  exp_writeunlock () ; 
 int /*<<< orphan*/  svc_expkey_cache ; 
 int /*<<< orphan*/  svc_export_cache ; 

void
nfsd_export_flush(void)
{
	exp_writelock();
	cache_purge(&svc_expkey_cache);
	cache_purge(&svc_export_cache);
	exp_writeunlock();
}