#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_20__ {int /*<<< orphan*/ * UserX; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* Write ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_18__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_17__ {int /*<<< orphan*/  Rpc; int /*<<< orphan*/ * HubName; } ;
struct TYPE_16__ {scalar_t__ AuthType; scalar_t__ AuthData; int /*<<< orphan*/  Name; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_SET_USER ;
typedef  TYPE_2__ PS ;
typedef  TYPE_3__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_4__ CONSOLE ;
typedef  TYPE_5__ AUTHUSERCERT ;

/* Variables and functions */
 scalar_t__ AUTHTYPE_USERCERT ; 
 int /*<<< orphan*/ * CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcSetUser (TYPE_1__*) ; 
 int /*<<< orphan*/ * GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetParamUniStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_4__*,char*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 scalar_t__ ScGetUser (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int XToFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*,int /*<<< orphan*/ ) ; 

UINT PsUserCertGet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_SET_USER t;
	AUTHUSERCERT *a;
	// Parameter list that can be specified
	PARAM args[] =
	{
		// "name", prompt_proc, prompt_param, eval_proc, eval_param
		{"[name]", CmdPrompt, _UU("CMD_UserCreate_Prompt_NAME"), CmdEvalNotEmpty, NULL},
		{"SAVECERT", CmdPrompt, _UU("CMD_SAVECERTPATH"), NULL, NULL},
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
	// Get the user object
	StrCpy(t.HubName, sizeof(t.HubName), ps->HubName);
	StrCpy(t.Name, sizeof(t.Name), GetParamStr(o, "[name]"));

	ret = ScGetUser(ps->Rpc, &t);
	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}

	a = (AUTHUSERCERT *)t.AuthData;

	if (t.AuthType != AUTHTYPE_USERCERT || a == NULL || a->UserX == NULL)
	{
		// The user is not using specific certificate authentication
		ret = ERR_INVALID_PARAMETER;

		c->Write(c, _UU("CMD_UserCertGet_Not_Cert"));
	}
	else
	{
		if (XToFileW(a->UserX, GetParamUniStr(o, "SAVECERT"), true) == false)
		{
			c->Write(c, _UU("CMD_SAVECERT_FAILED"));
		}
	}

	FreeRpcSetUser(&t);

	FreeParamValueList(o);

	return ret;
}