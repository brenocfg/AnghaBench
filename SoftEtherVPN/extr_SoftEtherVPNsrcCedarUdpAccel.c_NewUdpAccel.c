#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int NoNatT; int IsInCedarPortList; int ClientMode; int IsIPv6; scalar_t__ MyCookie; scalar_t__ YourCookie; int /*<<< orphan*/  NatT_GetIpThread; int /*<<< orphan*/  NatT_HaltEvent; int /*<<< orphan*/  NatT_Lock; int /*<<< orphan*/  MyPort; scalar_t__ MaxUdpPacketSize; int /*<<< orphan*/  NextIv; int /*<<< orphan*/  RecvBlockQueue; int /*<<< orphan*/  MyIp; int /*<<< orphan*/  YourKey; int /*<<< orphan*/  MyKey; TYPE_2__* UdpSock; void* Now; void* CreatedTick; int /*<<< orphan*/  NatT_TranId; TYPE_3__* Cedar; } ;
typedef  TYPE_1__ UDP_ACCEL ;
struct TYPE_11__ {int /*<<< orphan*/  ref; int /*<<< orphan*/  UdpPortList; } ;
struct TYPE_10__ {int /*<<< orphan*/  LocalPort; } ;
typedef  TYPE_2__ SOCK ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_3__ CEDAR ;

/* Variables and functions */
 int /*<<< orphan*/  AddIntDistinct (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ ) ; 
 int IsIP6 (int /*<<< orphan*/ *) ; 
 int IsIntInList (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ IsZeroIP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 scalar_t__ MTU_FOR_PPPOE ; 
 int /*<<< orphan*/  NatT_GetIpThread ; 
 int /*<<< orphan*/  NewEvent () ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  NewQueue () ; 
 int /*<<< orphan*/  NewThread (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_2__* NewUDPEx3 (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Rand (int /*<<< orphan*/ ,int) ; 
 void* Rand32 () ; 
 int /*<<< orphan*/  Rand64 () ; 
 void* Tick64 () ; 
 scalar_t__ UDP_SERVER_PORT_HIGHER ; 
 scalar_t__ UDP_SERVER_PORT_LOWER ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 TYPE_1__* ZeroMalloc (int) ; 

UDP_ACCEL *NewUdpAccel(CEDAR *cedar, IP *ip, bool client_mode, bool random_port, bool no_nat_t)
{
	UDP_ACCEL *a;
	SOCK *s;
	UINT max_udp_size;
	bool is_in_cedar_port_list = false;

	if (IsZeroIP(ip))
	{
		ip = NULL;
	}

	if (client_mode || random_port)
	{
		// Use a appropriate vacant port number in the case of using random port or client mode
		s = NewUDPEx3(0, ip);
	}
	else
	{
		// Specify in the range in the case of server mode
		UINT i;
		s = NULL;

		LockList(cedar->UdpPortList);
		{
			for (i = UDP_SERVER_PORT_LOWER;i <= UDP_SERVER_PORT_HIGHER;i++)
			{
				if (IsIntInList(cedar->UdpPortList, i) == false)
				{
					s = NewUDPEx3(i, ip);

					if (s != NULL)
					{
						is_in_cedar_port_list = true;
						break;
					}
				}
			}

			if (s == NULL)
			{
				// Leave the port selection to the OS because the available port is not found within the range
				s = NewUDPEx3(0, ip);
			}

			if (s != NULL && is_in_cedar_port_list)
			{
				AddIntDistinct(cedar->UdpPortList, i);
			}
		}
		UnlockList(cedar->UdpPortList);
	}

	if (s == NULL)
	{
		return NULL;
	}

	a = ZeroMalloc(sizeof(UDP_ACCEL));

	a->Cedar = cedar;
	AddRef(a->Cedar->ref);

	a->NoNatT = no_nat_t;


	a->NatT_TranId = Rand64();

	a->CreatedTick = Tick64();

	a->IsInCedarPortList = is_in_cedar_port_list;

	a->ClientMode = client_mode;

	a->Now = Tick64();
	a->UdpSock = s;
	Rand(a->MyKey, sizeof(a->MyKey));
	Rand(a->YourKey, sizeof(a->YourKey));

	Copy(&a->MyIp, ip, sizeof(IP));
	a->MyPort = s->LocalPort;

	a->IsIPv6 = IsIP6(ip);

	if (a->IsIPv6)
	{
		a->NoNatT = true;
	}

	a->RecvBlockQueue = NewQueue();

	Rand(a->NextIv, sizeof(a->NextIv));

	do
	{
		a->MyCookie = Rand32();
	}
	while (a->MyCookie == 0);

	do
	{
		a->YourCookie = Rand32();
	}
	while (a->MyCookie == 0 || a->MyCookie == a->YourCookie);

	// Calculate the maximum transmittable UDP packet size
	max_udp_size = MTU_FOR_PPPOE;

	if (a->IsIPv6 == false)
	{
		// IPv4
		max_udp_size -= 20;
	}
	else
	{
		// IPv6
		max_udp_size -= 40;
	}

	// UDP
	max_udp_size -= 8;

	a->MaxUdpPacketSize = max_udp_size;

	Debug("Udp Accel My Port = %u\n", a->MyPort);

	// Initialize the NAT-T server IP address acquisition thread
	a->NatT_Lock = NewLock();
	a->NatT_HaltEvent = NewEvent();

	if (a->NoNatT == false)
	{
		a->NatT_GetIpThread = NewThread(NatT_GetIpThread, a);
	}

	return a;
}