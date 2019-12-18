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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UDPPACKET ;
struct TYPE_6__ {int /*<<< orphan*/  ThreadList; int /*<<< orphan*/  Engine; int /*<<< orphan*/  Cedar; int /*<<< orphan*/  SockEvent; int /*<<< orphan*/  ClientList; int /*<<< orphan*/  IkeSaList; int /*<<< orphan*/  IPsecSaList; int /*<<< orphan*/  SendPacketList; } ;
typedef  int /*<<< orphan*/  IPSECSA ;
typedef  TYPE_1__ IKE_SERVER ;
typedef  int /*<<< orphan*/  IKE_SA ;
typedef  int /*<<< orphan*/  IKE_CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  Debug (char*,...) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  FreeIPsecSa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeIkeClient (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeIkeEngine (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeIkeSa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeThreadList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeUdpPacket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPsecLog (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 void* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseCedar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSockEvent (int /*<<< orphan*/ ) ; 

void FreeIKEServer(IKE_SERVER *ike)
{
	UINT i;
	// Validate arguments
	if (ike == NULL)
	{
		return;
	}

	IPsecLog(ike, NULL, NULL, NULL, "LI_STOPPING");

	for (i = 0;i < LIST_NUM(ike->SendPacketList);i++)
	{
		UDPPACKET *udp = LIST_DATA(ike->SendPacketList, i);

		FreeUdpPacket(udp);
	}

	ReleaseList(ike->SendPacketList);

	Debug("Num of IPsec SAs: %u\n", LIST_NUM(ike->IPsecSaList));
	IPsecLog(ike, NULL, NULL, NULL, "LI_NUM_IPSEC_SA", LIST_NUM(ike->IPsecSaList));

	for (i = 0;i < LIST_NUM(ike->IPsecSaList);i++)
	{
		IPSECSA *sa = LIST_DATA(ike->IPsecSaList, i);

		FreeIPsecSa(sa);
	}

	ReleaseList(ike->IPsecSaList);

	Debug("Num of IKE SAs: %u\n", LIST_NUM(ike->IkeSaList));
	IPsecLog(ike, NULL, NULL, NULL, "LI_NUM_IKE_SA", LIST_NUM(ike->IkeSaList));

	for (i = 0;i < LIST_NUM(ike->IkeSaList);i++)
	{
		IKE_SA *sa = LIST_DATA(ike->IkeSaList, i);

		FreeIkeSa(sa);
	}

	ReleaseList(ike->IkeSaList);

	Debug("Num of IKE_CLIENTs: %u\n", LIST_NUM(ike->ClientList));
	IPsecLog(ike, NULL, NULL, NULL, "LI_NUM_IKE_CLIENTS", LIST_NUM(ike->ClientList));

	for (i = 0;i < LIST_NUM(ike->ClientList);i++)
	{
		IKE_CLIENT *c = LIST_DATA(ike->ClientList, i);

		FreeIkeClient(ike, c);
	}

	ReleaseList(ike->ClientList);

	ReleaseSockEvent(ike->SockEvent);

	IPsecLog(ike, NULL, NULL, NULL, "LI_STOP");

	ReleaseCedar(ike->Cedar);

	FreeIkeEngine(ike->Engine);

	Debug("FreeThreadList()...\n");
	FreeThreadList(ike->ThreadList);
	Debug("FreeThreadList() Done.\n");

	Free(ike);
}