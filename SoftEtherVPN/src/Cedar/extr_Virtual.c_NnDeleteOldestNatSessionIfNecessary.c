#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_9__ {int SecureNAT_MaxTcpSessionsPerIp; int SecureNAT_MaxUdpSessionsPerIp; int SecureNAT_MaxIcmpSessionsPerIp; } ;
struct TYPE_8__ {TYPE_1__* v; } ;
struct TYPE_7__ {TYPE_3__* HubOption; } ;
typedef  TYPE_2__ NATIVE_NAT ;
typedef  TYPE_3__ HUB_OPTION ;

/* Variables and functions */
#define  NAT_ICMP 130 
#define  NAT_TCP 129 
#define  NAT_UDP 128 
 int /*<<< orphan*/  NnDeleteOldestNatSession (TYPE_2__*,int,int) ; 
 int NnGetNumNatEntriesPerIp (TYPE_2__*,int,int) ; 

void NnDeleteOldestNatSessionIfNecessary(NATIVE_NAT *t, UINT ip, UINT protocol)
{
	UINT current_num;
	UINT max_sessions = 0;
	// Validate arguments
	if (t == NULL)
	{
		return;
	}

	if (t->v->HubOption != NULL)
	{
		HUB_OPTION *o = t->v->HubOption;

		switch (protocol)
		{
		case NAT_TCP:
			max_sessions = o->SecureNAT_MaxTcpSessionsPerIp;
			break;

		case NAT_UDP:
			max_sessions = o->SecureNAT_MaxUdpSessionsPerIp;
			break;

		case NAT_ICMP:
			max_sessions = o->SecureNAT_MaxIcmpSessionsPerIp;
			break;
		}
	}

	if (max_sessions == 0)
	{
		return;
	}

	current_num = NnGetNumNatEntriesPerIp(t, ip, protocol);

	if (current_num >= max_sessions)
	{
		NnDeleteOldestNatSession(t, ip, protocol);
	}
}