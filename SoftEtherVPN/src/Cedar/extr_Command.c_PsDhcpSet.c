#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_14__ {int ApplyDhcpPushRoutes; int /*<<< orphan*/  HubName; int /*<<< orphan*/  DhcpPushRoutes; int /*<<< orphan*/  SaveLog; int /*<<< orphan*/  DhcpDomainName; int /*<<< orphan*/  DhcpDnsServerAddress2; int /*<<< orphan*/  DhcpDnsServerAddress; int /*<<< orphan*/  DhcpGatewayAddress; int /*<<< orphan*/  DhcpExpireTimeSpan; int /*<<< orphan*/  DhcpSubnetMask; int /*<<< orphan*/  DhcpLeaseIPEnd; int /*<<< orphan*/  DhcpLeaseIPStart; } ;
typedef  TYPE_1__ VH_OPTION ;
typedef  scalar_t__ UINT ;
struct TYPE_18__ {char* member_0; int member_1; int member_2; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* Write ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_16__ {char* member_0; TYPE_5__* member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; } ;
struct TYPE_15__ {int /*<<< orphan*/  CapsList; int /*<<< orphan*/  Rpc; int /*<<< orphan*/ * HubName; } ;
typedef  TYPE_2__ PS ;
typedef  TYPE_3__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_4__ CONSOLE ;
typedef  TYPE_5__ CMD_EVAL_MIN_MAX ;

/* Variables and functions */
 int /*<<< orphan*/ * CmdEvalIp ; 
 int /*<<< orphan*/ * CmdEvalMinMax ; 
 int /*<<< orphan*/ * CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/ * CmdPrompt ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NOT_SUPPORTED_FUNCTION_ON_OPENSOURCE ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int GetCapsBool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GetParamInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetParamYes (int /*<<< orphan*/ *,char*) ; 
 int IsEmptyStr (int /*<<< orphan*/ *) ; 
 int NAT_UDP_MAX_TIMEOUT ; 
 int NAT_UDP_MIN_TIMEOUT ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_4__*,char*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 scalar_t__ ScGetSecureNATOption (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ ScSetSecureNATOption (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrToIP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 

UINT PsDhcpSet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	VH_OPTION t;
	// Parameter list that can be specified
	CMD_EVAL_MIN_MAX mm =
	{
		"CMD_NatSet_Eval_UDP", NAT_UDP_MIN_TIMEOUT / 1000, NAT_UDP_MAX_TIMEOUT / 1000,
	};
	PARAM args[] =
	{
		// "name", prompt_proc, prompt_param, eval_proc, eval_param
		{"START", CmdPrompt, _UU("CMD_DhcpSet_Prompt_START"), CmdEvalIp, NULL},
		{"END", CmdPrompt, _UU("CMD_DhcpSet_Prompt_END"), CmdEvalIp, NULL},
		{"MASK", CmdPrompt, _UU("CMD_DhcpSet_Prompt_MASK"), CmdEvalIp, NULL},
		{"EXPIRE", CmdPrompt, _UU("CMD_DhcpSet_Prompt_EXPIRE"), CmdEvalMinMax, &mm},
		{"GW", CmdPrompt, _UU("CMD_DhcpSet_Prompt_GW"), CmdEvalIp, NULL},
		{"DNS", CmdPrompt, _UU("CMD_DhcpSet_Prompt_DNS"), CmdEvalIp, NULL},
		{"DNS2", CmdPrompt, _UU("CMD_DhcpSet_Prompt_DNS2"), CmdEvalIp, NULL},
		{"DOMAIN", CmdPrompt, _UU("CMD_DhcpSet_Prompt_DOMAIN"), NULL, NULL},
		{"LOG", CmdPrompt, _UU("CMD_NatSet_Prompt_LOG"), CmdEvalNotEmpty, NULL},
		{"PUSHROUTE", NULL, _UU("CMD_DhcpSet_PUSHROUTE"), NULL, NULL},
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

	// RPC call
	ret = ScGetSecureNATOption(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}
	else
	{

		StrToIP(&t.DhcpLeaseIPStart, GetParamStr(o, "START"));
		StrToIP(&t.DhcpLeaseIPEnd, GetParamStr(o, "END"));
		StrToIP(&t.DhcpSubnetMask, GetParamStr(o, "MASK"));
		t.DhcpExpireTimeSpan = GetParamInt(o, "EXPIRE");
		StrToIP(&t.DhcpGatewayAddress, GetParamStr(o, "GW"));
		StrToIP(&t.DhcpDnsServerAddress, GetParamStr(o, "DNS"));
		StrToIP(&t.DhcpDnsServerAddress2, GetParamStr(o, "DNS2"));
		StrCpy(t.DhcpDomainName, sizeof(t.DhcpDomainName), GetParamStr(o, "DOMAIN"));
		t.SaveLog = GetParamYes(o, "LOG");

		StrCpy(t.DhcpPushRoutes, sizeof(t.DhcpPushRoutes), GetParamStr(o, "PUSHROUTE"));
		t.ApplyDhcpPushRoutes = true;

		StrCpy(t.HubName, sizeof(t.HubName), ps->HubName);
		ret = ScSetSecureNATOption(ps->Rpc, &t);

		if (ret != ERR_NO_ERROR)
		{
			// An error has occured
			CmdPrintError(c, ret);
			FreeParamValueList(o);
			return ret;
		}

		if (IsEmptyStr(GetParamStr(o, "PUSHROUTE")) == false)
		{
			if (GetCapsBool(ps->CapsList, "b_suppport_push_route") == false &&
				GetCapsBool(ps->CapsList, "b_suppport_push_route_config"))
			{
				CmdPrintError(c, ERR_NOT_SUPPORTED_FUNCTION_ON_OPENSOURCE);
			}
		}
	}

	FreeParamValueList(o);

	return 0;
}