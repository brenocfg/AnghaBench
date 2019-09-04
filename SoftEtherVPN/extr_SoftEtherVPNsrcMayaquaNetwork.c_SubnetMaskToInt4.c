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
 scalar_t__ CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IntToSubnetMask4 (int /*<<< orphan*/ *,int) ; 
 int IsIP4 (int /*<<< orphan*/ *) ; 

UINT SubnetMaskToInt4(IP *a)
{
	UINT i;
	// Validate arguments
	if (IsIP4(a) == false)
	{
		return 0;
	}

	for (i = 0;i <= 32;i++)
	{
		IP tmp;

		IntToSubnetMask4(&tmp, i);

		if (CmpIpAddr(a, &tmp) == 0)
		{
			return i;
		}
	}

	return 0;
}