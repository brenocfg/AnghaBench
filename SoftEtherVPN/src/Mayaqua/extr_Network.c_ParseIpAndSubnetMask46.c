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
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 scalar_t__ IsIP4 (int /*<<< orphan*/ *) ; 
 int IsSubnetMask4 (int /*<<< orphan*/ *) ; 
 int IsSubnetMask6 (int /*<<< orphan*/ *) ; 
 int ParseIpAndMask46 (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool ParseIpAndSubnetMask46(char *src, IP *ip, IP *mask)
{
	// Validate arguments
	if (src == NULL || ip == NULL || mask == NULL)
	{
		return false;
	}

	if (ParseIpAndMask46(src, ip, mask) == false)
	{
		return false;
	}

	if (IsIP4(ip))
	{
		return IsSubnetMask4(mask);
	}
	else
	{
		return IsSubnetMask6(mask);
	}
}