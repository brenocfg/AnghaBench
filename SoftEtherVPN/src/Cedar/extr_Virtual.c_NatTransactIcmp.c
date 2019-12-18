#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_20__ ;
typedef  struct TYPE_25__   TYPE_1__ ;

/* Type definitions */
struct TYPE_25__ {int NatDoCancelFlag; scalar_t__ Now; void* TmpBuf; int /*<<< orphan*/  SockEvent; scalar_t__ IcmpRawSocketOk; } ;
typedef  TYPE_1__ VH ;
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
struct TYPE_31__ {int IgnoreRecvErr; int IgnoreSendErr; int /*<<< orphan*/  LocalPort; int /*<<< orphan*/  LocalIP; } ;
struct TYPE_30__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; int /*<<< orphan*/  Ttl; } ;
struct TYPE_29__ {int DataSize; scalar_t__ Data; int /*<<< orphan*/  IpAddress; scalar_t__ Ok; } ;
struct TYPE_28__ {scalar_t__ DstIP; } ;
struct TYPE_27__ {scalar_t__ DestPort; int UdpSocketCreated; scalar_t__ LastCommTime; scalar_t__ DestIp; int /*<<< orphan*/ * IcmpThread; TYPE_6__* Sock; TYPE_20__* UdpSendQueue; int /*<<< orphan*/  UdpRecvQueue; int /*<<< orphan*/  SrcPort; TYPE_5__* IcmpResponseBlock; scalar_t__ IcmpTaskFinished; TYPE_5__* IcmpQueryBlock; int /*<<< orphan*/  PublicPort; int /*<<< orphan*/  PublicIp; scalar_t__ DisconnectNow; } ;
struct TYPE_26__ {int num_item; } ;
typedef  TYPE_2__ NAT_ENTRY ;
typedef  TYPE_3__ IPV4_HEADER ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_4__ ICMP_RESULT ;
typedef  TYPE_5__ BLOCK ;

/* Variables and functions */
 scalar_t__ CmpIpAddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Copy (void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  Debug (char*) ; 
 int /*<<< orphan*/  DeleteNatIcmp (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  Disconnect (TYPE_6__*) ; 
 int /*<<< orphan*/  FreeBlock (TYPE_5__*) ; 
 TYPE_5__* GetNext (TYPE_20__*) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  IPToUINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IP_PROTO_ICMPV4 ; 
 int /*<<< orphan*/  IcmpFreeResult (TYPE_4__*) ; 
 TYPE_4__* IcmpParseResult (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,scalar_t__) ; 
 int /*<<< orphan*/  InsertQueue (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  JoinSockToSockEvent (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKE_SPECIAL_PORT (int /*<<< orphan*/ ) ; 
 scalar_t__ MAX_NUM_IGNORE_ERRORS ; 
 void* Malloc (scalar_t__) ; 
 scalar_t__ NAT_ICMP_TIMEOUT ; 
 scalar_t__ NAT_ICMP_TIMEOUT_WITH_API ; 
 int /*<<< orphan*/  NatIcmpThreadProc ; 
 TYPE_5__* NewBlock (void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewThread (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_6__* NewUDP (int /*<<< orphan*/ ) ; 
 scalar_t__ RecvFrom (TYPE_6__*,int /*<<< orphan*/ *,scalar_t__*,void*,int) ; 
 int /*<<< orphan*/  ReleaseSock (TYPE_6__*) ; 
 int /*<<< orphan*/  ReleaseThread (int /*<<< orphan*/ *) ; 
 scalar_t__ SOCK_LATER ; 
 scalar_t__ SendTo (TYPE_6__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetTtl (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UINTToIP (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  WaitThread (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool NatTransactIcmp(VH *v, NAT_ENTRY *n)
{
	void *buf;
	UINT recv_size;
	BLOCK *block;
	IP dest_ip;
	UINT num_ignore_errors = 0;
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

	if (v->IcmpRawSocketOk)
	{
		// Environment that the Raw sockets are available
		if (n->UdpSocketCreated == false)
		{
			// Create a UDP socket
			n->Sock = NewUDP(MAKE_SPECIAL_PORT(IP_PROTO_ICMPV4));
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
	}
	else
	{
		// Create a thread for using ICMP API if Raw sockets are not available
		if (n->IcmpThread == NULL)
		{
			if (n->UdpSendQueue->num_item >= 1)
			{
				// Since UdpSendQueue contains only 1 query, get a first query
				// and create a thread and pass the query to the thread
				BLOCK *block = GetNext(n->UdpSendQueue);

				n->IcmpQueryBlock = block;

				n->IcmpThread = NewThread(NatIcmpThreadProc, n);
			}
		}

		if (n->IcmpTaskFinished)
		{
			if (n->IcmpResponseBlock != NULL)
			{
				// Because there was a response from the thread that calls ICMP API, pass this result to the stack
				block = n->IcmpResponseBlock;
				n->IcmpResponseBlock = NULL;
				InsertQueue(n->UdpRecvQueue, block);
				v->NatDoCancelFlag = true;
				n->LastCommTime = v->Now;
			}
			else
			{
				// Disconnect immediately when it fails
				goto DISCONNECT;
			}
		}

		// Examine whether this session timed-out
		if ((n->LastCommTime + (UINT64)NAT_ICMP_TIMEOUT_WITH_API) < v->Now || n->LastCommTime > v->Now)
		{
			// Time-out
			goto DISCONNECT;
		}

		return true;
	}

	// Following are processed only for if the raw sockets are available
	buf = v->TmpBuf;
	UINTToIP(&dest_ip, n->DestIp);

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
			Debug("ICMP ERROR\n");
			// Error?
			if (n->Sock->IgnoreRecvErr == false)
			{
				// A fatal error occurred
				goto DISCONNECT;
			}
			else
			{
				if ((num_ignore_errors++) >= MAX_NUM_IGNORE_ERRORS)
				{
					goto DISCONNECT;
				}
			}
		}
		else
		{
			// Analyze the arriving packet
			ICMP_RESULT *ret = IcmpParseResult(&dest_ip, n->SrcPort, 0, buf, recv_size);

			if (ret != NULL)
			{
				if ((ret->Ok && CmpIpAddr(&ret->IpAddress, &dest_ip) == 0) ||
					(ret->DataSize >= sizeof(IPV4_HEADER) && ((IPV4_HEADER *)ret->Data)->DstIP == n->DestIp))
				{
					// Insert to the queue
					void *data = Malloc(recv_size);
					Copy(data, buf, recv_size);
					block = NewBlock(data, recv_size, 0);
					InsertQueue(n->UdpRecvQueue, block);
					v->NatDoCancelFlag = true;
					n->LastCommTime = v->Now;
				}

				IcmpFreeResult(ret);
			}
		}
	}

	// Try to send data to the UDP socket
	while (block = GetNext(n->UdpSendQueue))
	{
		// Assemble the Echo header and ICMP header
		UINT send_size;

		SetTtl(n->Sock, block->Ttl);
		send_size = SendTo(n->Sock, &dest_ip, dest_port, block->Buf, block->Size);

		FreeBlock(block);
		if (send_size == 0)
		{
			Debug("ICMP ERROR\n");
			// Determine whether a fatal error
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
	if ((n->LastCommTime + (UINT64)NAT_ICMP_TIMEOUT) < v->Now || n->LastCommTime > v->Now)
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

	// Terminate if the thread has been created
	if (n->IcmpThread != NULL)
	{
		WaitThread(n->IcmpThread, INFINITE);
		ReleaseThread(n->IcmpThread);
		n->IcmpThread = NULL;
	}

	// Delete the entry
	DeleteNatIcmp(v, n);

	return false;
}