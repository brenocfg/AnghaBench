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
typedef  scalar_t__ Oid ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  InitializeCaches () ; 
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,char const*) ; 
 scalar_t__ get_namespace_oid (char const*,int) ; 

__attribute__((used)) static void
CachedNamespaceLookup(const char *nspname, Oid *cachedOid)
{
	/* force callbacks to be registered, so we always get notified upon changes */
	InitializeCaches();

	if (*cachedOid == InvalidOid)
	{
		*cachedOid = get_namespace_oid(nspname, true);

		if (*cachedOid == InvalidOid)
		{
			ereport(ERROR, (errmsg(
								"cache lookup failed for namespace %s, called too early?",
								nspname)));
		}
	}
}