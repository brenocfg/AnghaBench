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
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  z ;
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_20__ {int /*<<< orphan*/  (* Write ) (TYPE_6__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_19__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_18__ {int /*<<< orphan*/  RemoteClient; } ;
struct TYPE_17__ {int /*<<< orphan*/  StartupAccount; int /*<<< orphan*/  ServerCert; int /*<<< orphan*/  ClientOption; TYPE_1__* ClientAuth; int /*<<< orphan*/  RetryOnServerCert; int /*<<< orphan*/  CheckServerCert; int /*<<< orphan*/  AccountName; } ;
struct TYPE_16__ {scalar_t__ AuthType; int /*<<< orphan*/  Username; } ;
typedef  TYPE_2__ RPC_CLIENT_GET_ACCOUNT ;
typedef  TYPE_2__ RPC_CLIENT_CREATE_ACCOUNT ;
typedef  TYPE_4__ PC ;
typedef  TYPE_5__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_6__ CONSOLE ;

/* Variables and functions */
 scalar_t__ CLIENT_AUTHTYPE_PASSWORD ; 
 scalar_t__ CcGetAccount (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ CcSetAccount (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  CiFreeClientGetAccount (TYPE_2__*) ; 
 int /*<<< orphan*/  CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_6__*,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetParamUniStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_6__*,char*,int /*<<< orphan*/ *,TYPE_5__*,int) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ) ; 

UINT PcAccountUsernameSet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PC *pc = (PC *)param;
	UINT ret = ERR_NO_ERROR;
	RPC_CLIENT_GET_ACCOUNT t;
	// Parameter list that can be specified
	PARAM args[] =
	{
		{"[name]", CmdPrompt, _UU("CMD_AccountCreate_Prompt_Name"), CmdEvalNotEmpty, NULL},
		{"USERNAME", CmdPrompt, _UU("CMD_AccountCreate_Prompt_Username"), CmdEvalNotEmpty, NULL},
	};

	// Get the parameter list
	o = ParseCommandList(c, cmd_name, str, args, sizeof(args) / sizeof(args[0]));
	if (o == NULL)
	{
		return ERR_INVALID_PARAMETER;
	}

	// RPC call
	Zero(&t, sizeof(t));

	UniStrCpy(t.AccountName, sizeof(t.AccountName), GetParamUniStr(o, "[name]"));

	ret = CcGetAccount(pc->RemoteClient, &t);

	if (ret == ERR_NO_ERROR)
	{
		RPC_CLIENT_CREATE_ACCOUNT z;
		// Change the settings
		StrCpy(t.ClientAuth->Username, sizeof(t.ClientAuth->Username), GetParamStr(o, "USERNAME"));

		if (t.ClientAuth->AuthType == CLIENT_AUTHTYPE_PASSWORD)
		{
			c->Write(c, _UU("CMD_AccountUsername_Notice"));
		}

		Zero(&z, sizeof(z));
		z.CheckServerCert = t.CheckServerCert;
		z.RetryOnServerCert = t.RetryOnServerCert;
		z.ClientAuth = t.ClientAuth;
		z.ClientOption = t.ClientOption;
		z.ServerCert = t.ServerCert;
		z.StartupAccount = t.StartupAccount;

		ret = CcSetAccount(pc->RemoteClient, &z);
	}

	if (ret != ERR_NO_ERROR)
	{
		// Error has occurred
		CmdPrintError(c, ret);
	}

	CiFreeClientGetAccount(&t);

	// Release of the parameter list
	FreeParamValueList(o);

	return ret;
}