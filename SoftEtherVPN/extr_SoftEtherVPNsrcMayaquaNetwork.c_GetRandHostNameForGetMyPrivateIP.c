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
typedef  size_t UINT ;

/* Variables and functions */
 size_t Rand32 () ; 

char *GetRandHostNameForGetMyPrivateIP()
{
	char *hosts[] =
	{
		"www.microsoft.com",
		"www.yahoo.com",
		"www.bing.com",
	};
	UINT num_hosts = 3;

	return hosts[Rand32() % num_hosts];
}