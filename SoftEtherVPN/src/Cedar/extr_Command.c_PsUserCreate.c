#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  random_pass2 ;
typedef  int /*<<< orphan*/  random_pass ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_16__ {int /*<<< orphan*/  (* Write ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_15__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_14__ {int /*<<< orphan*/  Rpc; int /*<<< orphan*/ * HubName; } ;
struct TYPE_13__ {int /*<<< orphan*/  AuthData; int /*<<< orphan*/  AuthType; int /*<<< orphan*/  Name; int /*<<< orphan*/  Note; int /*<<< orphan*/  Realname; int /*<<< orphan*/  GroupName; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_SET_USER ;
typedef  TYPE_2__ PS ;
typedef  TYPE_3__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_4__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  AUTHTYPE_PASSWORD ; 
 int /*<<< orphan*/  AUTHTYPE_RADIUS ; 
 int /*<<< orphan*/ * CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcSetUser (TYPE_1__*) ; 
 int /*<<< orphan*/ * GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetParamUniStr (int /*<<< orphan*/ *,char*) ; 
 int MD5_SIZE ; 
 int /*<<< orphan*/  NewPasswordAuthDataRaw (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NewRadiusAuthData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_4__*,char*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  Rand (int /*<<< orphan*/ *,int) ; 
 int SHA1_SIZE ; 
 scalar_t__ ScCreateUser (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Trim (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 

UINT PsUserCreate(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_SET_USER t;
	// Parameter list that can be specified
	PARAM args[] =
	{
		// "name", prompt_proc, prompt_param, eval_proc, eval_param
		{"[name]", CmdPrompt, _UU("CMD_UserCreate_Prompt_NAME"), CmdEvalNotEmpty, NULL},
		{"GROUP", CmdPrompt, _UU("CMD_UserCreate_Prompt_GROUP"), NULL, NULL},
		{"REALNAME", CmdPrompt, _UU("CMD_UserCreate_Prompt_REALNAME"), NULL, NULL},
		{"NOTE", CmdPrompt, _UU("CMD_UserCreate_Prompt_NOTE"), NULL, NULL},
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
	StrCpy(t.GroupName, sizeof(t.GroupName), GetParamStr(o, "GROUP"));
	UniStrCpy(t.Realname, sizeof(t.Realname), GetParamUniStr(o, "REALNAME"));
	UniStrCpy(t.Note, sizeof(t.Note), GetParamUniStr(o, "NOTE"));

	Trim(t.Name);
	if (StrCmpi(t.Name, "*") == 0)
	{
		t.AuthType = AUTHTYPE_RADIUS;
		t.AuthData = NewRadiusAuthData(NULL);
	}
	else
	{
		UCHAR random_pass[SHA1_SIZE];
		UCHAR random_pass2[MD5_SIZE];

		Rand(random_pass, sizeof(random_pass));
		Rand(random_pass2, sizeof(random_pass2));
		t.AuthType = AUTHTYPE_PASSWORD;
		t.AuthData = NewPasswordAuthDataRaw(random_pass, random_pass2);
	}

	// RPC call
	ret = ScCreateUser(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}

	FreeRpcSetUser(&t);

	FreeParamValueList(o);

	return 0;
}