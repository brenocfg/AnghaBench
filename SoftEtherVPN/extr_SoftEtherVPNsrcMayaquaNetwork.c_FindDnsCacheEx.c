#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_5__ {char* HostName; } ;
typedef  TYPE_1__ DNSCACHE ;

/* Variables and functions */
 int /*<<< orphan*/  DnsCache ; 
 int /*<<< orphan*/  GenDnsCacheKeyName (char*,int,char*,int) ; 
 int /*<<< orphan*/  LockDnsCache () ; 
 int MAX_SIZE ; 
 TYPE_1__* Search (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  UnlockDnsCache () ; 

DNSCACHE *FindDnsCacheEx(char *hostname, bool ipv6)
{
	DNSCACHE *c;
	char tmp[MAX_SIZE];
	if (hostname == NULL)
	{
		return NULL;
	}

	GenDnsCacheKeyName(tmp, sizeof(tmp), hostname, ipv6);

	LockDnsCache();
	{
		DNSCACHE t;
		t.HostName = tmp;
		c = Search(DnsCache, &t);
	}
	UnlockDnsCache();

	return c;
}