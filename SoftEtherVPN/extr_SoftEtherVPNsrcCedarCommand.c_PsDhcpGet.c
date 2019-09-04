#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
struct TYPE_11__ {int /*<<< orphan*/  DhcpPushRoutes; scalar_t__ ApplyDhcpPushRoutes; scalar_t__ SaveLog; int /*<<< orphan*/  DhcpDomainName; int /*<<< orphan*/  DhcpDnsServerAddress2; int /*<<< orphan*/  DhcpDnsServerAddress; int /*<<< orphan*/  DhcpGatewayAddress; int /*<<< orphan*/  DhcpExpireTimeSpan; int /*<<< orphan*/  DhcpSubnetMask; int /*<<< orphan*/  DhcpLeaseIPEnd; int /*<<< orphan*/  DhcpLeaseIPStart; scalar_t__ UseDhcp; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ VH_OPTION ;
typedef  scalar_t__ UINT ;
struct TYPE_13__ {int /*<<< orphan*/  (* Write ) (TYPE_3__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  Rpc; int /*<<< orphan*/ * HubName; } ;
typedef  TYPE_2__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  TYPE_3__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CtNewStandard () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 scalar_t__ IPToUINT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPToUniStr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_3__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ScGetSecureNATOption (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniToStru (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *) ; 

UINT PsDhcpGet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	VH_OPTION t;

	// If virtual HUB is not selected, it's an error
	if (ps->HubName == NULL)
	{
		c->Write(c, _UU("CMD_Hub_Not_Selected"));
		return ERR_INVALID_PARAMETER;
	}

	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));
	StrCpy(t.HubName, sizeof(t.HubName), ps->HubName);

	// RPC call
	ret = ScGetSecureNATOption(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}
	else
	{
		wchar_t tmp[MAX_SIZE];
		CT *ct = CtNewStandard();

		// To use the virtual DHCP function
		CtInsert(ct, _UU("CMD_DhcpGet_Column_USE"), t.UseDhcp ? _UU("SEC_YES") : _UU("SEC_NO"));

		// Start address of the distributing address zone
		IPToUniStr(tmp, sizeof(tmp), &t.DhcpLeaseIPStart);
		CtInsert(ct, _UU("CMD_DhcpGet_Column_IP1"), tmp);

		// End address of the distributing address zone
		IPToUniStr(tmp, sizeof(tmp), &t.DhcpLeaseIPEnd);
		CtInsert(ct, _UU("CMD_DhcpGet_Column_IP2"), tmp);

		// Subnet mask
		IPToUniStr(tmp, sizeof(tmp), &t.DhcpSubnetMask);
		CtInsert(ct, _UU("CMD_DhcpGet_Column_MASK"), tmp);

		// Lease time (in seconds)
		UniToStru(tmp, t.DhcpExpireTimeSpan);
		CtInsert(ct, _UU("CMD_DhcpGet_Column_LEASE"), tmp);

		// Default gateway address
		UniStrCpy(tmp, sizeof(tmp), _UU("SEC_NONE"));
		if (IPToUINT(&t.DhcpGatewayAddress) != 0)
		{
			IPToUniStr(tmp, sizeof(tmp), &t.DhcpGatewayAddress);
		}
		CtInsert(ct, _UU("CMD_DhcpGet_Column_GW"), tmp);

		// DNS server address 1
		UniStrCpy(tmp, sizeof(tmp), _UU("SEC_NONE"));
		if (IPToUINT(&t.DhcpDnsServerAddress) != 0)
		{
			IPToUniStr(tmp, sizeof(tmp), &t.DhcpDnsServerAddress);
		}
		CtInsert(ct, _UU("CMD_DhcpGet_Column_DNS"), tmp);

		// DNS server address 2
		UniStrCpy(tmp, sizeof(tmp), _UU("SEC_NONE"));
		if (IPToUINT(&t.DhcpDnsServerAddress2) != 0)
		{
			IPToUniStr(tmp, sizeof(tmp), &t.DhcpDnsServerAddress2);
		}
		CtInsert(ct, _UU("CMD_DhcpGet_Column_DNS2"), tmp);

		// Domain name
		StrToUni(tmp, sizeof(tmp), t.DhcpDomainName);
		CtInsert(ct, _UU("CMD_DhcpGet_Column_DOMAIN"), tmp);

		// To save the log
		CtInsert(ct, _UU("CMD_SecureNatHostGet_Column_LOG"), t.SaveLog ? _UU("SEC_YES") : _UU("SEC_NO"));

		// Push routing table
		if (t.ApplyDhcpPushRoutes)
		{
			StrToUni(tmp, sizeof(tmp), t.DhcpPushRoutes);
			CtInsert(ct, _UU("CMD_DhcpGet_Column_PUSHROUTE"), tmp);
		}

		CtFree(ct, c);
	}

	FreeParamValueList(o);

	return 0;
}