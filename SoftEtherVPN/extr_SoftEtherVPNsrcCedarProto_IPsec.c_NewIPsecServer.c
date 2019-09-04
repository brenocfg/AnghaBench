#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {TYPE_1__* Server; int /*<<< orphan*/  ref; } ;
struct TYPE_15__ {int /*<<< orphan*/  OsServiceCheckThread; int /*<<< orphan*/  OsServiceCheckThreadEvent; int /*<<< orphan*/  EtherIPIdList; int /*<<< orphan*/  UdpListener; TYPE_10__* Ike; int /*<<< orphan*/  L2TP; TYPE_3__* Cedar; int /*<<< orphan*/  LockSettings; } ;
struct TYPE_14__ {int /*<<< orphan*/  ListenIP; } ;
struct TYPE_13__ {int /*<<< orphan*/  Secret; } ;
typedef  TYPE_2__ IPSEC_SERVER ;
typedef  TYPE_3__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CmpEtherIPId ; 
 int /*<<< orphan*/  IPSEC_DEFAULT_SECRET ; 
 int /*<<< orphan*/  IPsecOsServiceCheckThread ; 
 int /*<<< orphan*/  IPsecServerUdpPacketRecvProc ; 
 int /*<<< orphan*/  NewEvent () ; 
 TYPE_10__* NewIKEServer (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  NewL2TPServer (TYPE_3__*) ; 
 int /*<<< orphan*/  NewList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  NewThread (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  NewUdpListener (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* ZeroMalloc (int) ; 

IPSEC_SERVER *NewIPsecServer(CEDAR *cedar)
{
	IPSEC_SERVER *s;
	// Validate arguments
	if (cedar == NULL)
	{
		return NULL;
	}

	s = ZeroMalloc(sizeof(IPSEC_SERVER));

	s->LockSettings = NewLock();

	s->Cedar = cedar;

	AddRef(s->Cedar->ref);

	s->L2TP = NewL2TPServer(cedar);

	s->Ike = NewIKEServer(cedar, s);
	StrCpy(s->Ike->Secret, sizeof(s->Ike->Secret), IPSEC_DEFAULT_SECRET);

	s->UdpListener = NewUdpListener(IPsecServerUdpPacketRecvProc, s, &cedar->Server->ListenIP);

	s->EtherIPIdList = NewList(CmpEtherIPId);

	// Start an OS service monitoring thread
	s->OsServiceCheckThreadEvent = NewEvent();
	s->OsServiceCheckThread = NewThread(IPsecOsServiceCheckThread, s);

	return s;
}