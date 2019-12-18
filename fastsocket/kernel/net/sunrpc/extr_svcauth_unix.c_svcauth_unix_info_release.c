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
struct svc_xprt {struct ip_map* xpt_auth_cache; } ;
struct ip_map {int /*<<< orphan*/  h; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_put (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_map_cache ; 

void
svcauth_unix_info_release(struct svc_xprt *xpt)
{
	struct ip_map *ipm;

	ipm = xpt->xpt_auth_cache;
	if (ipm != NULL)
		cache_put(&ipm->h, &ip_map_cache);
}