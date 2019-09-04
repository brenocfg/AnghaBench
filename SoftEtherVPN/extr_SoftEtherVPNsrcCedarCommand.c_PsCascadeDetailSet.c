#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
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
struct TYPE_21__ {void* DisableQoS; void* HalfConnection; void* ConnectionDisconnectSpan; void* AdditionalConnectionInterval; void* MaxConnection; int /*<<< orphan*/  AccountName; } ;
struct TYPE_20__ {char* member_0; int member_1; int member_2; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* Write ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_18__ {char* member_0; TYPE_5__* member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_17__ {int /*<<< orphan*/  Rpc; int /*<<< orphan*/ * HubName; } ;
struct TYPE_16__ {TYPE_7__* ClientOption; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_CREATE_LINK ;
typedef  TYPE_2__ PS ;
typedef  TYPE_3__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_4__ CONSOLE ;
typedef  TYPE_5__ CMD_EVAL_MIN_MAX ;
typedef  int /*<<< orphan*/  CLIENT_OPTION ;

/* Variables and functions */
 int /*<<< orphan*/ * CmdEvalMinMax ; 
 int /*<<< orphan*/ * CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcCreateLink (TYPE_1__*) ; 
 void* GetParamInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetParamUniStr (int /*<<< orphan*/ *,char*) ; 
 void* GetParamYes (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_4__*,char*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 scalar_t__ ScGetLink (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ ScSetLink (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 TYPE_7__* ZeroMalloc (int) ; 
 int /*<<< orphan*/  _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 

UINT PsCascadeDetailSet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_CREATE_LINK t;
	CMD_EVAL_MIN_MAX mm_maxtcp =
	{
		"CMD_CascadeDetailSet_Eval_MaxTcp", 1, 32
	};
	CMD_EVAL_MIN_MAX mm_interval =
	{
		"CMD_CascadeDetailSet_Eval_Interval", 1, 4294967295UL
	};
	// Parameter list that can be specified
	PARAM args[] =
	{
		// "name", prompt_proc, prompt_param, eval_proc, eval_param
		{"[name]", CmdPrompt, _UU("CMD_CascadeCreate_Prompt_Name"), CmdEvalNotEmpty, NULL},
		{"MAXTCP", CmdPrompt, _UU("CMD_CascadeDetailSet_Prompt_MaxTcp"), CmdEvalMinMax, &mm_maxtcp},
		{"INTERVAL", CmdPrompt, _UU("CMD_CascadeDetailSet_Prompt_Interval"), CmdEvalMinMax, &mm_interval},
		{"TTL", CmdPrompt, _UU("CMD_CascadeDetailSet_Prompt_TTL"), NULL, NULL},
		{"HALF", CmdPrompt, _UU("CMD_CascadeDetailSet_Prompt_HALF"), NULL, NULL},
		{"NOQOS", CmdPrompt, _UU("CMD_AccountDetailSet_Prompt_NOQOS"), NULL, NULL},
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
	t.ClientOption = ZeroMalloc(sizeof(CLIENT_OPTION));
	UniStrCpy(t.ClientOption->AccountName, sizeof(t.ClientOption->AccountName), GetParamUniStr(o, "[name]"));

	// RPC call
	ret = ScGetLink(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}
	else
	{
		// Data change
		t.ClientOption->MaxConnection = GetParamInt(o, "MAXTCP");
		t.ClientOption->AdditionalConnectionInterval = GetParamInt(o, "INTERVAL");
		t.ClientOption->ConnectionDisconnectSpan = GetParamInt(o, "TTL");
		t.ClientOption->HalfConnection = GetParamYes(o, "HALF");
		t.ClientOption->DisableQoS = GetParamYes(o, "NOQOS");

		ret = ScSetLink(ps->Rpc, &t);
		if (ret != ERR_NO_ERROR)
		{
			// An error has occured
			CmdPrintError(c, ret);
			FreeParamValueList(o);
			return ret;
		}

		FreeRpcCreateLink(&t);
	}

	FreeParamValueList(o);

	return 0;
}