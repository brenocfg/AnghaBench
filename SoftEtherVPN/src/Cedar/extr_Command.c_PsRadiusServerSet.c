#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_17__ {char* member_0; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* Write ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_15__ {char* member_0; TYPE_5__* member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_14__ {char* HubName; int /*<<< orphan*/  Rpc; } ;
struct TYPE_13__ {int /*<<< orphan*/  RadiusRetryInterval; int /*<<< orphan*/  RadiusSecret; int /*<<< orphan*/  RadiusServerName; scalar_t__ RadiusPort; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_RADIUS ;
typedef  TYPE_2__ PS ;
typedef  TYPE_3__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_4__ CONSOLE ;
typedef  TYPE_5__ CMD_EVAL_MIN_MAX ;

/* Variables and functions */
 int /*<<< orphan*/ * CmdEvalMinMax ; 
 int /*<<< orphan*/ * CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 int /*<<< orphan*/  CmdPromptChoosePassword ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetParamInt (int /*<<< orphan*/ *,char*) ; 
 char* GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_4__*,char*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 scalar_t__ ParseHostPort (char*,char**,scalar_t__*,int) ; 
 int /*<<< orphan*/  RADIUS_RETRY_INTERVAL ; 
 int /*<<< orphan*/  RADIUS_RETRY_TIMEOUT ; 
 scalar_t__ ScSetHubRadius (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 

UINT PsRadiusServerSet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_RADIUS t;
	char *host;
	UINT port;
	// Parameter list that can be specified
	CMD_EVAL_MIN_MAX minmax =
	{
		"CMD_RadiusServerSet_EVAL_NUMINTERVAL", RADIUS_RETRY_INTERVAL, RADIUS_RETRY_TIMEOUT,
	};
	PARAM args[] =
	{
		// "name", prompt_proc, prompt_param, eval_proc, eval_param
		{"[server_name:port]", CmdPrompt, _UU("CMD_RadiusServerSet_Prompt_Host"), CmdEvalNotEmpty, NULL},
		{"SECRET", CmdPromptChoosePassword, _UU("CMD_RadiusServerSet_Prompt_Secret"), NULL, NULL},
		{"RETRY_INTERVAL", CmdPrompt, _UU("CMD_RadiusServerSet_Prompt_RetryInterval"), CmdEvalMinMax, &minmax},
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

	if (ParseHostPort(GetParamStr(o, "[server_name:port]"), &host, &port, 1812))
	{
		Zero(&t, sizeof(t));

		StrCpy(t.HubName, sizeof(t.HubName), ps->HubName);
		t.RadiusPort = port;
		StrCpy(t.RadiusServerName, sizeof(t.RadiusServerName), host);
		StrCpy(t.RadiusSecret, sizeof(t.RadiusSecret), GetParamStr(o, "SECRET"));
		t.RadiusRetryInterval = GetParamInt(o, "RETRY_INTERVAL");

		Free(host);

		// RPC call
		ret = ScSetHubRadius(ps->Rpc, &t);

		if (ret != ERR_NO_ERROR)
		{
			// An error has occured
			CmdPrintError(c, ret);
			FreeParamValueList(o);
			return ret;
		}
	}

	FreeParamValueList(o);

	return 0;
}