#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_13__ {int /*<<< orphan*/  TrafficDiffList; int /*<<< orphan*/  TrafficLock; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  AssignedBridgeLicense; int /*<<< orphan*/  AssignedClientLicense; int /*<<< orphan*/  CurrentSessions; int /*<<< orphan*/  CurrentTcpConnections; int /*<<< orphan*/  HubList; } ;
struct TYPE_12__ {scalar_t__ Type; int /*<<< orphan*/  lock; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  LastCommTime; int /*<<< orphan*/  IpTable; int /*<<< orphan*/  MacHashTable; int /*<<< orphan*/  NumSessionsBridge; int /*<<< orphan*/  NumSessionsClient; int /*<<< orphan*/  SessionList; int /*<<< orphan*/  NumSessions; TYPE_1__* Name; } ;
struct TYPE_11__ {int /*<<< orphan*/  MyRandomKey; TYPE_4__* Cedar; } ;
struct TYPE_10__ {scalar_t__ Type; struct TYPE_10__* Name; struct TYPE_10__* HubName; int /*<<< orphan*/  Traffic; } ;
typedef  TYPE_1__ TRAFFIC_DIFF ;
typedef  TYPE_2__ SERVER ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_3__ HUB ;
typedef  TYPE_4__ CEDAR ;

/* Variables and functions */
 scalar_t__ Count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteAll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 scalar_t__ GetServerCapsInt (TYPE_2__*,char*) ; 
 scalar_t__ HASH_LIST_NUM (int /*<<< orphan*/ ) ; 
 void* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OutRpcTraffic (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OutRpcTrafficEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  PackAddIntEx (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PackAddStrEx (int /*<<< orphan*/ *,char*,TYPE_1__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PackAddTime64Ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  SHA1_SIZE ; 
 scalar_t__ SiGetPoint (TYPE_2__*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void SiCalledEnumHub(SERVER *s, PACK *p, PACK *req)
{
	UINT i;
	CEDAR *c;
	// Validate arguments
	if (s == NULL || p == NULL || req == NULL)
	{
		return;
	}


	c = s->Cedar;

	LockList(c->HubList);
	{
		UINT num = LIST_NUM(c->HubList);
		for (i = 0;i < num;i++)
		{
			HUB *h = LIST_DATA(c->HubList, i);
			Lock(h->lock);
			{
				PackAddStrEx(p, "HubName", h->Name, i, num);
				PackAddIntEx(p, "HubType", h->Type, i, num);
				PackAddIntEx(p, "NumSession", Count(h->NumSessions), i, num);

				PackAddIntEx(p, "NumSessions", LIST_NUM(h->SessionList), i, num);
				PackAddIntEx(p, "NumSessionsClient", Count(h->NumSessionsClient), i, num);
				PackAddIntEx(p, "NumSessionsBridge", Count(h->NumSessionsBridge), i, num);

				PackAddIntEx(p, "NumMacTables", HASH_LIST_NUM(h->MacHashTable), i, num);

				PackAddIntEx(p, "NumIpTables", LIST_NUM(h->IpTable), i, num);

				PackAddTime64Ex(p, "LastCommTime", h->LastCommTime, i, num);
				PackAddTime64Ex(p, "CreatedTime", h->CreatedTime, i, num);
			}
			Unlock(h->lock);
		}
	}
	UnlockList(c->HubList);

	PackAddInt(p, "Point", SiGetPoint(s));
	PackAddInt(p, "NumTcpConnections", Count(s->Cedar->CurrentTcpConnections));
	PackAddInt(p, "NumTotalSessions", Count(s->Cedar->CurrentSessions));
	PackAddInt(p, "MaxSessions", GetServerCapsInt(s, "i_max_sessions"));

	PackAddInt(p, "AssignedClientLicense", Count(s->Cedar->AssignedClientLicense));
	PackAddInt(p, "AssignedBridgeLicense", Count(s->Cedar->AssignedBridgeLicense));

	PackAddData(p, "RandomKey", s->MyRandomKey, SHA1_SIZE);


	Lock(c->TrafficLock);
	{
		OutRpcTraffic(p, c->Traffic);
	}
	Unlock(c->TrafficLock);

	LockList(c->TrafficDiffList);
	{
		UINT num = LIST_NUM(c->TrafficDiffList);
		UINT i;

		for (i = 0;i < num;i++)
		{
			TRAFFIC_DIFF *d = LIST_DATA(c->TrafficDiffList, i);

			PackAddIntEx(p, "TdType", d->Type, i, num);
			PackAddStrEx(p, "TdHubName", d->HubName, i, num);
			PackAddStrEx(p, "TdName", d->Name, i, num);

			OutRpcTrafficEx(&d->Traffic, p, i, num);

			Free(d->HubName);
			Free(d->Name);
			Free(d);
		}

		DeleteAll(c->TrafficDiffList);
	}
	UnlockList(c->TrafficDiffList);
}