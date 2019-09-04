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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  IPToStr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IsSubnetMask (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SubnetMaskToInt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ToStr (char*,int /*<<< orphan*/ ) ; 

void MaskToStrEx(char *str, UINT size, IP *mask, bool always_full_address)
{
	// Validate arguments
	if (str == NULL || mask == NULL)
	{
		return;
	}

	if (always_full_address == false && IsSubnetMask(mask))
	{
		ToStr(str, SubnetMaskToInt(mask));
	}
	else
	{
		IPToStr(str, size, mask);
	}
}