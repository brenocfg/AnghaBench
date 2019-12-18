#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sl ;
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int NoMoreChangeSettings; int Halt; int /*<<< orphan*/  LockSettings; int /*<<< orphan*/  OsServiceCheckThreadEvent; int /*<<< orphan*/  OsServiceCheckThread; int /*<<< orphan*/  EtherIPIdList; int /*<<< orphan*/  Ike; int /*<<< orphan*/  L2TP; int /*<<< orphan*/  Cedar; int /*<<< orphan*/  UdpListener; } ;
typedef  int /*<<< orphan*/  IPSEC_SERVICES ;
typedef  TYPE_1__ IPSEC_SERVER ;
typedef  TYPE_1__ ETHERIP_ID ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeIKEServer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeL2TPServer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeUdpListener (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  IPsecServerSetServices (TYPE_1__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseCedar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StopIKEServer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StopL2TPServer (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (int /*<<< orphan*/ *,int) ; 

void FreeIPsecServer(IPSEC_SERVER *s)
{
	UINT i;
	IPSEC_SERVICES sl;
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	s->NoMoreChangeSettings = true;

	// Stopp the L2TP server
	StopL2TPServer(s->L2TP, false);

	// Stop the IKE server
	StopIKEServer(s->Ike);

	// Stop all the services explicitly
	Zero(&sl, sizeof(sl));
	IPsecServerSetServices(s, &sl);

	// Releasing process
	FreeUdpListener(s->UdpListener);

	ReleaseCedar(s->Cedar);

	FreeL2TPServer(s->L2TP);

	FreeIKEServer(s->Ike);

	for (i = 0;i < LIST_NUM(s->EtherIPIdList);i++)
	{
		ETHERIP_ID *k = LIST_DATA(s->EtherIPIdList, i);

		Free(k);
	}

	ReleaseList(s->EtherIPIdList);

	// Stop the OS monitoring thread
	s->Halt = true;
	Set(s->OsServiceCheckThreadEvent);
	WaitThread(s->OsServiceCheckThread, INFINITE);
	ReleaseThread(s->OsServiceCheckThread);
	ReleaseEvent(s->OsServiceCheckThreadEvent);

	DeleteLock(s->LockSettings);

	Free(s);
}