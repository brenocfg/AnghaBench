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
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_5__ {char* HostName; int /*<<< orphan*/  IpAddress; } ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_1__ HOSTCACHE ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  HostCacheList ; 
 int IsEmptyStr (char*) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 TYPE_1__* Search (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

bool GetHostCache(char *hostname, UINT size, IP *ip)
{
	bool ret;
	// Validate arguments
	if (hostname == NULL || ip == NULL)
	{
		return false;
	}

	ret = false;

	LockList(HostCacheList);
	{
		HOSTCACHE t, *c;
		Zero(&t, sizeof(t));
		Copy(&t.IpAddress, ip, sizeof(IP));

		c = Search(HostCacheList, &t);
		if (c != NULL)
		{
			if (IsEmptyStr(c->HostName) == false)
			{
				ret = true;
				StrCpy(hostname, size, c->HostName);
			}
			else
			{
				ret = true;
				StrCpy(hostname, size, "");
			}
		}
	}
	UnlockList(HostCacheList);

	return ret;
}