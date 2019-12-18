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
 scalar_t__ CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPAnd4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int IsIP4 (int /*<<< orphan*/ *) ; 

bool IsInSameNetwork4(IP *a1, IP *a2, IP *subnet)
{
	IP net1, net2;
	// Validate arguments
	if (IsIP4(a1) == false || IsIP4(a2) == false || IsIP4(subnet) == false)
	{
		return false;
	}

	IPAnd4(&net1, a1, subnet);
	IPAnd4(&net2, a2, subnet);

	if (CmpIpAddr(&net1, &net2) == 0)
	{
		return true;
	}

	return false;
}