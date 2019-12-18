#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  z ;
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_19__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_18__ {int /*<<< orphan*/  RemoteClient; } ;
struct TYPE_17__ {TYPE_1__* ClientOption; int /*<<< orphan*/  StartupAccount; int /*<<< orphan*/  ServerCert; int /*<<< orphan*/  ClientAuth; int /*<<< orphan*/  RetryOnServerCert; int /*<<< orphan*/  CheckServerCert; int /*<<< orphan*/  AccountName; } ;
struct TYPE_16__ {scalar_t__ NumTokens; char** Token; } ;
struct TYPE_15__ {TYPE_3__* CustomHttpHeader; } ;
typedef  TYPE_2__ TOKEN_LIST ;
typedef  TYPE_3__ RPC_CLIENT_GET_ACCOUNT ;
typedef  TYPE_3__ RPC_CLIENT_CREATE_ACCOUNT ;
typedef  TYPE_5__ PC ;
typedef  TYPE_6__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 scalar_t__ CcGetAccount (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ CcSetAccount (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  CiFreeClientGetAccount (TYPE_3__*) ; 
 int /*<<< orphan*/  CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 char* GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetParamUniStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,TYPE_6__*,int) ; 
 TYPE_2__* ParseToken (TYPE_3__*,char*) ; 
 int StartWith (char*,char*) ; 
 int /*<<< orphan*/  StrCat (TYPE_3__*,int,char*) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 

UINT PcAccountHttpHeaderDelete(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	PC *pc = (PC *)param;
	UINT ret = ERR_NO_ERROR;
	RPC_CLIENT_GET_ACCOUNT t;

	// Parameter list that can be specified
	PARAM args[] =
	{
		{"[name]", CmdPrompt, _UU("CMD_AccountCreate_Prompt_Name"), CmdEvalNotEmpty, NULL},
		{"NAME", CmdPrompt, _UU("CMD_AccountHttpHeader_Prompt_Name"), CmdEvalNotEmpty, NULL},
	};

	// Get the parameter list
	LIST *o = ParseCommandList(c, cmd_name, str, args, sizeof(args) / sizeof(args[0]));
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
		UINT i = 0;
		TOKEN_LIST *tokens = NULL;
		RPC_CLIENT_CREATE_ACCOUNT z;
		char *value = GetParamStr(o, "NAME");

		Zero(&z, sizeof(z));
		z.CheckServerCert = t.CheckServerCert;
		z.RetryOnServerCert = t.RetryOnServerCert;
		z.ClientAuth = t.ClientAuth;
		z.ClientOption = t.ClientOption;
		z.ServerCert = t.ServerCert;
		z.StartupAccount = t.StartupAccount;

		Zero(z.ClientOption->CustomHttpHeader, sizeof(z.ClientOption->CustomHttpHeader));

		tokens = ParseToken(t.ClientOption->CustomHttpHeader, "\r\n");

		for (i = 0; i < tokens->NumTokens; i++)
		{
			if (StartWith(tokens->Token[i], value) == false)
			{
				StrCat(z.ClientOption->CustomHttpHeader, sizeof(z.ClientOption->CustomHttpHeader), tokens->Token[i]);
				StrCat(z.ClientOption->CustomHttpHeader, 1, "\r\n");
			}
		}

		ret = CcSetAccount(pc->RemoteClient, &z);
	}
	else
	{
		// Error has occurred
		CmdPrintError(c, ret);
	}

	CiFreeClientGetAccount(&t);

	// Release of the parameter list
	FreeParamValueList(o);

	return ret;
}