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
 int /*<<< orphan*/  RPC_AUTH_GSS ; 
 int cache_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cache_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsc_cache ; 
 int /*<<< orphan*/  rsi_cache ; 
 int svc_auth_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svc_auth_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svcauthops_gss ; 

int
gss_svc_init(void)
{
	int rv = svc_auth_register(RPC_AUTH_GSS, &svcauthops_gss);
	if (rv)
		return rv;
	rv = cache_register(&rsc_cache);
	if (rv)
		goto out1;
	rv = cache_register(&rsi_cache);
	if (rv)
		goto out2;
	return 0;
out2:
	cache_unregister(&rsc_cache);
out1:
	svc_auth_unregister(RPC_AUTH_GSS);
	return rv;
}