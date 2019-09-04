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
 int /*<<< orphan*/  IPToUINT (int /*<<< orphan*/ *) ; 
 int IsIP4 (int /*<<< orphan*/ *) ; 
 int ParseIpAndSubnetMask46 (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

bool ParseIpAndSubnetMask4(char *src, UINT *ip, UINT *mask)
{
	IP ip2, mask2;
	// Validate arguments
	if (src == NULL)
	{
		return false;
	}

	if (ParseIpAndSubnetMask46(src, &ip2, &mask2) == false)
	{
		return false;
	}

	if (IsIP4(&ip2) == false)
	{
		return false;
	}

	if (ip != NULL)
	{
		*ip = IPToUINT(&ip2);
	}

	if (mask != NULL)
	{
		*mask = IPToUINT(&mask2);
	}

	return true;
}