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
struct TYPE_6__ {int /*<<< orphan*/  RemoteClient; } ;
struct TYPE_5__ {int /*<<< orphan*/  OsType; int /*<<< orphan*/  ProcessId; int /*<<< orphan*/  ClientBuildInfoString; int /*<<< orphan*/  ClientVersionString; int /*<<< orphan*/  ClientProductName; } ;
typedef  TYPE_1__ RPC_CLIENT_VERSION ;
typedef  TYPE_2__ PC ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 scalar_t__ CcGetClientVersion (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CtNewStandard () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  OsTypeToStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniToStru (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 

UINT PcVersionGet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PC *pc = (PC *)param;
	UINT ret = ERR_NO_ERROR;
	RPC_CLIENT_VERSION t;

	// Get the parameter list
	o = ParseCommandList(c, cmd_name, str, NULL, 0);
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	// RPC call
	Zero(&t, sizeof(t));

	ret = CcGetClientVersion(pc->RemoteClient, &t);

	if (ret == ERR_NO_ERROR)
	{
		wchar_t tmp[MAX_SIZE];
		CT *ct;

		// Success
		ct = CtNewStandard();

		StrToUni(tmp, sizeof(tmp), t.ClientProductName);
		CtInsert(ct, _UU("CMD_VersionGet_1"), tmp);

		StrToUni(tmp, sizeof(tmp), t.ClientVersionString);
		CtInsert(ct, _UU("CMD_VersionGet_2"), tmp);

		StrToUni(tmp, sizeof(tmp), t.ClientBuildInfoString);
		CtInsert(ct, _UU("CMD_VersionGet_3"), tmp);

		UniToStru(tmp, t.ProcessId);
		CtInsert(ct, _UU("CMD_VersionGet_4"), tmp);

		StrToUni(tmp, sizeof(tmp), OsTypeToStr(t.OsType));
		CtInsert(ct, _UU("CMD_VersionGet_5"), tmp);

		CtFree(ct, c);
	}

	if (ret != ERR_NO_ERROR)
	{
		// Error has occurred
		CmdPrintError(c, ret);
	}

	// Release the parameter list
	FreeParamValueList(o);

	return ret;
}