#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_7__ ;
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_4__ ;
typedef  struct TYPE_32__   TYPE_3__ ;
typedef  struct TYPE_31__   TYPE_2__ ;
typedef  struct TYPE_30__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  hubname ;
struct TYPE_31__ {TYPE_1__* Group; int /*<<< orphan*/  lock; int /*<<< orphan*/  Traffic; } ;
typedef  TYPE_2__ USER ;
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_35__ {int /*<<< orphan*/ * HubList; scalar_t__ AssignedClientLicense; scalar_t__ AssignedBridgeLicense; int /*<<< orphan*/  TrafficLock; int /*<<< orphan*/  Traffic; scalar_t__ CurrentTcpConnections; scalar_t__ CurrentSessions; } ;
struct TYPE_34__ {scalar_t__ SystemId; int /*<<< orphan*/ * RandomKey; void* AssignedClientLicense; void* AssignedBridgeLicense; int /*<<< orphan*/  Traffic; void* NumTcpConnections; void* MaxSessions; void* NumSessions; void* Point; int /*<<< orphan*/  hostname; int /*<<< orphan*/ * HubList; scalar_t__ Me; } ;
struct TYPE_33__ {int DynamicHub; char* Name; scalar_t__ Type; int Offline; scalar_t__ LastCommTime; int /*<<< orphan*/  TrafficLock; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  lock; scalar_t__ NumMacTables; scalar_t__ NumIpTables; scalar_t__ NumSessionsBridge; scalar_t__ NumSessionsClient; scalar_t__ NumSessions; TYPE_6__* FarmMember; int /*<<< orphan*/ * IpTable; int /*<<< orphan*/  MacHashTable; int /*<<< orphan*/ * SessionList; } ;
struct TYPE_32__ {int /*<<< orphan*/ * FarmMemberList; int /*<<< orphan*/  MyRandomKey; TYPE_7__* Cedar; } ;
struct TYPE_30__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  Traffic; } ;
typedef  int /*<<< orphan*/  TRAFFIC ;
typedef  TYPE_3__ SERVER ;
typedef  int /*<<< orphan*/  PACK ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_4__ HUB_LIST ;
typedef  TYPE_4__ HUB ;
typedef  TYPE_6__ FARM_MEMBER ;
typedef  TYPE_7__ CEDAR ;

/* Variables and functions */
 TYPE_2__* AcGetUser (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  AcLock (TYPE_4__*) ; 
 int /*<<< orphan*/  AcUnlock (TYPE_4__*) ; 
 int /*<<< orphan*/  Add (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  AddTraffic (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ Count (scalar_t__) ; 
 int /*<<< orphan*/  Debug (char*,char*,...) ; 
 int /*<<< orphan*/  Delete (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  DeleteAll (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (TYPE_4__*) ; 
 int /*<<< orphan*/  FreePack (int /*<<< orphan*/ *) ; 
 TYPE_4__* GetHub (TYPE_7__*,char*) ; 
 void* GetServerCapsInt (TYPE_3__*,char*) ; 
 scalar_t__ HASH_LIST_NUM (int /*<<< orphan*/ ) ; 
 scalar_t__ HUB_TYPE_FARM_DYNAMIC ; 
 scalar_t__ HUB_TYPE_FARM_STATIC ; 
 int /*<<< orphan*/  InRpcTraffic (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InRpcTrafficEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int IsZero (int /*<<< orphan*/ *,int) ; 
 void* LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHashList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewPack () ; 
 int /*<<< orphan*/  PackAddDataEx (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  PackAddInt64Ex (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  PackGetData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int PackGetDataSize (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PackGetIndexCount (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PackGetInt64 (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PackGetInt64Ex (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 scalar_t__ PackGetIntEx (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  PackGetStrEx (int /*<<< orphan*/ *,char*,char*,int,scalar_t__) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_4__*) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ReleaseUser (TYPE_2__*) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  SiCallDeleteHub (TYPE_3__*,TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/ * SiCallTask (TYPE_6__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SiDelHubCreateHistory (TYPE_3__*,char*) ; 
 void* SiGetPoint (TYPE_3__*) ; 
 int SiIsHubRegistedOnCreateHistory (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 scalar_t__ TRAFFIC_DIFF_HUB ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHashList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ *) ; 
 TYPE_4__* ZeroMalloc (int) ; 

void SiCallEnumHub(SERVER *s, FARM_MEMBER *f)
{
	CEDAR *c;
	// Validate arguments
	if (s == NULL || f == NULL)
	{
		return;
	}

	c = s->Cedar;

	if (f->Me)
	{

		// Enumerate local HUBs
		LockList(f->HubList);
		{
			// For a local HUB, re-enumerate by erasing all STATIC HUB list once first
			UINT i;
			LIST *o = NewListFast(NULL);
			for (i = 0;i < LIST_NUM(f->HubList);i++)
			{
				HUB_LIST *h = LIST_DATA(f->HubList, i);
				if (h->DynamicHub == false)
				{
					Add(o, h);
				}
			}

			// Clear all the STATIC HUB
			for (i = 0;i < LIST_NUM(o);i++)
			{
				HUB_LIST *h = LIST_DATA(o, i);
				Free(h);
				Delete(f->HubList, h);
			}
			ReleaseList(o);

			// Second, stop DYNAMIC HUBs without user
			o = NewListFast(NULL);
			for (i = 0;i < LIST_NUM(f->HubList);i++)
			{
				HUB_LIST *h = LIST_DATA(f->HubList, i);
				if (h->DynamicHub == true)
				{
					LockList(c->HubList);
					{
						HUB *hub = GetHub(s->Cedar, h->Name);
						if (hub != NULL)
						{
							if (Count(hub->NumSessions) == 0 || hub->Type != HUB_TYPE_FARM_DYNAMIC)
							{
								Add(o, h);
							}
							ReleaseHub(hub);
						}
					}
					UnlockList(c->HubList);
				}
			}

			for (i = 0;i < LIST_NUM(o);i++)
			{
				HUB_LIST *h = LIST_DATA(o, i);
				Debug("Delete HUB: %s\n", h->Name);
				Free(h);
				Delete(f->HubList, h);
			}

			ReleaseList(o);

			// Set the enumeration results
			LockList(c->HubList);
			{
				for (i = 0;i < LIST_NUM(c->HubList);i++)
				{
					HUB *h = LIST_DATA(c->HubList, i);
					if (h->Offline == false)
					{
						if (h->Type == HUB_TYPE_FARM_STATIC)
						{
							HUB_LIST *hh = ZeroMalloc(sizeof(HUB_LIST));
							hh->FarmMember = f;
							hh->DynamicHub = false;
							StrCpy(hh->Name, sizeof(hh->Name), h->Name);
							Add(f->HubList, hh);

							LockList(h->SessionList);
							{
								hh->NumSessions = LIST_NUM(h->SessionList);
								hh->NumSessionsBridge = Count(h->NumSessionsBridge);
								hh->NumSessionsClient = Count(h->NumSessionsClient);
							}
							UnlockList(h->SessionList);

							LockHashList(h->MacHashTable);
							{
								hh->NumMacTables = HASH_LIST_NUM(h->MacHashTable);
							}
							UnlockHashList(h->MacHashTable);

							LockList(h->IpTable);
							{
								hh->NumIpTables = LIST_NUM(h->IpTable);
							}
							UnlockList(h->IpTable);
						}
					}
				}
			}
			UnlockList(c->HubList);
		}
		UnlockList(f->HubList);

		// Point
		f->Point = SiGetPoint(s);
		f->NumSessions = Count(s->Cedar->CurrentSessions);
		f->MaxSessions = GetServerCapsInt(s, "i_max_sessions");
		f->NumTcpConnections = Count(s->Cedar->CurrentTcpConnections);

		Lock(s->Cedar->TrafficLock);
		{
			Copy(&f->Traffic, s->Cedar->Traffic, sizeof(TRAFFIC));
		}
		Unlock(s->Cedar->TrafficLock);

		f->AssignedBridgeLicense = Count(s->Cedar->AssignedBridgeLicense);
		f->AssignedClientLicense = Count(s->Cedar->AssignedClientLicense);

		Copy(f->RandomKey, s->MyRandomKey, SHA1_SIZE);


		Debug("Server %s: Point %u\n", f->hostname, f->Point);
	}
	else
	{
		// Enumerate HUBs which are remote member
		PACK *p = NewPack();
		UINT i, num, j;
		LIST *o = NewListFast(NULL);

		num = 0;

		for (i = 0;i < LIST_NUM(s->FarmMemberList);i++)
		{
			FARM_MEMBER *f = LIST_DATA(s->FarmMemberList, i);

			if (IsZero(f->RandomKey, SHA1_SIZE) == false && f->SystemId != 0)
			{
				num++;
			}
		}

		j = 0;

		for (i = 0;i < LIST_NUM(s->FarmMemberList);i++)
		{
			FARM_MEMBER *f = LIST_DATA(s->FarmMemberList, i);

			if (IsZero(f->RandomKey, SHA1_SIZE) == false && f->SystemId != 0)
			{
				PackAddDataEx(p, "MemberRandomKey", f->RandomKey, SHA1_SIZE, j, num);
				PackAddInt64Ex(p, "MemberSystemId", f->SystemId, j, num);
				j++;
			}
		}
		PackAddInt(p, "MemberSystemIdNum", num);

		p = SiCallTask(f, p, "enumhub");
		if (p != NULL)
		{
			LockList(f->HubList);
			{
				UINT i;
				// Erase the list
				for (i = 0;i < LIST_NUM(f->HubList);i++)
				{
					HUB_LIST *hh = LIST_DATA(f->HubList, i);
					Free(hh);
				}
				DeleteAll(f->HubList);

				for (i = 0;i < PackGetIndexCount(p, "HubName");i++)
				{
					HUB_LIST *hh = ZeroMalloc(sizeof(HUB_LIST));
					UINT num;
					UINT64 LastCommTime;

					PackGetStrEx(p, "HubName", hh->Name, sizeof(hh->Name), i);
					num = PackGetIntEx(p, "NumSession", i);
					hh->DynamicHub = ((PackGetIntEx(p, "HubType", i) == HUB_TYPE_FARM_DYNAMIC) ? true : false);
					hh->FarmMember = f;
					hh->NumSessions = PackGetIntEx(p, "NumSessions", i);
					hh->NumSessionsClient = PackGetIntEx(p, "NumSessionsClient", i);
					hh->NumSessionsBridge = PackGetIntEx(p, "NumSessionsBridge", i);
					hh->NumIpTables = PackGetIntEx(p, "NumIpTables", i);
					hh->NumMacTables = PackGetIntEx(p, "NumMacTables", i);
					LastCommTime = PackGetInt64Ex(p, "LastCommTime", i);
					Add(f->HubList, hh);
					//Debug("%s\n", hh->Name);

					LockList(c->HubList);
					{
						HUB *h = GetHub(c, hh->Name);

						if (h != NULL)
						{
							// Update the LastCommTime of the Virtual HUB
							Lock(h->lock);
							{
								if (h->LastCommTime < LastCommTime)
								{
									h->LastCommTime = LastCommTime;
								}
							}
							Unlock(h->lock);

							ReleaseHub(h);
						}
					}
					UnlockList(c->HubList);

					if (hh->DynamicHub && num >= 1)
					{
						// It is not necessary to be registered in the virtual HUB creation
						// history list because user session is already connected.
						// Remove from the Virtual HUB creation history list
						SiDelHubCreateHistory(s, hh->Name);
					}

					if (hh->DynamicHub && num == 0)
					{
						// Check the Virtual HUB creation history list.
						// If it is created within 60 seconds of the most recent
						// in the case of Virtual HUB which the first user is not
						// connected yet, not to remove because there is no user
						if (SiIsHubRegistedOnCreateHistory(s, hh->Name) == false)
						{
							// Stop because all uses have gone in the dynamic HUB
							HUB *h;
							LockList(c->HubList);
							{
								h = GetHub(c, hh->Name);
							}
							UnlockList(c->HubList);

							if (h != NULL)
							{
								Add(o, h);
							}
						}
					}
				}
			}
			UnlockList(f->HubList);
			f->Point = PackGetInt(p, "Point");
			Debug("Server %s: Point %u\n", f->hostname, f->Point);
			f->NumSessions = PackGetInt(p, "NumTotalSessions");
			if (f->NumSessions == 0)
			{
				f->NumSessions = PackGetInt(p, "NumSessions");
			}
			f->MaxSessions = PackGetInt(p, "MaxSessions");
			f->NumTcpConnections = PackGetInt(p, "NumTcpConnections");
			InRpcTraffic(&f->Traffic, p);

			f->AssignedBridgeLicense = PackGetInt(p, "AssignedBridgeLicense");
			f->AssignedClientLicense = PackGetInt(p, "AssignedClientLicense");

			if (PackGetDataSize(p, "RandomKey") == SHA1_SIZE)
			{
				PackGetData(p, "RandomKey", f->RandomKey);
			}

			f->SystemId = PackGetInt64(p, "SystemId");

			// Apply the traffic difference information
			num = PackGetIndexCount(p, "TdType");
			for (i = 0;i < num;i++)
			{
				TRAFFIC traffic;
				UINT type;
				HUB *h;
				char name[MAX_SIZE];
				char hubname[MAX_SIZE];

				type = PackGetIntEx(p, "TdType", i);
				PackGetStrEx(p, "TdName", name, sizeof(name), i);
				PackGetStrEx(p, "TdHubName", hubname, sizeof(hubname), i);
				InRpcTrafficEx(&traffic, p, i);

				LockList(c->HubList);
				{
					h = GetHub(c, hubname);
					if (h != NULL)
					{
						if (type == TRAFFIC_DIFF_HUB)
						{
							Lock(h->TrafficLock);
							{
								AddTraffic(h->Traffic, &traffic);
							}
							Unlock(h->TrafficLock);
						}
						else
						{
							AcLock(h);
							{
								USER *u = AcGetUser(h, name);
								if (u != NULL)
								{
									Lock(u->lock);
									{
										AddTraffic(u->Traffic, &traffic);
									}
									Unlock(u->lock);
									if (u->Group != NULL)
									{
										Lock(u->Group->lock);
										{
											AddTraffic(u->Group->Traffic, &traffic);
										}
										Unlock(u->Group->lock);
									}
									ReleaseUser(u);
								}
							}
							AcUnlock(h);
						}
						ReleaseHub(h);
					}
					UnlockList(c->HubList);
				}
			}

			FreePack(p);
		}

		for (i = 0;i < LIST_NUM(o);i++)
		{
			HUB *h = LIST_DATA(o, i);
			SiCallDeleteHub(s, f, h);
			Debug("Delete HUB: %s\n", h->Name);
			ReleaseHub(h);
		}

		ReleaseList(o);
	}
}