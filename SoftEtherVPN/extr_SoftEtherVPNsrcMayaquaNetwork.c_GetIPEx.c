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
 int GetIP4 (int /*<<< orphan*/ *,char*) ; 
 int GetIP6 (int /*<<< orphan*/ *,char*) ; 

bool GetIPEx(IP *ip, char *hostname, bool ipv6)
{
	if (ipv6 == false)
	{
		return GetIP4(ip, hostname);
	}
	else
	{
		return GetIP6(ip, hostname);
	}
}