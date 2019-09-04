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

bool IsHostIPAddress4(IP *ip)
{
	UINT a;
	// Validate arguments
	if (ip == NULL)
	{
		return false;
	}

	a = IPToUINT(ip);

	if (a == 0 || a == 0xffffffff)
	{
		return false;
	}

	return true;
}