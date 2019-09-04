#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_3__ {int /*<<< orphan*/  IpAddress; } ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_1__ DNSCACHE ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 TYPE_1__* FindDnsCache (char*) ; 
 int /*<<< orphan*/  GenDnsCacheKeyName (char*,int,char*,int) ; 
 int MAX_SIZE ; 

bool QueryDnsCacheEx(IP *ip, char *hostname, bool ipv6)
{
	DNSCACHE *c;
	char tmp[MAX_SIZE];
	// Validate arguments
	if (ip == NULL || hostname == NULL)
	{
		return false;
	}

	GenDnsCacheKeyName(tmp, sizeof(tmp), hostname, ipv6);

	c = FindDnsCache(tmp);
	if (c == NULL)
	{
		return false;
	}

	Copy(ip, &c->IpAddress, sizeof(IP));

	return true;
}