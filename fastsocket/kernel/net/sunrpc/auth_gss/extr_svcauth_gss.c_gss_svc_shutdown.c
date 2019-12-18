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
 int /*<<< orphan*/  cache_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rsc_cache ; 
 int /*<<< orphan*/  rsi_cache ; 
 int /*<<< orphan*/  svc_auth_unregister (int /*<<< orphan*/ ) ; 

void
gss_svc_shutdown(void)
{
	cache_unregister(&rsc_cache);
	cache_unregister(&rsi_cache);
	svc_auth_unregister(RPC_AUTH_GSS);
}