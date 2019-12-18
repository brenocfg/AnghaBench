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
 int StrToIP6 (int /*<<< orphan*/ *,char*) ; 

bool IsIpStr6(char *str)
{
	IP ip;
	// Validate arguments
	if (str == NULL)
	{
		return false;
	}

	if (StrToIP6(&ip, str) == false)
	{
		return false;
	}

	return true;
}