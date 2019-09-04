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
 int /*<<< orphan*/  IPToStr4 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPToStr6 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IsIP6 (int /*<<< orphan*/ *) ; 

void IPToStr(char *str, UINT size, IP *ip)
{
	// Validate arguments
	if (str == NULL || ip == NULL)
	{
		return;
	}

	if (IsIP6(ip))
	{
		IPToStr6(str, size, ip);
	}
	else
	{
		IPToStr4(str, size, ip);
	}
}