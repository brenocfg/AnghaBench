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
struct TYPE_10__ {int KeepConnectProtocol; int /*<<< orphan*/  KeepConnectInterval; scalar_t__ KeepConnectPort; int /*<<< orphan*/  KeepConnectHost; } ;
struct TYPE_9__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_8__ {int /*<<< orphan*/  RemoteClient; } ;
typedef  TYPE_1__ PC ;
typedef  TYPE_2__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CONSOLE ;
typedef  TYPE_3__ CLIENT_CONFIG ;

/* Variables and functions */
 scalar_t__ CcGetClientConfig (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ CcSetClientConfig (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/ * CmdEvalHostAndPort ; 
 int /*<<< orphan*/ * CmdEvalTcpOrUdp ; 
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetParamInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 scalar_t__ ParseHostPort (int /*<<< orphan*/ ,char**,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ StrCmpi (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 

UINT PcKeepSet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PC *pc = (PC *)param;
	UINT ret = ERR_NO_ERROR;
	CLIENT_CONFIG t;
	char *host;
	UINT port;
	// Parameter list that can be specified
	PARAM args[] =
	{
		// "name", prompt_proc, prompt_param, eval_proc, eval_param
		{"HOST", CmdPrompt, _UU("CMD_KeepSet_PROMPT_HOST"), CmdEvalHostAndPort, NULL},
		{"PROTOCOL", CmdPrompt, _UU("CMD_KeepSet_PROMPT_PROTOCOL"), CmdEvalTcpOrUdp, NULL},
		{"INTERVAL", CmdPrompt, _UU("CMD_KeepSet_PROMPT_INTERVAL"), NULL, NULL},
	};

	o = ParseCommandList(c, cmd_name, str, args, sizeof(args) / sizeof(args[0]));
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	// RPC call
	Zero(&t, sizeof(t));

	ret = CcGetClientConfig(pc->RemoteClient, &t);

	if (ret == ERR_NO_ERROR)
	{
		if (ParseHostPort(GetParamStr(o, "HOST"), &host, &port, 0))
		{
			StrCpy(t.KeepConnectHost, sizeof(t.KeepConnectHost), host);
			t.KeepConnectPort = port;
			t.KeepConnectInterval = GetParamInt(o, "INTERVAL");
			t.KeepConnectProtocol = (StrCmpi(GetParamStr(o, "PROTOCOL"), "tcp") == 0) ? 0 : 1;
			Free(host);

			ret = CcSetClientConfig(pc->RemoteClient, &t);
		}
	}

	if (ret != ERR_NO_ERROR)
	{
		// Error has occurred
		CmdPrintError(c, ret);
	}

	// Release of the parameter list
	FreeParamValueList(o);

	return ret;
}