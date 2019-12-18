#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  scalar_t__ UINT ;
struct TYPE_6__ {scalar_t__ Err_IPv4; scalar_t__ Err_IPv6; int /*<<< orphan*/  CurrentIPv6; int /*<<< orphan*/  CurrentIPv4; int /*<<< orphan*/  DnsSuffix; int /*<<< orphan*/  CurrentHostName; int /*<<< orphan*/  CurrentFqdn; } ;
struct TYPE_5__ {int /*<<< orphan*/  Rpc; } ;
typedef  TYPE_1__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_2__ DDNS_CLIENT_STATUS ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CtNewStandard () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int IsEmptyStr (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ScGetDDnsClientStatus (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  _E (scalar_t__) ; 
 int /*<<< orphan*/  _UU (char*) ; 

UINT PsDynamicDnsGetStatus(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	DDNS_CLIENT_STATUS t;

	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));

	// RPC call
	ret = ScGetDDnsClientStatus(ps->Rpc, &t);

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
		wchar_t tmp[MAX_SIZE];

		// FQDN
		if (IsEmptyStr(t.CurrentFqdn) == false)
		{
			StrToUni(tmp, sizeof(tmp), t.CurrentFqdn);
		}
		else
		{
			UniStrCpy(tmp, sizeof(tmp), _UU("SM_DDNS_FQDN_EMPTY"));
		}
		CtInsert(ct, _UU("CMD_DynamicDnsGetStatus_PRINT_FQDN"), tmp);

		// Hostname
		if (IsEmptyStr(t.CurrentHostName) == false)
		{
			StrToUni(tmp, sizeof(tmp), t.CurrentHostName);
		}
		else
		{
			UniStrCpy(tmp, sizeof(tmp), _UU("SM_DDNS_FQDN_EMPTY"));
		}
		CtInsert(ct, _UU("CMD_DynamicDnsGetStatus_PRINT_HOSTNAME"), tmp);

		// Suffix
		if (IsEmptyStr(t.DnsSuffix) == false)
		{
			StrToUni(tmp, sizeof(tmp), t.DnsSuffix);
		}
		else
		{
			UniStrCpy(tmp, sizeof(tmp), _UU("SM_DDNS_FQDN_EMPTY"));
		}
		CtInsert(ct, _UU("CMD_DynamicDnsGetStatus_PRINT_SUFFIX"), tmp);

		// IPv4
		if (t.Err_IPv4 == ERR_NO_ERROR)
		{
			StrToUni(tmp, sizeof(tmp), t.CurrentIPv4);
		}
		else
		{
			UniStrCpy(tmp, sizeof(tmp), _E(t.Err_IPv4));
		}
		CtInsert(ct, _UU("CMD_DynamicDnsGetStatus_PRINT_IPv4"), tmp);

		// IPv6
		if (t.Err_IPv6 == ERR_NO_ERROR)
		{
			StrToUni(tmp, sizeof(tmp), t.CurrentIPv6);
		}
		else
		{
			UniStrCpy(tmp, sizeof(tmp), _E(t.Err_IPv6));
		}
		CtInsert(ct, _UU("CMD_DynamicDnsGetStatus_PRINT_IPv6"), tmp);

		CtFree(ct, c);
	}

	FreeParamValueList(o);

	return 0;
}