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
typedef  int /*<<< orphan*/  nstat_provider_filter ;
typedef  int /*<<< orphan*/  nstat_provider_cookie_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int nstat_tcpudp_reporting_allowed (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
nstat_tcp_reporting_allowed(nstat_provider_cookie_t cookie, nstat_provider_filter *filter)
{
	return nstat_tcpudp_reporting_allowed(cookie, filter, FALSE);
}