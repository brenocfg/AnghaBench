#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_10__ {scalar_t__ Expires; int /*<<< orphan*/  HostName; int /*<<< orphan*/  IpAddress; } ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_1__ HOSTCACHE ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ Delete (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ EXPIRES_HOSTNAME ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/ * HostCacheList ; 
 int IsNetworkNameCacheEnabled () ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 TYPE_1__* Search (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ Tick64 () ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 TYPE_1__* ZeroMalloc (int) ; 

void AddHostCache(IP *ip, char *hostname)
{
	// Validate arguments
	if (ip == NULL || hostname == NULL)
	{
		return;
	}
	if (IsNetworkNameCacheEnabled() == false)
	{
		return;
	}

	LockList(HostCacheList);
	{
		HOSTCACHE t, *c;
		UINT i;
		LIST *o;

		Zero(&t, sizeof(t));
		Copy(&t.IpAddress, ip, sizeof(IP));

		c = Search(HostCacheList, &t);
		if (c == NULL)
		{
			c = ZeroMalloc(sizeof(HOSTCACHE));
			Copy(&c->IpAddress, ip, sizeof(IP));
			Add(HostCacheList, c);
		}

		StrCpy(c->HostName, sizeof(c->HostName), hostname);
		c->Expires = Tick64() + (UINT64)EXPIRES_HOSTNAME;

		o = NewListFast(NULL);

		for (i = 0;i < LIST_NUM(HostCacheList);i++)
		{
			HOSTCACHE *c = LIST_DATA(HostCacheList, i);

			if (c->Expires <= Tick64())
			{
				Add(o, c);
			}
		}

		for (i = 0;i < LIST_NUM(o);i++)
		{
			HOSTCACHE *c = LIST_DATA(o, i);

			if (Delete(HostCacheList, c))
			{
				Free(c);
			}
		}

		ReleaseList(o);
	}
	UnlockList(HostCacheList);
}