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
struct TYPE_17__ {int /*<<< orphan*/  NatTable; int /*<<< orphan*/  TcpMss; int /*<<< orphan*/  Now; int /*<<< orphan*/  Counter; } ;
typedef  TYPE_1__ VH ;
typedef  void* UINT ;
struct TYPE_19__ {scalar_t__ SecureNAT_MaxTcpSynSentPerIp; scalar_t__ SecureNAT_MaxTcpSessionsPerIp; } ;
struct TYPE_18__ {int DisconnectNow; int CurrentRTT; int TcpSendTimeoutSpan; int /*<<< orphan*/  Id; int /*<<< orphan*/  SendSeqInit; int /*<<< orphan*/  TcpStatus; void* RecvFifo; void* SendFifo; int /*<<< orphan*/  TcpRecvMaxSegmentSize; int /*<<< orphan*/  TcpSendMaxSegmentSize; int /*<<< orphan*/ * Sock; int /*<<< orphan*/  TcpLastRecvAckTime; int /*<<< orphan*/  LastCommTime; int /*<<< orphan*/  CreatedTime; void* DestPort; void* DestIp; void* SrcPort; void* SrcIp; int /*<<< orphan*/  Protocol; int /*<<< orphan*/  lock; TYPE_1__* v; } ;
typedef  TYPE_2__ NAT_ENTRY ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_3__ HUB_OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int CanCreateNewNatEntry (TYPE_1__*) ; 
 int /*<<< orphan*/  Debug (char*,char*,void*,char*,void*) ; 
 int /*<<< orphan*/  DisconnectNatEntryNow (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ GetNumNatEntriesPerIp (TYPE_1__*,void*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* GetOldestNatEntryOfIp (TYPE_1__*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPToStr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Inc (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int NAT_INITIAL_RTT_VALUE ; 
 int /*<<< orphan*/  NAT_TCP ; 
 int /*<<< orphan*/  NAT_TCP_CONNECTING ; 
 int /*<<< orphan*/  NLog (TYPE_1__*,char*,int /*<<< orphan*/ ,char*,void*,char*,void*) ; 
 TYPE_3__* NatGetHubOption (TYPE_1__*) ; 
 void* NewFifo () ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  Rand32 () ; 
 int /*<<< orphan*/  UINTToIP (int /*<<< orphan*/ *,void*) ; 
 TYPE_2__* ZeroMalloc (int) ; 

NAT_ENTRY *CreateNatTcp(VH *v, UINT src_ip, UINT src_port, UINT dest_ip, UINT dest_port)
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

	// Fail immediately if the connection with SYN_SENT are too many
	if (o != NULL && o->SecureNAT_MaxTcpSynSentPerIp != 0)
	{
		if (GetNumNatEntriesPerIp(v, src_ip, NAT_TCP, true) >= o->SecureNAT_MaxTcpSynSentPerIp)
		{
			return NULL;
		}
	}

	// If the connections other than SYN_SENT are too many, delete old ones 
	if (o != NULL && o->SecureNAT_MaxTcpSessionsPerIp != 0)
	{
		if (GetNumNatEntriesPerIp(v, src_ip, NAT_TCP, false) >= o->SecureNAT_MaxTcpSessionsPerIp)
		{
			NAT_ENTRY *oldest = GetOldestNatEntryOfIp(v, src_ip, NAT_TCP);

			if (oldest != NULL)
			{
				DisconnectNatEntryNow(v, oldest);
			}
		}
	}

	// Create a NAT entry
	n = ZeroMalloc(sizeof(NAT_ENTRY));
	n->Id = Inc(v->Counter);
	n->v = v;
	n->lock = NewLock();
	n->Protocol = NAT_TCP;
	n->SrcIp = src_ip;
	n->SrcPort = src_port;
	n->DestIp = dest_ip;
	n->DestPort = dest_port;
	n->CreatedTime = n->LastCommTime = v->Now;
	n->TcpLastRecvAckTime = v->Now;
	n->Sock = NULL;
	n->DisconnectNow = false;
	n->TcpSendMaxSegmentSize = n->TcpRecvMaxSegmentSize = v->TcpMss;

	n->SendFifo = NewFifo();
	n->RecvFifo = NewFifo();

	n->TcpStatus = NAT_TCP_CONNECTING;

	n->SendSeqInit = Rand32();
	n->CurrentRTT = NAT_INITIAL_RTT_VALUE;
	n->TcpSendTimeoutSpan = n->CurrentRTT * 2;

	// Add to the NAT table
	Add(v->NatTable, n);


#if	1
	{
		IP ip1, ip2;
		char s1[MAX_SIZE], s2[MAX_SIZE];
		UINTToIP(&ip1, src_ip);
		UINTToIP(&ip2, dest_ip);
		IPToStr(s1, 0, &ip1);
		IPToStr(s2, 0, &ip2);
		Debug("NAT_ENTRY: CreateNatTcp %s %u -> %s %u\n", s1, src_port, s2, dest_port);

		NLog(v, "LH_NAT_TCP_CREATED", n->Id, s1, src_port, s2, dest_port);
	}
#endif

	return n;
}