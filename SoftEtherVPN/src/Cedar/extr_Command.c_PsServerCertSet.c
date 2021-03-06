#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_19__ {int /*<<< orphan*/  (* Write ) (TYPE_4__*,char*) ;} ;
struct TYPE_18__ {char* member_0; char* member_2; int /*<<< orphan*/ * member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_1; } ;
struct TYPE_17__ {int /*<<< orphan*/  Rpc; } ;
struct TYPE_16__ {scalar_t__ Flag1; int /*<<< orphan*/  Key; int /*<<< orphan*/  Cert; } ;
typedef  TYPE_1__ RPC_KEY_PAIR ;
typedef  TYPE_2__ PS ;
typedef  TYPE_3__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_4__ CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  CmdEvalIsFile ; 
 scalar_t__ CmdLoadCertAndKey (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 scalar_t__ ERR_INTERNAL_ERROR ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcKeyPair (TYPE_1__*) ; 
 int /*<<< orphan*/  GetParamUniStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_4__*,char*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 scalar_t__ ScSetServerCert (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 
 char* _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*,char*) ; 

UINT PsServerCertSet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_KEY_PAIR t;
	// Parameter list that can be specified
	PARAM args[] =
	{
		// "name", prompt_proc, prompt_param, eval_proc, eval_param
		{"LOADCERT", CmdPrompt, _UU("CMD_LOADCERTPATH"), CmdEvalIsFile, NULL},
		{"LOADKEY", CmdPrompt, _UU("CMD_LOADKEYPATH"), CmdEvalIsFile, NULL},
	};

	o = ParseCommandList(c, cmd_name, str, args, sizeof(args) / sizeof(args[0]));
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	Zero(&t, sizeof(t));

	if (CmdLoadCertAndKey(c, &t.Cert, &t.Key,
		GetParamUniStr(o, "LOADCERT"),
		GetParamUniStr(o, "LOADKEY")))
	{
		// RPC call
		ret = ScSetServerCert(ps->Rpc, &t);

		if (ret != ERR_NO_ERROR)
		{
			// An error has occured
			CmdPrintError(c, ret);
			FreeParamValueList(o);
			return ret;
		}

		if (t.Flag1 == 0)
		{
			// Show the warning message
			c->Write(c, L"");
			c->Write(c, _UU("SM_CERT_NEED_ROOT"));
			c->Write(c, L"");
		}

		FreeRpcKeyPair(&t);
	}
	else
	{
		ret = ERR_INTERNAL_ERROR;
	}

	FreeParamValueList(o);

	return ret;
}