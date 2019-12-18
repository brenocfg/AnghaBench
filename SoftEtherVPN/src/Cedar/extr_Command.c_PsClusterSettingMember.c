#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_10__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/ * member_1; } ;
struct TYPE_9__ {int /*<<< orphan*/  Rpc; } ;
struct TYPE_8__ {int NumPort; scalar_t__ Weight; scalar_t__* Ports; int /*<<< orphan*/  ServerType; int /*<<< orphan*/  PublicIp; int /*<<< orphan*/  MemberPassword; scalar_t__ ControllerPort; int /*<<< orphan*/  ControllerName; } ;
typedef  TYPE_1__ RPC_FARM ;
typedef  TYPE_2__ PS ;
typedef  TYPE_3__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/ * CmdEvalHostAndPort ; 
 int /*<<< orphan*/ * CmdEvalIp ; 
 int /*<<< orphan*/ * CmdEvalPortList ; 
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/ * CmdPrompt ; 
 int /*<<< orphan*/ * CmdPromptChoosePassword ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 scalar_t__ FARM_DEFAULT_WEIGHT ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcFarm (TYPE_1__*) ; 
 scalar_t__ GetParamInt (int /*<<< orphan*/ *,char*) ; 
 char* GetParamStr (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ LIST_DATA (int /*<<< orphan*/ *,scalar_t__) ; 
 int LIST_NUM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 scalar_t__ ParseHostPort (char*,char**,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * PsClusterSettingMemberPromptIp ; 
 int /*<<< orphan*/ * PsClusterSettingMemberPromptPorts ; 
 int /*<<< orphan*/  ReleaseList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SERVER_TYPE_FARM_MEMBER ; 
 scalar_t__ ScSetFarmSetting (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Sha0 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  StrLen (char*) ; 
 int /*<<< orphan*/  StrToIP32 (char*) ; 
 int /*<<< orphan*/ * StrToPortList (char*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 scalar_t__* ZeroMalloc (int) ; 
 int /*<<< orphan*/ * _UU (char*) ; 

UINT PsClusterSettingMember(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_FARM t;
	char *host_and_port;
	char *host;
	UINT port;
	UINT weight;
	// Parameter list that can be specified
	PARAM args[] =
	{
		// "name", prompt_proc, prompt_param, eval_proc, eval_param
		{"[server:port]", CmdPrompt, _UU("CMD_ClusterSettingMember_Prompt_HOST_1"), CmdEvalHostAndPort, NULL},
		{"IP", PsClusterSettingMemberPromptIp, NULL, CmdEvalIp, NULL},
		{"PORTS", PsClusterSettingMemberPromptPorts, NULL, CmdEvalPortList, NULL},
		{"PASSWORD", CmdPromptChoosePassword, NULL, NULL, NULL},
		{"WEIGHT", NULL, NULL, NULL, NULL},
	};

	o = ParseCommandList(c, cmd_name, str, args, sizeof(args) / sizeof(args[0]));
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	weight = GetParamInt(o, "WEIGHT");

	if (weight == 0)
	{
		weight = FARM_DEFAULT_WEIGHT;
	}

	Zero(&t, sizeof(t));
	host_and_port = GetParamStr(o, "[server:port]");
	if (ParseHostPort(host_and_port, &host, &port, 0))
	{
		char *pw;
		char *ports_str;
		LIST *ports;
		UINT i;

		StrCpy(t.ControllerName, sizeof(t.ControllerName), host);
		t.ControllerPort = port;
		Free(host);

		pw = GetParamStr(o, "PASSWORD");

		Sha0(t.MemberPassword, pw, StrLen(pw));
		t.PublicIp = StrToIP32(GetParamStr(o, "IP"));
		t.ServerType = SERVER_TYPE_FARM_MEMBER;

		ports_str = GetParamStr(o, "PORTS");

		ports = StrToPortList(ports_str);

		t.NumPort = LIST_NUM(ports);
		t.Ports = ZeroMalloc(sizeof(UINT) * t.NumPort);

		for (i = 0;i < t.NumPort;i++)
		{
			t.Ports[i] = (UINT)LIST_DATA(ports, i);
		}

		t.Weight = weight;

		ReleaseList(ports);

		// RPC call
		ret = ScSetFarmSetting(ps->Rpc, &t);

		if (ret != ERR_NO_ERROR)
		{
			// An error has occured
			CmdPrintError(c, ret);
			FreeParamValueList(o);
			return ret;
		}

		FreeRpcFarm(&t);
	}

	FreeParamValueList(o);

	return 0;
}