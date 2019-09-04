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
typedef  int /*<<< orphan*/  name ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/  UserList; struct TYPE_9__* Msg; int /*<<< orphan*/  AdminOptionList; int /*<<< orphan*/  SecurityLogger; int /*<<< orphan*/  PacketLogger; int /*<<< orphan*/  RadiusOptionLock; int /*<<< orphan*/  TicketList; int /*<<< orphan*/  TrafficLock; struct TYPE_9__* SecureNATOption; struct TYPE_9__* Option; int /*<<< orphan*/  OldTraffic; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  SessionCounter; int /*<<< orphan*/  NumSessionsBridge; int /*<<< orphan*/  NumSessionsClient; int /*<<< orphan*/  NumSessions; int /*<<< orphan*/  LinkList; int /*<<< orphan*/  MonitorList; int /*<<< orphan*/  IpTable; int /*<<< orphan*/  MacHashTable; int /*<<< orphan*/  SessionList; struct TYPE_9__* Name; int /*<<< orphan*/  lock_online; int /*<<< orphan*/  lock; int /*<<< orphan*/  Cedar; int /*<<< orphan*/  HubDb; int /*<<< orphan*/  RadiusSecret; struct TYPE_9__* RadiusServerName; scalar_t__ WatchDogStarted; } ;
typedef  TYPE_1__ HUB ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteCounter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteHubDb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeAccessList (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeLog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeTraffic (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeUserList (int /*<<< orphan*/ ) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  ReleaseAllLink (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseCedar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseHashList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StopHubWatchDog (TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,TYPE_1__*) ; 

void CleanupHub(HUB *h)
{
	UINT i;
	char name[MAX_SIZE];
	// Validate arguments
	if (h == NULL)
	{
		return;
	}

	StrCpy(name, sizeof(name), h->Name);

	if (h->WatchDogStarted)
	{
		StopHubWatchDog(h);
	}

	FreeAccessList(h);

	if (h->RadiusServerName != NULL)
	{
		Free(h->RadiusServerName);
		FreeBuf(h->RadiusSecret);
	}
	ReleaseAllLink(h);
	DeleteHubDb(h->HubDb);
	ReleaseCedar(h->Cedar);
	DeleteLock(h->lock);
	DeleteLock(h->lock_online);
	Free(h->Name);
	ReleaseList(h->SessionList);
	ReleaseHashList(h->MacHashTable);
	ReleaseList(h->IpTable);
	ReleaseList(h->MonitorList);
	ReleaseList(h->LinkList);
	DeleteCounter(h->NumSessions);
	DeleteCounter(h->NumSessionsClient);
	DeleteCounter(h->NumSessionsBridge);
	DeleteCounter(h->SessionCounter);
	FreeTraffic(h->Traffic);
	FreeTraffic(h->OldTraffic);
	Free(h->Option);

	Free(h->SecureNATOption);

	DeleteLock(h->TrafficLock);

	for (i = 0;i < LIST_NUM(h->TicketList);i++)
	{
		Free(LIST_DATA(h->TicketList, i));
	}

	ReleaseList(h->TicketList);

	DeleteLock(h->RadiusOptionLock);

	FreeLog(h->PacketLogger);
	FreeLog(h->SecurityLogger);

	for (i = 0;i < LIST_NUM(h->AdminOptionList);i++)
	{
		Free(LIST_DATA(h->AdminOptionList, i));
	}
	ReleaseList(h->AdminOptionList);

	if (h->Msg != NULL)
	{
		Free(h->Msg);
	}

	FreeUserList(h->UserList);

	Free(h);
}