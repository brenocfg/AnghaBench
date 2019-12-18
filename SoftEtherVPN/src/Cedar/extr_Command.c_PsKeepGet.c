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
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  scalar_t__ UINT ;
struct TYPE_6__ {int /*<<< orphan*/  Rpc; } ;
struct TYPE_5__ {scalar_t__ KeepConnectProtocol; scalar_t__ UseKeepConnect; int /*<<< orphan*/  KeepConnectInterval; int /*<<< orphan*/  KeepConnectPort; int /*<<< orphan*/  KeepConnectHost; } ;
typedef  TYPE_1__ RPC_KEEP ;
typedef  TYPE_2__ PS ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * CtNewStandard () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ScGetKeep (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrToUni (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniToStru (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 char* _UU (char*) ; 

UINT PsKeepGet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_KEEP t;

	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));

	// RPC call
	ret = ScGetKeep(ps->Rpc, &t);

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

		StrToUni(tmp, sizeof(tmp), t.KeepConnectHost);
		CtInsert(ct, _UU("CMD_KeepGet_COLUMN_1"), tmp);

		UniToStru(tmp, t.KeepConnectPort);
		CtInsert(ct, _UU("CMD_KeepGet_COLUMN_2"), tmp);

		UniToStru(tmp, t.KeepConnectInterval);
		CtInsert(ct, _UU("CMD_KeepGet_COLUMN_3"), tmp);

		CtInsert(ct, _UU("CMD_KeepGet_COLUMN_4"),
			t.KeepConnectProtocol == 0 ? L"TCP/IP" : L"UDP/IP");

		CtInsert(ct, _UU("CMD_KeepGet_COLUMN_5"),
			t.UseKeepConnect ? _UU("SM_ACCESS_ENABLE") : _UU("SM_ACCESS_DISABLE"));

		CtFree(ct, c);
	}

	FreeParamValueList(o);

	return 0;
}