#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_23__ {int Deny; int Masked; int /*<<< orphan*/  Priority; int /*<<< orphan*/  SubnetMask; int /*<<< orphan*/  IpAddress; } ;
struct TYPE_22__ {char* member_0; int member_1; unsigned long member_2; } ;
struct TYPE_21__ {int /*<<< orphan*/  (* Write ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_20__ {char* member_0; TYPE_5__* member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_19__ {int /*<<< orphan*/  Rpc; int /*<<< orphan*/ * HubName; } ;
struct TYPE_18__ {int /*<<< orphan*/  o; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_AC_LIST ;
typedef  TYPE_2__ PS ;
typedef  TYPE_3__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_4__ CONSOLE ;
typedef  TYPE_5__ CMD_EVAL_MIN_MAX ;
typedef  TYPE_6__ AC ;

/* Variables and functions */
 int /*<<< orphan*/  CmdEvalIpAndMask4 ; 
 int /*<<< orphan*/  CmdEvalMinMax ; 
 int /*<<< orphan*/  CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcAcList (TYPE_1__*) ; 
 int /*<<< orphan*/  GetParamInt (int /*<<< orphan*/ *,char*) ; 
 char* GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_4__*,char*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 int /*<<< orphan*/  ParseIpAndMask4 (char*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ ScGetAcList (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ ScSetAcList (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ StartWith (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UINTToIP (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 TYPE_6__* ZeroMalloc (int) ; 
 int /*<<< orphan*/  _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 

UINT PsAcAdd(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_AC_LIST t;
	// Parameter list that can be specified
	CMD_EVAL_MIN_MAX mm =
	{
		"CMD_AcAdd_Eval_PRIORITY", 1, 4294967295UL,
	};
	PARAM args[] =
	{
		// "name", prompt_proc, prompt_param, eval_proc, eval_param
		{"[allow|deny]", CmdPrompt, _UU("CMD_AcAdd_Prompt_AD"), CmdEvalNotEmpty, NULL},
		{"PRIORITY", CmdPrompt, _UU("CMD_AcAdd_Prompt_PRIORITY"), CmdEvalMinMax, &mm},
		{"IP", CmdPrompt, _UU("CMD_AcAdd_Prompt_IP"), CmdEvalIpAndMask4, NULL},
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
	ret = ScGetAcList(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}
	else
	{
		// Add a new item to the list
		AC *ac = ZeroMalloc(sizeof(AC));
		char *test = GetParamStr(o, "[allow|deny]");
		UINT u_ip, u_mask;

		if (StartWith("deny", test))
		{
			ac->Deny = true;
		}

		ParseIpAndMask4(GetParamStr(o, "IP"), &u_ip, &u_mask);
		UINTToIP(&ac->IpAddress, u_ip);

		if (u_mask == 0xffffffff)
		{
			ac->Masked = false;
		}
		else
		{
			ac->Masked = true;
			UINTToIP(&ac->SubnetMask, u_mask);
		}

		ac->Priority = GetParamInt(o, "PRIORITY");

		Insert(t.o, ac);

		ret = ScSetAcList(ps->Rpc, &t);
		if (ret != ERR_NO_ERROR)
		{
			// An error has occured
			CmdPrintError(c, ret);
			FreeParamValueList(o);
			return ret;
		}
	}

	FreeRpcAcList(&t);

	FreeParamValueList(o);

	return 0;
}