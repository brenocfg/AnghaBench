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
 int IsInSameNetwork6 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int StrToIP6 (int /*<<< orphan*/ *,char*) ; 
 int StrToMask6 (int /*<<< orphan*/ *,char*) ; 

bool IsInSameNetwork6ByStr(char *ip1, char *ip2, char *subnet)
{
	IP p1, p2, s;

	if (StrToIP6(&p1, ip1) == false)
	{
		return false;
	}

	if (StrToIP6(&p2, ip2) == false)
	{
		return false;
	}

	if (StrToMask6(&s, subnet) == false)
	{
		return false;
	}

	return IsInSameNetwork6(&p1, &p2, &s);
}