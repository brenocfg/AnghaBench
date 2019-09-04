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
 scalar_t__ IsIP6 (int /*<<< orphan*/ *) ; 
 int IsSubnetMask4 (int /*<<< orphan*/ *) ; 
 int IsSubnetMask6 (int /*<<< orphan*/ *) ; 

bool IsSubnetMask(IP *ip)
{
	if (IsIP6(ip))
	{
		return IsSubnetMask6(ip);
	}
	else
	{
		return IsSubnetMask4(ip);
	}
}