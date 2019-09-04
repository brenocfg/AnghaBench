#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  X ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/  CurrentActiveLinks; int /*<<< orphan*/  FifoBudgetLock; int /*<<< orphan*/  QueueBudgetLock; int /*<<< orphan*/  CurrentTcpQueueSizeLock; int /*<<< orphan*/  CurrentRegionLock; int /*<<< orphan*/  OpenVPNPublicPortsLock; int /*<<< orphan*/  UdpPortList; int /*<<< orphan*/  AcceptingSockets; int /*<<< orphan*/  CedarSuperLock; int /*<<< orphan*/  AssignedClientLicense; int /*<<< orphan*/  AssignedBridgeLicense; struct TYPE_9__* BuildInfo; struct TYPE_9__* VerString; int /*<<< orphan*/  TrafficLock; int /*<<< orphan*/  Traffic; struct TYPE_9__* HttpAcceptEncoding; struct TYPE_9__* HttpAcceptLanguage; struct TYPE_9__* HttpAccept; struct TYPE_9__* HttpUserAgent; struct TYPE_9__* MachineName; struct TYPE_9__* ServerStr; int /*<<< orphan*/  TrafficDiffList; struct TYPE_9__* HubName; struct TYPE_9__* Name; struct TYPE_9__* CipherList; scalar_t__ ServerK; int /*<<< orphan*/ * ServerX; int /*<<< orphan*/ * DebugLog; int /*<<< orphan*/  CurrentSessions; int /*<<< orphan*/  ConnectionIncrement; int /*<<< orphan*/  lock; int /*<<< orphan*/  UDPEntryList; int /*<<< orphan*/  ConnectionList; int /*<<< orphan*/  HubList; int /*<<< orphan*/  ListenerList; int /*<<< orphan*/  CaList; int /*<<< orphan*/  WebUI; } ;
typedef  TYPE_1__ TRAFFIC_DIFF ;
typedef  TYPE_1__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteCounter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeCedarLayer3 (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeK (scalar_t__) ; 
 int /*<<< orphan*/  FreeLocalBridgeList (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeLog (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeNetSvcList (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeNoSslList (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeTraffic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 void* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseIntList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WuFreeWebUI (int /*<<< orphan*/ ) ; 

void CleanupCedar(CEDAR *c)
{
	UINT i;
	// Validate arguments
	if (c == NULL)
	{
		return;
	}

	WuFreeWebUI(c->WebUI);
	FreeCedarLayer3(c);

/*
	for (i = 0;i < LIST_NUM(c->HubList);i++)
	{
		HUB *h = LIST_DATA(c->HubList, i);
	}
*/
	for (i = 0;i < LIST_NUM(c->CaList);i++)
	{
		X *x = LIST_DATA(c->CaList, i);
		FreeX(x);
	}
	ReleaseList(c->CaList);

	ReleaseList(c->ListenerList);
	ReleaseList(c->HubList);
	ReleaseList(c->ConnectionList);
	//CleanupUDPEntry(c);
	ReleaseList(c->UDPEntryList);
	DeleteLock(c->lock);
	DeleteCounter(c->ConnectionIncrement);
	DeleteCounter(c->CurrentSessions);

	if (c->DebugLog != NULL)
	{
		FreeLog(c->DebugLog);
	}

	if (c->ServerX)
	{
		FreeX(c->ServerX);
	}
	if (c->ServerK)
	{
		FreeK(c->ServerK);
	}

	if (c->CipherList)
	{
		Free(c->CipherList);
	}

	for (i = 0;i < LIST_NUM(c->TrafficDiffList);i++)
	{
		TRAFFIC_DIFF *d = LIST_DATA(c->TrafficDiffList, i);
		Free(d->Name);
		Free(d->HubName);
		Free(d);
	}

	ReleaseList(c->TrafficDiffList);

	Free(c->ServerStr);
	Free(c->MachineName);

	Free(c->HttpUserAgent);
	Free(c->HttpAccept);
	Free(c->HttpAcceptLanguage);
	Free(c->HttpAcceptEncoding);

	FreeTraffic(c->Traffic);

	DeleteLock(c->TrafficLock);

	FreeNetSvcList(c);

	Free(c->VerString);
	Free(c->BuildInfo);

	FreeLocalBridgeList(c);

	DeleteCounter(c->AssignedBridgeLicense);
	DeleteCounter(c->AssignedClientLicense);

	FreeNoSslList(c);

	DeleteLock(c->CedarSuperLock);

	DeleteCounter(c->AcceptingSockets);

	ReleaseIntList(c->UdpPortList);

	DeleteLock(c->OpenVPNPublicPortsLock);

	DeleteLock(c->CurrentRegionLock);

	DeleteLock(c->CurrentTcpQueueSizeLock);
	DeleteLock(c->QueueBudgetLock);
	DeleteLock(c->FifoBudgetLock);

	DeleteCounter(c->CurrentActiveLinks);

	Free(c);
}