#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  NatTable; int /*<<< orphan*/  SockEvent; int /*<<< orphan*/  Now; int /*<<< orphan*/  Counter; } ;
typedef  TYPE_1__ VH ;
typedef  scalar_t__ UINT ;
struct TYPE_19__ {scalar_t__ SecureNAT_MaxTcpSessionsPerIp; scalar_t__ SecureNAT_MaxUdpSessionsPerIp; } ;
struct TYPE_18__ {int ProxyDns; int UdpSocketCreated; int /*<<< orphan*/  Id; void* UdpRecvQueue; void* UdpSendQueue; int /*<<< orphan*/  LastCommTime; int /*<<< orphan*/  CreatedTime; scalar_t__ DestIpProxy; scalar_t__ DestPort; scalar_t__ DestIp; scalar_t__ SrcPort; scalar_t__ SrcIp; int /*<<< orphan*/  Protocol; int /*<<< orphan*/  lock; TYPE_1__* v; } ;
typedef  TYPE_2__ NAT_ENTRY ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_3__ HUB_OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int CanCreateNewNatEntry (TYPE_1__*) ; 
 int /*<<< orphan*/  Debug (char*,char*,scalar_t__,char*,scalar_t__) ; 
 int /*<<< orphan*/  DisconnectNatEntryNow (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ GetNumNatEntriesPerIp (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* GetOldestNatEntryOfIp (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPToStr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Inc (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  NAT_UDP ; 
 int /*<<< orphan*/  NLog (TYPE_1__*,char*,int /*<<< orphan*/ ,char*,scalar_t__,char*,scalar_t__) ; 
 TYPE_3__* NatGetHubOption (TYPE_1__*) ; 
 int /*<<< orphan*/  NewLock () ; 
 void* NewQueue () ; 
 int /*<<< orphan*/  SetSockEvent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINTToIP (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__* ZeroMalloc (int) ; 

NAT_ENTRY *CreateNatUdp(VH *v, UINT src_ip, UINT src_port, UINT dest_ip, UINT dest_port, UINT dns_proxy_ip)
{
	NAT_ENTRY *n;
	HUB_OPTION *o;
	// Validate arguments
	if (v == NULL)
	{
		return NULL;
	}

	if (CanCreateNewNatEntry(v) == false)
	{
		return NULL;
	}

	o = NatGetHubOption(v);
	if (o != NULL && o->SecureNAT_MaxTcpSessionsPerIp != 0)
	{
		if (GetNumNatEntriesPerIp(v, src_ip, NAT_UDP, false) >= o->SecureNAT_MaxUdpSessionsPerIp)
		{
			NAT_ENTRY *oldest = GetOldestNatEntryOfIp(v, src_ip, NAT_UDP);

			if (oldest != NULL)
			{
				DisconnectNatEntryNow(v, oldest);
			}
		}
	}

	n = ZeroMalloc(sizeof(NAT_ENTRY));
	n->Id = Inc(v->Counter);
	n->v = v;
	n->lock = NewLock();
	n->Protocol = NAT_UDP;
	n->SrcIp = src_ip;
	n->SrcPort = src_port;
	n->DestIp = dest_ip;
	n->DestPort = dest_port;

	if (dns_proxy_ip != 0)
	{
		n->ProxyDns = true;
		n->DestIpProxy = dns_proxy_ip;
	}

	n->CreatedTime = n->LastCommTime = v->Now;

	n->UdpSendQueue = NewQueue();
	n->UdpRecvQueue = NewQueue();

	n->UdpSocketCreated = false;

	SetSockEvent(v->SockEvent);

#if	1
	{
		IP ip1, ip2;
		char s1[MAX_SIZE], s2[MAX_SIZE];
		UINTToIP(&ip1, src_ip);
		UINTToIP(&ip2, dest_ip);
		IPToStr(s1, 0, &ip1);
		IPToStr(s2, 0, &ip2);
		Debug("NAT_ENTRY: CreateNatUdp %s %u -> %s %u\n", s1, src_port, s2, dest_port);

		NLog(v, "LH_NAT_UDP_CREATED", n->Id, s1, src_port, s2, dest_port);
	}
#endif

	Add(v->NatTable, n);

	return n;
}