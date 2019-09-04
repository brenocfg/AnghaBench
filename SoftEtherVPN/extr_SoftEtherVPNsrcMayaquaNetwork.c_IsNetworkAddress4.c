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
typedef  int UINT ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int IPToUINT (int /*<<< orphan*/ *) ; 
 int IsIP4 (int /*<<< orphan*/ *) ; 
 int IsSubnetMask4 (int /*<<< orphan*/ *) ; 

bool IsNetworkAddress4(IP *ip, IP *mask)
{
	UINT a, b;
	// Validate arguments
	if (ip == NULL || mask == NULL)
	{
		return false;
	}

	if (IsIP4(ip) == false || IsIP4(mask) == false)
	{
		return false;
	}

	if (IsSubnetMask4(mask) == false)
	{
		return false;
	}

	a = IPToUINT(ip);
	b = IPToUINT(mask);

	if ((a & b) == a)
	{
		return true;
	}

	return false;
}