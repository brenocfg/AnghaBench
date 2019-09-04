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
typedef  int /*<<< orphan*/  DHCP_CLASSLESS_ROUTE_TABLE ;

/* Variables and functions */
 int ParseClasslessRouteTableStr (int /*<<< orphan*/ *,char*) ; 

bool CheckClasslessRouteTableStr(char *str)
{
	DHCP_CLASSLESS_ROUTE_TABLE d;

	// Validate arguments
	if (str == NULL)
	{
		return false;
	}

	return ParseClasslessRouteTableStr(&d, str);
}