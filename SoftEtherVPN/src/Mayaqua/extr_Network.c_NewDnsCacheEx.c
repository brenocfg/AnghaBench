#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_6__ {char* HostName; int /*<<< orphan*/  IpAddress; } ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_1__ DNSCACHE ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 char* CopyStr (char*) ; 
 int /*<<< orphan*/  DnsCache ; 
 int /*<<< orphan*/  GenDnsCacheKeyName (char*,int,char*,int) ; 
 int IsNetworkNameCacheEnabled () ; 
 int /*<<< orphan*/  LockDnsCache () ; 
 int MAX_PATH ; 
 TYPE_1__* Search (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  UnlockDnsCache () ; 
 TYPE_1__* ZeroMalloc (int) ; 

void NewDnsCacheEx(char *hostname, IP *ip, bool ipv6)
{
	DNSCACHE *c;
	char tmp[MAX_PATH];
	// Validate arguments
	if (hostname == NULL || ip == NULL)
	{
		return;
	}

	if (IsNetworkNameCacheEnabled() == false)
	{
		return;
	}

	GenDnsCacheKeyName(tmp, sizeof(tmp), hostname, ipv6);

	LockDnsCache();
	{
		DNSCACHE t;

		// Search for anything matches to the hostname first
		t.HostName = tmp;
		c = Search(DnsCache, &t);

		if (c == NULL)
		{
			// Newly register
			c = ZeroMalloc(sizeof(DNSCACHE));
			c->HostName = CopyStr(tmp);

			Copy(&c->IpAddress, ip, sizeof(IP));

			Add(DnsCache, c);
		}
		else
		{
			// Update
			Copy(&c->IpAddress, ip, sizeof(IP));
		}
	}
	UnlockDnsCache();
}