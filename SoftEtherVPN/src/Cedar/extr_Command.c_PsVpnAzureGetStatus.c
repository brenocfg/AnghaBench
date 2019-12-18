#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t2 ;
typedef  int /*<<< orphan*/  t ;
typedef  scalar_t__ UINT ;
struct TYPE_8__ {int /*<<< orphan*/  Rpc; } ;
struct TYPE_7__ {scalar_t__ IsConnected; int /*<<< orphan*/  CurrentHostName; scalar_t__ IsEnabled; } ;
typedef  TYPE_1__ RPC_AZURE_STATUS ;
typedef  TYPE_2__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_1__ DDNS_CLIENT_STATUS ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  AZURE_DOMAIN_SUFFIX ; 
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CtNewStandard () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ScGetAzureStatus (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ ScGetDDnsClientStatus (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * _UU (char*) ; 

UINT PsVpnAzureGetStatus(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_AZURE_STATUS t;
	DDNS_CLIENT_STATUS t2;

	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));
	Zero(&t2, sizeof(t2));

	// RPC call
	ret = ScGetAzureStatus(ps->Rpc, &t);

	if (ret == ERR_NO_ERROR)
	{
		ret = ScGetDDnsClientStatus(ps->Rpc, &t2);
	}

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}
	else
	{
		CT *ct = CtNewStandard();

		CtInsert(ct, _UU("CMD_VpnAzureGetStatus_PRINT_ENABLED"), _UU(t.IsEnabled ? "SEC_YES" : "SEC_NO"));

		if (t.IsEnabled)
		{
			wchar_t tmp[MAX_SIZE];

			UniFormat(tmp, sizeof(tmp), L"%S%S", t2.CurrentHostName, AZURE_DOMAIN_SUFFIX);

			CtInsert(ct, _UU("CMD_VpnAzureGetStatus_PRINT_CONNECTED"), _UU(t.IsConnected ? "SEC_YES" : "SEC_NO"));
			CtInsert(ct, _UU("CMD_VpnAzureGetStatus_PRINT_HOSTNAME"), tmp);
		}

		CtFree(ct, c);
	}

	FreeParamValueList(o);

	return 0;
}