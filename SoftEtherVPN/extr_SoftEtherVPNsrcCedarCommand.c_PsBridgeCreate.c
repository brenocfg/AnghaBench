#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_20__ {int /*<<< orphan*/  (* Write ) (TYPE_4__*,char*) ;} ;
struct TYPE_19__ {char* member_0; char* member_2; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_1; } ;
struct TYPE_18__ {int /*<<< orphan*/  CapsList; int /*<<< orphan*/  Rpc; } ;
struct TYPE_17__ {int Active; int Online; int /*<<< orphan*/  TapMode; int /*<<< orphan*/  HubName; int /*<<< orphan*/  DeviceName; } ;
typedef  TYPE_1__ RPC_LOCALBRIDGE ;
typedef  TYPE_2__ PS ;
typedef  TYPE_3__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_4__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/ * CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/ * CmdPrompt ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 scalar_t__ GetCapsBool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetParamYes (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_4__*,char*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 scalar_t__ ScAddLocalBridge (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 char* _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  stub4 (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  stub5 (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  stub6 (TYPE_4__*,char*) ; 

UINT PsBridgeCreate(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_LOCALBRIDGE t;
	// Parameter list that can be specified
	PARAM args[] =
	{
		// "name", prompt_proc, prompt_param, eval_proc, eval_param
		{"[hubname]", CmdPrompt, _UU("CMD_BridgeCreate_PROMPT_HUBNAME"), CmdEvalNotEmpty, NULL},
		{"DEVICE", CmdPrompt, _UU("CMD_BridgeCreate_PROMPT_DEVICE"), CmdEvalNotEmpty, NULL},
		{"TAP", NULL, NULL, NULL, NULL},
	};

	o = ParseCommandList(c, cmd_name, str, args, sizeof(args) / sizeof(args[0]));
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));

	t.Active = true;
	StrCpy(t.DeviceName, sizeof(t.DeviceName), GetParamStr(o, "DEVICE"));
	StrCpy(t.HubName, sizeof(t.HubName), GetParamStr(o, "[hubname]"));
	t.Online = true;
	t.TapMode = GetParamYes(o, "TAP");

	// RPC call
	ret = ScAddLocalBridge(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}
	else
	{
		c->Write(c, _UU("SM_BRIDGE_INTEL"));
		c->Write(c, L"");

		if (GetCapsBool(ps->CapsList, "b_is_in_vm"))
		{
			// Message in the case of operating in a VM
			c->Write(c, _UU("D_SM_VMBRIDGE@CAPTION"));
			c->Write(c, _UU("D_SM_VMBRIDGE@S_1"));
			c->Write(c, _UU("D_SM_VMBRIDGE@S_2"));
			c->Write(c, L"");
		}
	}

	FreeParamValueList(o);

	return 0;
}