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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_11__ {TYPE_1__* Server; } ;
struct TYPE_10__ {scalar_t__ VpnOverIcmpListener; scalar_t__ VpnOverDnsListener; } ;
struct TYPE_9__ {scalar_t__ EnableVpnOverIcmp; scalar_t__ EnableVpnOverDns; int /*<<< orphan*/ * Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_SPECIAL_LISTENER ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_3__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_3__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  ERR_SPECIAL_LISTENER_DNS_ERROR ; 
 int /*<<< orphan*/  ERR_SPECIAL_LISTENER_ICMP_ERROR ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_1__*) ; 
 scalar_t__ MAKEBOOL (scalar_t__) ; 
 int /*<<< orphan*/  NO_SUPPORT_FOR_BRIDGE ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 
 int /*<<< orphan*/  SiApplySpecialListenerStatus (TYPE_1__*) ; 
 int SiCanOpenVpnOverDnsPort () ; 
 int SiCanOpenVpnOverIcmpPort () ; 

UINT StSetSpecialListener(ADMIN *a, RPC_SPECIAL_LISTENER *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	UINT ret = ERR_NO_ERROR;

	SERVER_ADMIN_ONLY;
	NO_SUPPORT_FOR_BRIDGE;

	// Check ports
	if (t->VpnOverDnsListener && (MAKEBOOL(s->EnableVpnOverDns) != MAKEBOOL(t->VpnOverDnsListener)))
	{
		if (SiCanOpenVpnOverDnsPort() == false)
		{
			return ERR_SPECIAL_LISTENER_DNS_ERROR;
		}
	}

	if (t->VpnOverIcmpListener && (MAKEBOOL(s->EnableVpnOverIcmp) != MAKEBOOL(t->VpnOverIcmpListener)))
	{
		if (SiCanOpenVpnOverIcmpPort() == false)
		{
			return ERR_SPECIAL_LISTENER_ICMP_ERROR;
		}
	}

	s->EnableVpnOverDns = t->VpnOverDnsListener;
	s->EnableVpnOverIcmp = t->VpnOverIcmpListener;

	SiApplySpecialListenerStatus(s);

	ALog(a, NULL, "LA_SET_SPECIAL_LISTENER");

	IncrementServerConfigRevision(s);

	return ERR_NO_ERROR;
}