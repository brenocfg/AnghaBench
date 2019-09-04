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
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_8__ {int /*<<< orphan*/  Rpc; } ;
struct TYPE_7__ {int /*<<< orphan*/  GatewayAddress; int /*<<< orphan*/  Metric; int /*<<< orphan*/  SubnetMask; int /*<<< orphan*/  NetworkAddress; int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ RPC_L3TABLE ;
typedef  TYPE_2__ PS ;
typedef  TYPE_3__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdEvalInt1 ; 
 int /*<<< orphan*/  CmdEvalIp ; 
 int /*<<< orphan*/  CmdEvalNetworkAndSubnetMask4 ; 
 int /*<<< orphan*/  CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetParamInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  ParseIpAndSubnetMask4 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ScAddL3Table (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrToIP32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 

UINT PsRouterTableAdd(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_L3TABLE t;
	// Parameter list that can be specified
	PARAM args[] =
	{
		// "name", prompt_proc, prompt_param, eval_proc, eval_param
		{"[name]", CmdPrompt, _UU("CMD_RouterTableAdd_PROMPT_NAME"), CmdEvalNotEmpty, NULL},
		{"NETWORK", CmdPrompt, _UU("CMD_RouterTableAdd_PROMPT_NETWORK"), CmdEvalNetworkAndSubnetMask4, NULL},
		{"GATEWAY", CmdPrompt, _UU("CMD_RouterTableAdd_PROMPT_GATEWAY"), CmdEvalIp, NULL},
		{"METRIC", CmdPrompt, _UU("CMD_RouterTableAdd_PROMPT_METRIC"), CmdEvalInt1, NULL},
	};

	o = ParseCommandList(c, cmd_name, str, args, sizeof(args) / sizeof(args[0]));
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));

	StrCpy(t.Name, sizeof(t.Name), GetParamStr(o, "[name]"));
	ParseIpAndSubnetMask4(GetParamStr(o, "NETWORK"), &t.NetworkAddress, &t.SubnetMask);
	t.Metric = GetParamInt(o, "METRIC");
	t.GatewayAddress = StrToIP32(GetParamStr(o, "GATEWAY"));

	// RPC call
	ret = ScAddL3Table(ps->Rpc, &t);

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