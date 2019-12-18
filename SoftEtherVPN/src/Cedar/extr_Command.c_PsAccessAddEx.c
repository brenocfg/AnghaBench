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
struct TYPE_20__ {int Active; int Discard; int /*<<< orphan*/  RedirectUrl; void* Loss; void* Jitter; void* Delay; int /*<<< orphan*/  Established; int /*<<< orphan*/  CheckTcpState; int /*<<< orphan*/  DestPortEnd; int /*<<< orphan*/  DestPortStart; int /*<<< orphan*/  SrcPortEnd; int /*<<< orphan*/  SrcPortStart; int /*<<< orphan*/  Protocol; int /*<<< orphan*/  DestSubnetMask; int /*<<< orphan*/  DestIpAddress; int /*<<< orphan*/  SrcSubnetMask; int /*<<< orphan*/  SrcIpAddress; int /*<<< orphan*/  DstMacMask; int /*<<< orphan*/  DstMacAddress; int /*<<< orphan*/  CheckDstMac; int /*<<< orphan*/  SrcMacMask; int /*<<< orphan*/  SrcMacAddress; int /*<<< orphan*/  CheckSrcMac; int /*<<< orphan*/  DestUsername; int /*<<< orphan*/  SrcUsername; void* Priority; int /*<<< orphan*/  Note; } ;
struct TYPE_19__ {char* member_0; int member_1; unsigned long member_2; } ;
struct TYPE_18__ {int /*<<< orphan*/  (* Write ) (TYPE_4__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_17__ {char* member_0; TYPE_5__* member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; } ;
struct TYPE_16__ {int /*<<< orphan*/  Rpc; int /*<<< orphan*/ * HubName; int /*<<< orphan*/  CapsList; } ;
struct TYPE_15__ {int /*<<< orphan*/  HubName; TYPE_6__ Access; } ;
typedef  TYPE_1__ RPC_ADD_ACCESS ;
typedef  TYPE_2__ PS ;
typedef  TYPE_3__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_4__ CONSOLE ;
typedef  TYPE_5__ CMD_EVAL_MIN_MAX ;
typedef  TYPE_6__ ACCESS ;

/* Variables and functions */
 int /*<<< orphan*/ * CmdEvalIpAndMask4 ; 
 int /*<<< orphan*/ * CmdEvalMacAddressAndMask ; 
 int /*<<< orphan*/ * CmdEvalMinMax ; 
 int /*<<< orphan*/ * CmdEvalNotEmpty ; 
 int /*<<< orphan*/ * CmdEvalPortRange ; 
 int /*<<< orphan*/ * CmdEvalProtocol ; 
 int /*<<< orphan*/ * CmdEvalTcpState ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/ * CmdPrompt ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NOT_SUPPORTED ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int GetCapsBool (int /*<<< orphan*/ ,char*) ; 
 void* GetParamInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetParamUniStr (int /*<<< orphan*/ *,char*) ; 
 unsigned long HUB_ACCESSLIST_DELAY_MAX ; 
 unsigned long HUB_ACCESSLIST_JITTER_MAX ; 
 unsigned long HUB_ACCESSLIST_LOSS_MAX ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_4__*,char*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  ParseIpAndMask4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ParseMacAddressAndMask (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ParsePortRange (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ParseTcpState (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ScAddAccess (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ StrToPassOrDiscard (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrToProtocol (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/ * _E (scalar_t__) ; 
 int /*<<< orphan*/ * _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ *) ; 

UINT PsAccessAddEx(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_ADD_ACCESS t;
	ACCESS *a;
	// Parameter list that can be specified
	CMD_EVAL_MIN_MAX minmax =
	{
		"CMD_AccessAdd_Eval_PRIORITY", 1, 4294967295UL,
	};
	CMD_EVAL_MIN_MAX minmax_delay =
	{
		"CMD_AccessAddEx_Eval_DELAY", 0, HUB_ACCESSLIST_DELAY_MAX,
	};
	CMD_EVAL_MIN_MAX minmax_jitter =
	{
		"CMD_AccessAddEx_Eval_JITTER", 0, HUB_ACCESSLIST_JITTER_MAX,
	};
	CMD_EVAL_MIN_MAX minmax_loss =
	{
		"CMD_AccessAddEx_Eval_LOSS", 0, HUB_ACCESSLIST_LOSS_MAX,
	};
	PARAM args[] =
	{
		// "name", prompt_proc, prompt_param, eval_proc, eval_param
		{"[pass|discard]", CmdPrompt, _UU("CMD_AccessAdd_Prompt_TYPE"), CmdEvalNotEmpty, NULL},
		{"MEMO", CmdPrompt, _UU("CMD_AccessAdd_Prompt_MEMO"), NULL, NULL},
		{"PRIORITY", CmdPrompt, _UU("CMD_AccessAdd_Prompt_PRIORITY"), CmdEvalMinMax, &minmax},
		{"SRCUSERNAME", CmdPrompt, _UU("CMD_AccessAdd_Prompt_SRCUSERNAME"), NULL, NULL},
		{"DESTUSERNAME", CmdPrompt, _UU("CMD_AccessAdd_Prompt_DESTUSERNAME"), NULL, NULL},
		{"SRCMAC", CmdPrompt, _UU("CMD_AccessAdd_Prompt_SRCMAC"), CmdEvalMacAddressAndMask, NULL},
		{"DESTMAC", CmdPrompt, _UU("CMD_AccessAdd_Prompt_DESTMAC"), CmdEvalMacAddressAndMask, NULL},
		{"SRCIP", CmdPrompt, _UU("CMD_AccessAdd_Prompt_SRCIP"), CmdEvalIpAndMask4, NULL},
		{"DESTIP", CmdPrompt, _UU("CMD_AccessAdd_Prompt_DESTIP"), CmdEvalIpAndMask4, NULL},
		{"PROTOCOL", CmdPrompt, _UU("CMD_AccessAdd_Prompt_PROTOCOL"), CmdEvalProtocol, NULL},
		{"SRCPORT", CmdPrompt, _UU("CMD_AccessAdd_Prompt_SRCPORT"), CmdEvalPortRange, NULL},
		{"DESTPORT", CmdPrompt, _UU("CMD_AccessAdd_Prompt_DESTPORT"), CmdEvalPortRange, NULL},
		{"TCPSTATE", CmdPrompt, _UU("CMD_AccessAdd_Prompt_TCPSTATE"), CmdEvalTcpState, NULL},
		{"DELAY", CmdPrompt, _UU("CMD_AccessAddEx_Prompt_DELAY"), CmdEvalMinMax, &minmax_delay},
		{"JITTER", CmdPrompt, _UU("CMD_AccessAddEx_Prompt_JITTER"), CmdEvalMinMax, &minmax_jitter},
		{"LOSS", CmdPrompt, _UU("CMD_AccessAddEx_Prompt_LOSS"), CmdEvalMinMax, &minmax_loss},
		{"REDIRECTURL", NULL, NULL, NULL, NULL},
	};

	// If virtual HUB is not selected, it's an error
	if (ps->HubName == NULL)
	{
		c->Write(c, _UU("CMD_Hub_Not_Selected"));
		return ERR_INVALID_PARAMETER;
	}

	// Check whether it is supported
	if (GetCapsBool(ps->CapsList, "b_support_ex_acl") == false)
	{
		c->Write(c, _E(ERR_NOT_SUPPORTED));
		return ERR_NOT_SUPPORTED;
	}

	o = ParseCommandList(c, cmd_name, str, args, sizeof(args) / sizeof(args[0]));
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));
	a = &t.Access;

	StrCpy(t.HubName, sizeof(t.HubName), ps->HubName);
	UniStrCpy(a->Note, sizeof(a->Note), GetParamUniStr(o, "MEMO"));
	a->Active = true;
	a->Priority = GetParamInt(o, "PRIORITY");
	a->Discard = StrToPassOrDiscard(GetParamStr(o, "[pass|discard]")) ? false : true;
	StrCpy(a->SrcUsername, sizeof(a->SrcUsername), GetParamStr(o, "SRCUSERNAME"));
	StrCpy(a->DestUsername, sizeof(a->DestUsername), GetParamStr(o, "DESTUSERNAME"));
	ParseMacAddressAndMask(GetParamStr(o, "SRCMAC"), &a->CheckSrcMac, a->SrcMacAddress, a->SrcMacMask);
	ParseMacAddressAndMask(GetParamStr(o, "DESTMAC"), &a->CheckDstMac, a->DstMacAddress, a->DstMacMask);
	ParseIpAndMask4(GetParamStr(o, "SRCIP"), &a->SrcIpAddress, &a->SrcSubnetMask);
	ParseIpAndMask4(GetParamStr(o, "DESTIP"), &a->DestIpAddress, &a->DestSubnetMask);
	a->Protocol = StrToProtocol(GetParamStr(o, "PROTOCOL"));
	ParsePortRange(GetParamStr(o, "SRCPORT"), &a->SrcPortStart, &a->SrcPortEnd);
	ParsePortRange(GetParamStr(o, "DESTPORT"), &a->DestPortStart, &a->DestPortEnd);
	ParseTcpState(GetParamStr(o, "TCPSTATE"), &a->CheckTcpState, &a->Established);
	a->Delay = GetParamInt(o, "DELAY");
	a->Jitter = GetParamInt(o, "JITTER");
	a->Loss = GetParamInt(o, "LOSS");
	StrCpy(a->RedirectUrl, sizeof(a->RedirectUrl), GetParamStr(o, "REDIRECTURL"));

	// RPC call
	ret = ScAddAccess(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}

	FreeParamValueList(o);

	return 0;
}