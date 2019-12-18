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
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  DHCP_CLASSLESS_ROUTE_TABLE ;

/* Variables and functions */
 int /*<<< orphan*/  BuildClasslessRouteTableStr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ParseClasslessRouteTableStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

bool NormalizeClasslessRouteTableStr(char *dst, UINT dst_size, char *src)
{
	DHCP_CLASSLESS_ROUTE_TABLE t;
	// Validate arguments
	if (dst == NULL || src == NULL)
	{
		return false;
	}

	Zero(&t, sizeof(t));
	if (ParseClasslessRouteTableStr(&t, src))
	{
		BuildClasslessRouteTableStr(dst, dst_size, &t);

		return true;
	}

	return false;
}