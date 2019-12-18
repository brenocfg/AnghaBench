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
struct TYPE_6__ {int /*<<< orphan*/  L2TP_DefaultHub; int /*<<< orphan*/  IPsec_Secret; scalar_t__ EtherIP_IPsec; scalar_t__ L2TP_Raw; scalar_t__ L2TP_IPsec; } ;
struct TYPE_5__ {int /*<<< orphan*/  Rpc; } ;
typedef  TYPE_1__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_2__ IPSEC_SERVICES ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CtNewStandard () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ScGetIPsecServices (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * _UU (char*) ; 

UINT PsIPsecGet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	IPSEC_SERVICES t;

	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));

	// RPC call
	ret = ScGetIPsecServices(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}
	else
	{
		wchar_t tmp[MAX_PATH];
		CT *ct = CtNewStandard();

		CtInsert(ct, _UU("CMD_IPsecGet_PRINT_L2TP"), _UU(t.L2TP_IPsec ? "SEC_YES" : "SEC_NO"));
		CtInsert(ct, _UU("CMD_IPsecGet_PRINT_L2TPRAW"), _UU(t.L2TP_Raw ? "SEC_YES" : "SEC_NO"));
		CtInsert(ct, _UU("CMD_IPsecGet_PRINT_ETHERIP"), _UU(t.EtherIP_IPsec ? "SEC_YES" : "SEC_NO"));

		StrToUni(tmp, sizeof(tmp), t.IPsec_Secret);
		CtInsert(ct, _UU("CMD_IPsecGet_PRINT_PSK"), tmp);

		StrToUni(tmp, sizeof(tmp), t.L2TP_DefaultHub);
		CtInsert(ct, _UU("CMD_IPsecGet_PRINT_DEFAULTHUB"), tmp);

		CtFree(ct, c);
	}

	FreeParamValueList(o);

	return 0;
}