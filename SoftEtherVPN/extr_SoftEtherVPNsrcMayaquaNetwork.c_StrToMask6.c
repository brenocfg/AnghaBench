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
 int /*<<< orphan*/  IntToSubnetMask6 (int /*<<< orphan*/ *,int) ; 
 int IsIP6 (int /*<<< orphan*/ *) ; 
 scalar_t__ IsNum (char*) ; 
 int StrToIP (int /*<<< orphan*/ *,char*) ; 
 int ToInt (char*) ; 

bool StrToMask6(IP *mask, char *str)
{
	// Validate arguments
	if (mask == NULL || str == NULL)
	{
		return false;
	}

	if (str[0] == '/')
	{
		str++;
	}

	if (IsNum(str))
	{
		UINT n = ToInt(str);

		if (n <= 128)
		{
			IntToSubnetMask6(mask, n);
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		if (StrToIP(mask, str) == false)
		{
			return false;
		}
		else
		{
			return IsIP6(mask);
		}
	}
}