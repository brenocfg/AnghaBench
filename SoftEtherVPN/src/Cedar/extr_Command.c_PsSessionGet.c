#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  str ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_17__ {int /*<<< orphan*/  (* Write ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_16__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_15__ {int /*<<< orphan*/  Rpc; int /*<<< orphan*/ * HubName; } ;
struct TYPE_14__ {char* ClientHostName; char* Username; char* RealUsername; char* GroupName; int /*<<< orphan*/  NodeInfo; int /*<<< orphan*/  Status; int /*<<< orphan*/  ClientIp6; int /*<<< orphan*/  ClientIp; int /*<<< orphan*/  Name; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_SESSION_STATUS ;
typedef  TYPE_2__ PS ;
typedef  TYPE_3__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  TYPE_4__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  BRIDGE_USER_NAME_PRINT ; 
 int /*<<< orphan*/  CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrintNodeInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CmdPrintStatusToListViewEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CtNewStandard () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcSessionStatus (TYPE_1__*) ; 
 int /*<<< orphan*/ * GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  IPToStr4or6 (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int IsEmptyStr (char*) ; 
 int /*<<< orphan*/  L3_USERNAME ; 
 int /*<<< orphan*/  LINK_USER_NAME_PRINT ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_4__*,char*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  SNAT_USER_NAME_PRINT ; 
 scalar_t__ ScGetSessionStatus (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int StartWith (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ StrCmpi (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ StrLen (char*) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 

UINT PsSessionGet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_SESSION_STATUS t;
	// Parameter list that can be specified
	PARAM args[] =
	{
		// "name", prompt_proc, prompt_param, eval_proc, eval_param
		{"[name]", CmdPrompt, _UU("CMD_SessionGet_Prompt_NAME"), CmdEvalNotEmpty, NULL},
	};

	// If virtual HUB is not selected, it's an error
	if (ps->HubName == NULL)
	{
		c->Write(c, _UU("CMD_Hub_Not_Selected"));
		return ERR_INVALID_PARAMETER;
	}

	o = ParseCommandList(c, cmd_name, str, args, sizeof(args) / sizeof(args[0]));
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));
	StrCpy(t.HubName, sizeof(t.HubName), ps->HubName);
	StrCpy(t.Name, sizeof(t.Name), GetParamStr(o, "[name]"));

	// RPC call
	ret = ScGetSessionStatus(ps->Rpc, &t);

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
		char str[MAX_SIZE];
		CT *ct = CtNewStandard();

		if (t.ClientIp != 0)
		{
			IPToStr4or6(str, sizeof(str), t.ClientIp, t.ClientIp6);
			StrToUni(tmp, sizeof(tmp), str);
			CtInsert(ct, _UU("SM_CLIENT_IP"), tmp);
		}

		if (StrLen(t.ClientHostName) != 0)
		{
			StrToUni(tmp, sizeof(tmp), t.ClientHostName);
			CtInsert(ct, _UU("SM_CLIENT_HOSTNAME"), tmp);
		}

		StrToUni(tmp, sizeof(tmp), t.Username);
		CtInsert(ct, _UU("SM_SESS_STATUS_USERNAME"), tmp);

		if (StrCmpi(t.Username, LINK_USER_NAME_PRINT) != 0 && StrCmpi(t.Username, SNAT_USER_NAME_PRINT) != 0 && StrCmpi(t.Username, BRIDGE_USER_NAME_PRINT) != 0)
		{
			StrToUni(tmp, sizeof(tmp), t.RealUsername);
			CtInsert(ct, _UU("SM_SESS_STATUS_REALUSER"), tmp);
		}

		if (IsEmptyStr(t.GroupName) == false)
		{
			StrToUni(tmp, sizeof(tmp), t.GroupName);
			CtInsert(ct, _UU("SM_SESS_STATUS_GROUPNAME"), tmp);
		}


		CmdPrintStatusToListViewEx(ct, &t.Status, true);

		if (StrCmpi(t.Username, LINK_USER_NAME_PRINT) != 0 && StrCmpi(t.Username, SNAT_USER_NAME_PRINT) != 0 && StrCmpi(t.Username, BRIDGE_USER_NAME_PRINT) != 0 &&
			StartWith(t.Username, L3_USERNAME) == false)
		{
			CmdPrintNodeInfo(ct, &t.NodeInfo);
		}

		CtFree(ct, c);
	}

	FreeRpcSessionStatus(&t);

	FreeParamValueList(o);

	return 0;
}