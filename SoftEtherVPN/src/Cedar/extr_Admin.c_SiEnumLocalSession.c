#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  size_t UINT ;
struct TYPE_28__ {TYPE_10__* SessionList; TYPE_1__* Option; } ;
struct TYPE_27__ {int NumSession; TYPE_7__* Sessions; } ;
struct TYPE_26__ {int IsDormantEnabled; int IsDormant; int /*<<< orphan*/  RemoteHostname; scalar_t__ LastCommDormant; int /*<<< orphan*/  UniqueId; int /*<<< orphan*/  Client_MonitorMode; int /*<<< orphan*/  Client_BridgeMode; int /*<<< orphan*/  PacketNum; int /*<<< orphan*/  PacketSize; int /*<<< orphan*/  CurrentNumTcp; int /*<<< orphan*/  VLanId; int /*<<< orphan*/  Layer3Mode; int /*<<< orphan*/  BridgeMode; int /*<<< orphan*/  SecureNATMode; int /*<<< orphan*/  LinkMode; void* LastCommTime; void* CreatedTime; int /*<<< orphan*/  MaxNumTcp; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  ClientIP; int /*<<< orphan*/  Ip; int /*<<< orphan*/  Username; int /*<<< orphan*/  Name; } ;
struct TYPE_25__ {int /*<<< orphan*/  Cedar; } ;
struct TYPE_23__ {int /*<<< orphan*/  UniqueId; } ;
struct TYPE_24__ {scalar_t__ LastCommTimeForDormant; int /*<<< orphan*/  lock; scalar_t__ NormalClient; TYPE_4__ NodeInfo; int /*<<< orphan*/  IsMonitorMode; int /*<<< orphan*/  IsBridgeMode; int /*<<< orphan*/  TrafficLock; int /*<<< orphan*/  Traffic; TYPE_3__* Connection; int /*<<< orphan*/  VLanId; int /*<<< orphan*/  L3SwitchMode; int /*<<< orphan*/  BridgeMode; int /*<<< orphan*/  SecureNATMode; int /*<<< orphan*/  LinkModeServer; int /*<<< orphan*/  LastCommTime; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  MaxConnection; int /*<<< orphan*/  Username; int /*<<< orphan*/  Name; } ;
struct TYPE_22__ {TYPE_2__* Tcp; int /*<<< orphan*/  ClientHostname; int /*<<< orphan*/  ClientIp; } ;
struct TYPE_21__ {TYPE_10__* TcpSockList; } ;
struct TYPE_20__ {scalar_t__ DetectDormantSessionInterval; } ;
struct TYPE_19__ {int /*<<< orphan*/  num_item; } ;
typedef  TYPE_5__ SESSION ;
typedef  TYPE_6__ SERVER ;
typedef  TYPE_7__ RPC_ENUM_SESSION_ITEM ;
typedef  TYPE_8__ RPC_ENUM_SESSION ;
typedef  TYPE_9__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CopyIP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_9__* GetHub (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GetMachineName (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  GetTrafficPacketNum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTrafficPacketSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPToUINT (int /*<<< orphan*/ *) ; 
 TYPE_5__* LIST_DATA (TYPE_10__*,size_t) ; 
 int LIST_NUM (TYPE_10__*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockHubList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (TYPE_10__*) ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_9__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ Tick64 () ; 
 void* Tick64ToTime64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockHubList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (TYPE_10__*) ; 
 void* ZeroMalloc (int) ; 

void SiEnumLocalSession(SERVER *s, char *hubname, RPC_ENUM_SESSION *t)
{
	HUB *h;
	UINT64 now = Tick64();
	UINT64 dormant_interval = 0;
	// Validate arguments
	if (s == NULL || hubname == NULL || t == NULL)
	{
		return;
	}

	LockHubList(s->Cedar);
	h = GetHub(s->Cedar, hubname);
	UnlockHubList(s->Cedar);

	if (h == NULL)
	{
		t->NumSession = 0;
		t->Sessions = ZeroMalloc(0);
		return;
	}

	if (h->Option != NULL)
	{
		dormant_interval = h->Option->DetectDormantSessionInterval * (UINT64)1000;
	}

	LockList(h->SessionList);
	{
		UINT i;
		t->NumSession = LIST_NUM(h->SessionList);
		t->Sessions = ZeroMalloc(sizeof(RPC_ENUM_SESSION_ITEM) * t->NumSession);

		for (i = 0;i < t->NumSession;i++)
		{
			SESSION *s = LIST_DATA(h->SessionList, i);
			RPC_ENUM_SESSION_ITEM *e = &t->Sessions[i];
			Lock(s->lock);
			{
				StrCpy(e->Name, sizeof(e->Name), s->Name);
				StrCpy(e->Username, sizeof(e->Username), s->Username);
				e->Ip = IPToUINT(&s->Connection->ClientIp);
				CopyIP(&e->ClientIP, &s->Connection->ClientIp);
				StrCpy(e->Hostname, sizeof(e->Hostname), s->Connection->ClientHostname);
				e->MaxNumTcp = s->MaxConnection;
				e->CreatedTime = Tick64ToTime64(s->CreatedTime);
				e->LastCommTime = Tick64ToTime64(s->LastCommTime);
				e->LinkMode = s->LinkModeServer;
				e->SecureNATMode = s->SecureNATMode;
				e->BridgeMode = s->BridgeMode;
				e->Layer3Mode = s->L3SwitchMode;
				e->VLanId = s->VLanId;
				LockList(s->Connection->Tcp->TcpSockList);
				{
					e->CurrentNumTcp = s->Connection->Tcp->TcpSockList->num_item;
				}
				UnlockList(s->Connection->Tcp->TcpSockList);
				Lock(s->TrafficLock);
				{
					e->PacketSize = GetTrafficPacketSize(s->Traffic);
					e->PacketNum = GetTrafficPacketNum(s->Traffic);
				}
				Unlock(s->TrafficLock);
				e->Client_BridgeMode = s->IsBridgeMode;
				e->Client_MonitorMode = s->IsMonitorMode;
				Copy(e->UniqueId, s->NodeInfo.UniqueId, 16);

				if (s->NormalClient)
				{
					e->IsDormantEnabled = (dormant_interval == 0 ? false : true);
					if (e->IsDormantEnabled)
					{
						if (s->LastCommTimeForDormant == 0)
						{
							e->LastCommDormant = (UINT64)0x7FFFFFFF;
						}
						else
						{
							e->LastCommDormant = now - s->LastCommTimeForDormant;
						}
						if (s->LastCommTimeForDormant == 0)
						{
							e->IsDormant = true;
						}
						else
						{
							if ((s->LastCommTimeForDormant + dormant_interval) < now)
							{
								e->IsDormant = true;
							}
						}
					}
				}
			}
			Unlock(s->lock);

			GetMachineName(e->RemoteHostname, sizeof(e->RemoteHostname));
		}
	}
	UnlockList(h->SessionList);

	ReleaseHub(h);
}