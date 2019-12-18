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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_8__ {int /*<<< orphan*/  Rpc; } ;
struct TYPE_7__ {int ServerVer; int ClientVer; int /*<<< orphan*/  ClientBuild; int /*<<< orphan*/  ClientStr; int /*<<< orphan*/  ServerBuild; int /*<<< orphan*/  ServerStr; int /*<<< orphan*/  ConnectedTime; int /*<<< orphan*/  Port; int /*<<< orphan*/  Hostname; int /*<<< orphan*/  Type; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ RPC_CONNECTION_INFO ;
typedef  TYPE_2__ PS ;
typedef  TYPE_3__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CtNewStandard () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetConnectionTypeStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDateTimeStrEx64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 scalar_t__ ScGetConnectionInfo (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ StrLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemToLocal64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniFormat (int /*<<< orphan*/ *,int,char*,int,int) ; 
 int /*<<< orphan*/  UniToStru (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 

UINT PsConnectionGet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_CONNECTION_INFO t;
	CT *ct;
	wchar_t tmp[MAX_SIZE];
	// Parameter list that can be specified
	PARAM args[] =
	{
		{"[name]", CmdPrompt, _UU("CMD_ConnectionGet_PROMPT_NAME"), CmdEvalNotEmpty, NULL},
	};

	o = ParseCommandList(c, cmd_name, str, args, sizeof(args) / sizeof(args[0]));
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));

	StrCpy(t.Name, sizeof(t.Name), GetParamStr(o, "[name]"));

	// RPC call
	ret = ScGetConnectionInfo(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}
	else
	{
		ct = CtNewStandard();

		StrToUni(tmp, sizeof(tmp), t.Name);
		CtInsert(ct, _UU("SM_CONNINFO_NAME"), tmp);

		CtInsert(ct, _UU("SM_CONNINFO_TYPE"), GetConnectionTypeStr(t.Type));

		StrToUni(tmp, sizeof(tmp), t.Hostname);
		CtInsert(ct, _UU("SM_CONNINFO_HOSTNAME"), tmp);

		UniToStru(tmp, t.Port);
		CtInsert(ct, _UU("SM_CONNINFO_PORT"), tmp);

		GetDateTimeStrEx64(tmp, sizeof(tmp), SystemToLocal64(t.ConnectedTime), NULL);
		CtInsert(ct, _UU("SM_CONNINFO_TIME"), tmp);

		StrToUni(tmp, sizeof(tmp), t.ServerStr);
		CtInsert(ct, _UU("SM_CONNINFO_SERVER_STR"), tmp);

		UniFormat(tmp, sizeof(tmp), L"%u.%02u", t.ServerVer / 100, t.ServerVer % 100);
		CtInsert(ct, _UU("SM_CONNINFO_SERVER_VER"), tmp);

		UniToStru(tmp, t.ServerBuild);
		CtInsert(ct, _UU("SM_CONNINFO_SERVER_BUILD"), tmp);

		if (StrLen(t.ClientStr) != 0)
		{
			StrToUni(tmp, sizeof(tmp), t.ClientStr);
			CtInsert(ct, _UU("SM_CONNINFO_CLIENT_STR"), tmp);

			UniFormat(tmp, sizeof(tmp), L"%u.%02u", t.ClientVer / 100, t.ClientVer % 100);
			CtInsert(ct, _UU("SM_CONNINFO_CLIENT_VER"), tmp);

			UniToStru(tmp, t.ClientBuild);
			CtInsert(ct, _UU("SM_CONNINFO_CLIENT_BUILD"), tmp);
		}

		CtFree(ct, c);
	}

	FreeParamValueList(o);

	return 0;
}