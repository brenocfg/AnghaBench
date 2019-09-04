#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int NatDoCancelFlag; scalar_t__ Now; scalar_t__ NatUdpTimeout; void* TmpBuf; int /*<<< orphan*/  SockEvent; } ;
typedef  TYPE_1__ VH ;
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_23__ {int IgnoreRecvErr; int IgnoreSendErr; scalar_t__ LocalPort; int /*<<< orphan*/  LocalIP; } ;
struct TYPE_22__ {int Size; scalar_t__ Buf; scalar_t__ Param1; } ;
struct TYPE_21__ {scalar_t__ DestPort; int UdpSocketCreated; int ProxyDns; scalar_t__ DestIp; scalar_t__ DestIpProxy; scalar_t__ LastCommTime; scalar_t__ SrcIp; scalar_t__ SrcPort; TYPE_5__* Sock; scalar_t__ PublicPort; int /*<<< orphan*/  UdpSendQueue; int /*<<< orphan*/  UdpRecvQueue; scalar_t__ PublicIp; scalar_t__ DisconnectNow; } ;
struct TYPE_20__ {scalar_t__ SrcIP; scalar_t__ SrcPort; } ;
typedef  TYPE_2__ NBTDG_HEADER ;
typedef  TYPE_3__ NAT_ENTRY ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_4__ BLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  DeleteNatUdp (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  Disconnect (TYPE_5__*) ; 
 scalar_t__ Endian16 (scalar_t__) ; 
 int /*<<< orphan*/  FreeBlock (TYPE_4__*) ; 
 int /*<<< orphan*/  FreeHostIPAddressList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetHostIPAddressList () ; 
 TYPE_4__* GetNext (int /*<<< orphan*/ ) ; 
 scalar_t__ IPToUINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  InsertQueue (int /*<<< orphan*/ ,TYPE_4__*) ; 
 scalar_t__ IsIP4 (int /*<<< orphan*/ *) ; 
 int IsLocalHostIP (int /*<<< orphan*/ *) ; 
 int IsZeroIp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JoinSockToSockEvent (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ *) ; 
 scalar_t__ MAX_NUM_IGNORE_ERRORS ; 
 void* Malloc (scalar_t__) ; 
 TYPE_4__* NewBlock (void*,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_5__* NewUDP (int /*<<< orphan*/ ) ; 
 scalar_t__ RecvFrom (TYPE_5__*,int /*<<< orphan*/ *,scalar_t__*,void*,int) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_5__*) ; 
 scalar_t__ SOCK_LATER ; 
 scalar_t__ SPECIAL_UDP_PORT_NBTDGM ; 
 scalar_t__ SPECIAL_UDP_PORT_SSDP ; 
 scalar_t__ SPECIAL_UDP_PORT_WSD ; 
 scalar_t__ SendTo (TYPE_5__*,int /*<<< orphan*/ *,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  UINTToIP (int /*<<< orphan*/ *,scalar_t__) ; 

bool NatTransactUdp(VH *v, NAT_ENTRY *n)
{
	void *buf;
	UINT recv_size;
	BLOCK *block;
	IP dest_ip;
	UINT num_ignore_errors;
	UINT dest_port = 0;
	// Validate arguments
	if (v == NULL || n == NULL)
	{
		return true;
	}

	dest_port = n->DestPort;

	if (n->DisconnectNow)
	{
		goto DISCONNECT;
	}

	if (n->UdpSocketCreated == false)
	{
		// Create a UDP socket
		n->Sock = NewUDP(0);
		if (n->Sock == NULL)
		{
			// Socket creation failure
			goto DISCONNECT;
		}
		else
		{
			n->PublicIp = IPToUINT(&n->Sock->LocalIP);
			n->PublicPort = n->Sock->LocalPort;

			JoinSockToSockEvent(n->Sock, v->SockEvent);
			n->UdpSocketCreated = true;
		}
	}

	buf = v->TmpBuf;
	if (n->ProxyDns == false)
	{
		UINTToIP(&dest_ip, n->DestIp);
	}
	else
	{
		UINTToIP(&dest_ip, n->DestIpProxy);
	}

	num_ignore_errors = 0;

	// Try to receive data from the UDP socket
	while (true)
	{
		IP src_ip;
		UINT src_port;
		recv_size = RecvFrom(n->Sock, &src_ip, &src_port, buf, 65536);

		if (recv_size == SOCK_LATER)
		{
			// Packet has not arrived
			break;
		}
		else if (recv_size == 0)
		{
			// Error?
			if (n->Sock->IgnoreRecvErr == false)
			{
				// A fatal error occurred
				goto DISCONNECT;
			}
			else
			{
				if ((num_ignore_errors++) > MAX_NUM_IGNORE_ERRORS)
				{
					goto DISCONNECT;
				}
			}
		}
		else
		{
			// Packet arrives. Check the source IP
			if (IPToUINT(&src_ip) == n->DestIp || n->DestIp == 0xFFFFFFFF || (IPToUINT(&src_ip) == n->DestIpProxy && n->ProxyDns) && src_port == n->DestPort)
			{
				// Insert to the queue
				void *data = Malloc(recv_size);
				Copy(data, buf, recv_size);
				block = NewBlock(data, recv_size, 0);

				if (block != NULL)
				{
					if (src_port == SPECIAL_UDP_PORT_WSD || src_port == SPECIAL_UDP_PORT_SSDP)
					{
						// Make believe there is a response from the host really in the case of WSD packet
						block->Param1 = IPToUINT(&src_ip);
					}
				}

				InsertQueue(n->UdpRecvQueue, block);
				v->NatDoCancelFlag = true;
				n->LastCommTime = v->Now;
			}
		}
	}

	// Try to send data to the UDP socket
	while (block = GetNext(n->UdpSendQueue))
	{
		UINT send_size;
		bool is_nbtdgm = false;
		LIST *local_ip_list = NULL;
		
		if (dest_port == SPECIAL_UDP_PORT_NBTDGM)
		{
			// Determine whether NetBIOS Datagram packet
			NBTDG_HEADER *nh = (NBTDG_HEADER *)block->Buf;

			if (nh != NULL && block->Size >= sizeof(NBTDG_HEADER))
			{
				if (nh->SrcIP == n->SrcIp && Endian16(nh->SrcPort) == n->SrcPort)
				{
					local_ip_list = GetHostIPAddressList();

					if (local_ip_list != NULL)
					{
						is_nbtdgm = true;
					}
				}
			}
		}

		if (is_nbtdgm == false)
		{
			// Normal UDP packet
			send_size = SendTo(n->Sock, &dest_ip, dest_port, block->Buf, block->Size);
		}
		else
		{
			// IP address and port number is embedded in the NetBIOS Datagram Packet.
			// Transfer by rewriting it properly
			UINT i;

			for (i = 0;i < LIST_NUM(local_ip_list);i++)
			{
				IP *my_ip = LIST_DATA(local_ip_list, i);

				if (IsIP4(my_ip) && IsZeroIp(my_ip) == false && IsLocalHostIP(my_ip) == false)
				{
					NBTDG_HEADER *nh = (NBTDG_HEADER *)block->Buf;

					nh->SrcIP = IPToUINT(my_ip);
					nh->SrcPort = Endian16(n->PublicPort);

					send_size = SendTo(n->Sock, &dest_ip, dest_port, block->Buf, block->Size);
				}
			}
		}

		if (local_ip_list != NULL)
		{
			FreeHostIPAddressList(local_ip_list);
		}

		FreeBlock(block);
		if (send_size == 0)
		{
			// Determining whether a fatal error
			if (n->Sock->IgnoreSendErr == false)
			{
				// A fatal error occurred
				goto DISCONNECT;
			}
		}
		else
		{
			n->LastCommTime = v->Now;
		}
	}

	// Examine whether this session timed-out
	if ((n->LastCommTime + (UINT64)v->NatUdpTimeout) < v->Now || n->LastCommTime > v->Now)
	{
		// Time-out
		goto DISCONNECT;
	}

	return true;

DISCONNECT:
	// Disconnect this session
	if (n->UdpSocketCreated)
	{
		// Close the socket
		Disconnect(n->Sock);
		ReleaseSock(n->Sock);
		n->Sock = NULL;
	}

	// Delete the entry
	DeleteNatUdp(v, n);

	return false;
}