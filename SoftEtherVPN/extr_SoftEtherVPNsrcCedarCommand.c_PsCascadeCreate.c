#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_20__ {int /*<<< orphan*/  (* Write ) (TYPE_6__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_19__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_18__ {char* HubName; int /*<<< orphan*/  Rpc; } ;
struct TYPE_17__ {int Online; TYPE_2__* ClientAuth; TYPE_1__* ClientOption; int /*<<< orphan*/  Policy; int /*<<< orphan*/  HubName; } ;
struct TYPE_16__ {int /*<<< orphan*/  Username; int /*<<< orphan*/  AuthType; } ;
struct TYPE_15__ {int RetryInterval; int MaxConnection; int UseEncrypt; int AdditionalConnectionInterval; int RequireBridgeRoutingMode; int /*<<< orphan*/  NumRetry; int /*<<< orphan*/  HubName; int /*<<< orphan*/  Hostname; scalar_t__ Port; int /*<<< orphan*/  AccountName; } ;
typedef  TYPE_3__ RPC_CREATE_LINK ;
typedef  TYPE_4__ PS ;
typedef  int /*<<< orphan*/  POLICY ;
typedef  TYPE_5__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_6__ CONSOLE ;
typedef  int /*<<< orphan*/  CLIENT_OPTION ;
typedef  int /*<<< orphan*/  CLIENT_AUTH ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_AUTHTYPE_ANONYMOUS ; 
 int /*<<< orphan*/  CmdEvalHostAndPort ; 
 int /*<<< orphan*/  CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdEvalSafe ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcCreateLink (TYPE_3__*) ; 
 int /*<<< orphan*/  GetDefaultPolicy () ; 
 char* GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetParamUniStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_6__*,char*,int /*<<< orphan*/ *,TYPE_5__*,int) ; 
 int /*<<< orphan*/  ParseHostPort (char*,char**,scalar_t__*,int) ; 
 scalar_t__ ScCreateLink (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 
 void* ZeroMalloc (int) ; 
 int /*<<< orphan*/  _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ) ; 

UINT PsCascadeCreate(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_CREATE_LINK t;
	char *host = NULL;
	UINT port = 443;
	// Parameter list that can be specified
	PARAM args[] =
	{
		// "name", prompt_proc, prompt_param, eval_proc, eval_param
		{"[name]", CmdPrompt, _UU("CMD_CascadeCreate_Prompt_Name"), CmdEvalNotEmpty, NULL},
		{"SERVER", CmdPrompt, _UU("CMD_CascadeCreate_Prompt_Server"), CmdEvalHostAndPort, NULL},
		{"HUB", CmdPrompt, _UU("CMD_CascadeCreate_Prompt_Hub"), CmdEvalSafe, NULL},
		{"USERNAME", CmdPrompt, _UU("CMD_CascadeCreate_Prompt_Username"), CmdEvalNotEmpty, NULL},
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

	ParseHostPort(GetParamStr(o, "SERVER"), &host, &port, 443);

	Zero(&t, sizeof(t));
	StrCpy(t.HubName, sizeof(t.HubName), ps->HubName);

	t.Online = false;

	Copy(&t.Policy, GetDefaultPolicy(), sizeof(POLICY));

	t.ClientOption = ZeroMalloc(sizeof(CLIENT_OPTION));
	UniStrCpy(t.ClientOption->AccountName, sizeof(t.ClientOption->AccountName), GetParamUniStr(o, "[name]"));
	t.ClientOption->Port = port;
	StrCpy(t.ClientOption->Hostname, sizeof(t.ClientOption->Hostname), host);
	StrCpy(t.ClientOption->HubName, sizeof(t.ClientOption->HubName), GetParamStr(o, "HUB"));
	t.ClientOption->NumRetry = INFINITE;
	t.ClientOption->RetryInterval = 15;
	t.ClientOption->MaxConnection = 8;
	t.ClientOption->UseEncrypt = true;
	t.ClientOption->AdditionalConnectionInterval = 1;
	t.ClientOption->RequireBridgeRoutingMode = true;

	t.ClientAuth = ZeroMalloc(sizeof(CLIENT_AUTH));
	t.ClientAuth->AuthType = CLIENT_AUTHTYPE_ANONYMOUS;
	StrCpy(t.ClientAuth->Username, sizeof(t.ClientAuth->Username), GetParamStr(o, "USERNAME"));

	Free(host);

	// RPC call
	ret = ScCreateLink(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}

	FreeRpcCreateLink(&t);

	FreeParamValueList(o);

	return 0;
}