#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int USHORT ;
typedef  scalar_t__ UINT ;
typedef  size_t UCHAR ;
struct TYPE_17__ {char* SvcName; size_t RandPortId; scalar_t__ volatile* NatTGlobalUdpPort; int ServerMode; scalar_t__ Port; size_t* SvcNameHash; int Client_IcmpId; int Client_IcmpSeqNo; scalar_t__ Protocol; int NoNatTRegister; void* Thread; TYPE_1__* SockEvent; TYPE_2__* UdpSock; void* IpQueryThread; int /*<<< orphan*/ * ProcRpcRecv; int /*<<< orphan*/ * ProcInterrupts; int /*<<< orphan*/  CurrentRegisterHostname; int /*<<< orphan*/  NatT_SourceIpList; void* NatT_TranId; int /*<<< orphan*/  NewSockQueue; void* NewSockConnectEvent; void* SendPacketList; void* TargetConnectedEvent; void* Param; int /*<<< orphan*/  Lock; int /*<<< orphan*/  Now; void* HaltEvent; void* SessionList; int /*<<< orphan*/  Interrupt; void* NatT_SessionKey; } ;
struct TYPE_16__ {scalar_t__ LocalPort; int /*<<< orphan*/  ref; } ;
struct TYPE_15__ {int /*<<< orphan*/  ref; } ;
typedef  TYPE_1__ SOCK_EVENT ;
typedef  TYPE_2__ SOCK ;
typedef  int /*<<< orphan*/  RUDP_STACK_RPC_RECV_PROC ;
typedef  int /*<<< orphan*/  RUDP_STACK_INTERRUPTS_PROC ;
typedef  TYPE_3__ RUDP_STACK ;
typedef  int /*<<< orphan*/  IP ;

/* Variables and functions */
 int /*<<< orphan*/  AddRef (int /*<<< orphan*/ ) ; 
 scalar_t__ Endian32 (scalar_t__) ; 
 int /*<<< orphan*/  IP_PROTO_ICMPV4 ; 
 scalar_t__ IsEmptyStr (char*) ; 
 int /*<<< orphan*/  JoinSockToSockEvent (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ListenTcpForPopupFirewallDialog () ; 
 scalar_t__ MAKE_SPECIAL_PORT (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MsGetProcessId () ; 
 void* NewEvent () ; 
 int /*<<< orphan*/  NewInterruptManager () ; 
 void* NewList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewListFast (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  NewQueue () ; 
 TYPE_1__* NewSockEvent () ; 
 void* NewThread (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_2__* NewUDP4ForSpecificIp (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_2__* NewUDPEx2 (scalar_t__,int,int /*<<< orphan*/ *) ; 
 TYPE_2__* NewUDPEx2RandMachineAndExePath (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int READ_USHORT (size_t*) ; 
 int /*<<< orphan*/ * RUDPCompareSessionList ; 
 int /*<<< orphan*/  RUDPGetRegisterHostNameByIP (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RUDPIpQueryThread ; 
 int /*<<< orphan*/  RUDPMainThread ; 
 scalar_t__ RUDP_PROTOCOL_DNS ; 
 scalar_t__ RUDP_PROTOCOL_ICMP ; 
 scalar_t__ RUDP_PROTOCOL_UDP ; 
 int Rand32 () ; 
 void* Rand64 () ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha1 (size_t*,...) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 int StrLen (char*) ; 
 int /*<<< orphan*/  StrLower (char*) ; 
 int /*<<< orphan*/  Tick64 () ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int /*<<< orphan*/  WaitThreadInit (void*) ; 
 TYPE_3__* ZeroMalloc (int) ; 
 int /*<<< orphan*/  getpid () ; 
 scalar_t__* rand_port_numbers ; 

RUDP_STACK *NewRUDP(bool server_mode, char *svc_name, RUDP_STACK_INTERRUPTS_PROC *proc_interrupts, RUDP_STACK_RPC_RECV_PROC *proc_rpc_recv, void *param, UINT port, SOCK *sock, SOCK_EVENT *sock_event, bool server_no_natt_register, bool over_dns_mode, IP *client_target_ip, volatile UINT *natt_global_udp_port, UCHAR rand_port_id, IP *listen_ip)
{
	RUDP_STACK *r;
	char tmp[MAX_SIZE];
	UCHAR pid_hash[SHA1_SIZE];
	UINT pid;
	USHORT pid_us;

	// Validate arguments
	if (IsEmptyStr(svc_name))
	{
		return NULL;
	}

	ListenTcpForPopupFirewallDialog();

	if (sock == NULL)
	{
		if (server_mode == false && client_target_ip != NULL)
		{
			sock = NewUDP4ForSpecificIp(client_target_ip, port);
		}
		else
		{
			if (rand_port_id == 0)
			{
				sock = NewUDPEx2(port, false, listen_ip);
			}
			else
			{
				sock = NewUDPEx2RandMachineAndExePath(false, listen_ip, 0, rand_port_id);
			}
		}

		if (sock == NULL)
		{
			return NULL;
		}
	}
	else
	{
		AddRef(sock->ref);
	}

	if (port == 0)
	{
		port = sock->LocalPort;
	}

	if (rand_port_id != 0)
	{
		rand_port_numbers[rand_port_id] = port;
	}

	if (sock_event == NULL)
	{
		sock_event = NewSockEvent();
	}
	else
	{
		AddRef(sock_event->ref);
	}

	r = ZeroMalloc(sizeof(RUDP_STACK));

	r->NatT_SessionKey = Rand64();

	StrCpy(r->SvcName, sizeof(r->SvcName), svc_name);
	r->RandPortId = rand_port_id;
	r->NatTGlobalUdpPort = natt_global_udp_port;
	r->ServerMode = server_mode;
	r->Interrupt = NewInterruptManager();
	r->SessionList = NewList(RUDPCompareSessionList);
	r->UdpSock = sock;
	r->Port = port;
	r->SockEvent = sock_event;
	r->HaltEvent = NewEvent();
	r->Now = Tick64();
	r->Lock = NewLock();
	r->Param = param;
	r->TargetConnectedEvent = NewEvent();
	r->SendPacketList = NewList(NULL);
	r->NewSockConnectEvent = NewEvent();
	r->NewSockQueue = NewQueue();
	r->NatT_TranId = Rand64();

	r->NatT_SourceIpList = NewListFast(NULL);

	StrCpy(tmp, sizeof(tmp), r->SvcName);
	Trim(tmp);
	StrLower(tmp);

	Sha1(r->SvcNameHash, tmp, StrLen(tmp));

	r->Client_IcmpId = (USHORT)(Rand32() % 65534 + 1);
	r->Client_IcmpSeqNo = (USHORT)(Rand32() % 65534 + 1);

	// Determination of the type of the protocol
	r->Protocol = RUDP_PROTOCOL_UDP;
	if (r->Port == MAKE_SPECIAL_PORT(IP_PROTO_ICMPV4))
	{
		r->Protocol = RUDP_PROTOCOL_ICMP;

		// Generate the ICMP ID based on the process ID
#ifdef	OS_WIN32
		pid = (UINT)MsGetProcessId();
#else	// OS_WIN32
		pid = (UINT)getpid();
#endif	// OS_WIN32

		pid = Endian32(pid);
		Sha1(pid_hash, &pid, sizeof(UINT));

		pid_us = READ_USHORT(pid_hash);
		if (pid_us == 0 || pid_us == 0xFFFF)
		{
			pid_us = 1;
		}

		r->Client_IcmpId = pid_us;
	}
	else if (over_dns_mode)
	{
		r->Protocol = RUDP_PROTOCOL_DNS;
	}

	if (r->ServerMode)
	{
		r->NoNatTRegister = server_no_natt_register;

		if (r->Protocol == RUDP_PROTOCOL_ICMP || r->Protocol == RUDP_PROTOCOL_DNS)
		{
			// Never register to the NAT-T server in case of using the DNS or the ICMP
			r->NoNatTRegister = true;
		}
	}

	if (true
		)
	{
		RUDPGetRegisterHostNameByIP(r->CurrentRegisterHostname, sizeof(r->CurrentRegisterHostname), NULL);
	}

	if (r->ServerMode)
	{
		r->ProcInterrupts = proc_interrupts;
		r->ProcRpcRecv = proc_rpc_recv;
	}

	if (r->ServerMode && r->NoNatTRegister == false
		)
	{
		r->IpQueryThread = NewThread(RUDPIpQueryThread, r);
	}

	JoinSockToSockEvent(r->UdpSock, r->SockEvent);

	r->Thread = NewThread(RUDPMainThread, r);
	WaitThreadInit(r->Thread);

	return r;
}