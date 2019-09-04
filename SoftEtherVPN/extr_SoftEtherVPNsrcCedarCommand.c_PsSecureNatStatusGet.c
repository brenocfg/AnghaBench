#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  scalar_t__ UINT ;
struct TYPE_14__ {int /*<<< orphan*/  (* Write ) (TYPE_3__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_13__ {int /*<<< orphan*/ * HubName; int /*<<< orphan*/  Rpc; } ;
struct TYPE_12__ {scalar_t__ IsRawIpMode; scalar_t__ IsKernelMode; int /*<<< orphan*/  NumDhcpClients; int /*<<< orphan*/  NumDnsSessions; int /*<<< orphan*/  NumIcmpSessions; int /*<<< orphan*/  NumUdpSessions; int /*<<< orphan*/  NumTcpSessions; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_NAT_STATUS ;
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
 int /*<<< orphan*/  FreeRpcNatStatus (TYPE_1__*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_3__*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ScGetSecureNATStatus (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *) ; 

UINT PsSecureNatStatusGet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_NAT_STATUS t;

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
	ret = ScGetSecureNATStatus(ps->Rpc, &t);

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

		StrToUni(tmp, sizeof(tmp), ps->HubName);
		CtInsert(ct, _UU("SM_HUB_COLUMN_1"), tmp);

		UniFormat(tmp, sizeof(tmp), _UU("SM_SNAT_NUM_SESSION"), t.NumTcpSessions);
		CtInsert(ct, _UU("NM_STATUS_TCP"), tmp);

		UniFormat(tmp, sizeof(tmp), _UU("SM_SNAT_NUM_SESSION"), t.NumUdpSessions);
		CtInsert(ct, _UU("NM_STATUS_UDP"), tmp);

		UniFormat(tmp, sizeof(tmp), _UU("SM_SNAT_NUM_SESSION"), t.NumIcmpSessions);
		CtInsert(ct, _UU("NM_STATUS_ICMP"), tmp);

		UniFormat(tmp, sizeof(tmp), _UU("SM_SNAT_NUM_SESSION"), t.NumDnsSessions);
		CtInsert(ct, _UU("NM_STATUS_DNS"), tmp);

		UniFormat(tmp, sizeof(tmp), _UU("SM_SNAT_NUM_CLIENT"), t.NumDhcpClients);
		CtInsert(ct, _UU("NM_STATUS_DHCP"), tmp);

		CtInsert(ct, _UU("SM_SNAT_IS_KERNEL"), t.IsKernelMode ? _UU("SEC_YES") : _UU("SEC_NO"));
		CtInsert(ct, _UU("SM_SNAT_IS_RAW"), t.IsRawIpMode ? _UU("SEC_YES") : _UU("SEC_NO"));

		CtFree(ct, c);
	}

	FreeRpcNatStatus(&t);

	FreeParamValueList(o);

	return 0;
}