#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
struct TYPE_10__ {int /*<<< orphan*/  SockEvent; } ;
typedef  TYPE_1__ VH ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_11__ {int ProxyDns; int /*<<< orphan*/  UdpSendQueue; int /*<<< orphan*/  DestIpProxy; } ;
typedef  TYPE_2__ NAT_ENTRY ;
typedef  int /*<<< orphan*/  IP ;
typedef  int /*<<< orphan*/  BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (void*,void*,int /*<<< orphan*/ ) ; 
 TYPE_2__* CreateNatUdp (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Debug (char*,...) ; 
 int GetDefaultDns (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPToStr (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPToUINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InsertQueue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 void* Malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAT_UDP ; 
 int /*<<< orphan*/ * NewBlock (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* SearchNat (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  SetNat (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetSockEvent (int /*<<< orphan*/ ) ; 

void UdpRecvForInternet(VH *v, UINT src_ip, UINT src_port, UINT dest_ip, UINT dest_port, void *data, UINT size, bool dns_proxy)
{
	NAT_ENTRY *n, t;
	BLOCK *block;
	void *buf;
	UINT dns_ip = 0;
	// Validate arguments
	if (data == NULL || v == NULL)
	{
		return;
	}

	if (dns_proxy)
	{
		// Get the DNS server of the proxy to connect to
		IP ip;
		char tmp[MAX_SIZE];
		if (GetDefaultDns(&ip) == false)
		{
			// Failure
			Debug("Failed to GetDefaultDns()\n");
			return;
		}
		dns_ip = IPToUINT(&ip);
		IPToStr(tmp, sizeof(tmp), &ip);
		Debug("Redirect to DNS Server %s\n", tmp);
	}

	// Examine whether the NAT entry for this packet has already been created
	SetNat(&t, NAT_UDP, src_ip, src_port, dest_ip, dest_port, 0, 0);
	n = SearchNat(v, &t);

	if (n == NULL)
	{
		// Create a NAT entry because it is the first packet
		n = CreateNatUdp(v, src_ip, src_port, dest_ip, dest_port, dns_proxy ? dns_ip : 0);
		if (n == NULL)
		{
			// Entry creation failed
			return;
		}

		if (dns_proxy)
		{
			n->ProxyDns = true;
			n->DestIpProxy = dns_ip;
		}
	}

	// Set the event by inserting the packet into the queue
	buf = Malloc(size);
	Copy(buf, data, size);
	block = NewBlock(buf, size, 0);
	InsertQueue(n->UdpSendQueue, block);

	SetSockEvent(v->SockEvent);
}