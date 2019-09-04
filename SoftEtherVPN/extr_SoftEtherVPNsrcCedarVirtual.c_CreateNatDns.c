#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  NatTable; int /*<<< orphan*/  Now; int /*<<< orphan*/  Counter; } ;
typedef  TYPE_1__ VH ;
typedef  void* UINT ;
struct TYPE_18__ {scalar_t__ SecureNAT_MaxDnsSessionsPerIp; } ;
struct TYPE_17__ {int DisconnectNow; int DnsGetIpFromHost; int /*<<< orphan*/  DnsTargetHostName; int /*<<< orphan*/  LastCommTime; int /*<<< orphan*/  CreatedTime; void* DnsTransactionId; void* DestPort; void* DestIp; void* SrcPort; void* SrcIp; int /*<<< orphan*/  Protocol; int /*<<< orphan*/  lock; TYPE_1__* v; int /*<<< orphan*/  Id; } ;
typedef  TYPE_2__ NAT_ENTRY ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_3__ HUB_OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int CanCreateNewNatEntry (TYPE_1__*) ; 
 int /*<<< orphan*/  CopyStr (char*) ; 
 int /*<<< orphan*/  Debug (char*,char*,void*,char*,void*) ; 
 int /*<<< orphan*/  DisconnectNatEntryNow (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ GetNumNatEntriesPerIp (TYPE_1__*,void*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* GetOldestNatEntryOfIp (TYPE_1__*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPToStr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Inc (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  NAT_DNS ; 
 TYPE_3__* NatGetHubOption (TYPE_1__*) ; 
 int /*<<< orphan*/  NewLock () ; 
 int /*<<< orphan*/  UINTToIP (int /*<<< orphan*/ *,void*) ; 
 TYPE_2__* ZeroMalloc (int) ; 

NAT_ENTRY *CreateNatDns(VH *v, UINT src_ip, UINT src_port, UINT dest_ip, UINT dest_port,
				  UINT transaction_id, bool dns_get_ip_from_host, char *dns_target_host_name)
{
	NAT_ENTRY *n;
	HUB_OPTION *o;
	// Validate arguments
	if (v == NULL || dns_target_host_name == NULL)
	{
		return NULL;
	}

	if (CanCreateNewNatEntry(v) == false)
	{
		return NULL;
	}

	o = NatGetHubOption(v);
	if (o != NULL && o->SecureNAT_MaxDnsSessionsPerIp != 0)
	{
		if (GetNumNatEntriesPerIp(v, src_ip, NAT_DNS, false) >= o->SecureNAT_MaxDnsSessionsPerIp)
		{
			NAT_ENTRY *oldest = GetOldestNatEntryOfIp(v, src_ip, NAT_DNS);

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
	n->Protocol = NAT_DNS;
	n->SrcIp = src_ip;
	n->SrcPort = src_port;
	n->DestIp = dest_ip;
	n->DestPort = dest_port;
	n->DnsTransactionId = transaction_id;
	n->CreatedTime = n->LastCommTime = v->Now;
	n->DisconnectNow = false;

	n->DnsGetIpFromHost = false;
	n->DnsTargetHostName = CopyStr(dns_target_host_name);

	Add(v->NatTable, n);

#if	1
	{
		IP ip1, ip2;
		char s1[MAX_SIZE], s2[MAX_SIZE];
		UINTToIP(&ip1, src_ip);
		UINTToIP(&ip2, dest_ip);
		IPToStr(s1, 0, &ip1);
		IPToStr(s2, 0, &ip2);
		Debug("NAT_ENTRY: CreateNatDns %s %u -> %s %u\n", s1, src_port, s2, dest_port);
	}
#endif


	return n;
}