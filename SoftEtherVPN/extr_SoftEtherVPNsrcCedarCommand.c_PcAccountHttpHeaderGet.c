#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  unistr ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_15__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_14__ {int /*<<< orphan*/  RemoteClient; } ;
struct TYPE_13__ {TYPE_1__* ClientOption; int /*<<< orphan*/  AccountName; } ;
struct TYPE_12__ {scalar_t__ NumTokens; int /*<<< orphan*/ * Token; } ;
struct TYPE_11__ {int /*<<< orphan*/  CustomHttpHeader; } ;
typedef  TYPE_2__ TOKEN_LIST ;
typedef  TYPE_3__ RPC_CLIENT_GET_ACCOUNT ;
typedef  TYPE_4__ PC ;
typedef  TYPE_5__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 scalar_t__ CcGetAccount (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  CiFreeClientGetAccount (TYPE_3__*) ; 
 int /*<<< orphan*/  CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 int /*<<< orphan*/  CtFreeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsertColumn (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * CtNew () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetParamUniStr (int /*<<< orphan*/ *,char*) ; 
 int HTTP_CUSTOM_HEADER_MAX_SIZE ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,TYPE_5__*,int) ; 
 TYPE_2__* ParseToken (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 

UINT PcAccountHttpHeaderGet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	PC *pc = (PC *)param;
	UINT ret = ERR_NO_ERROR;
	RPC_CLIENT_GET_ACCOUNT t;

	// Parameter list that can be specified
	PARAM args[] =
	{
		{"[name]", CmdPrompt, _UU("CMD_AccountCreate_Prompt_Name"), CmdEvalNotEmpty, NULL},
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

	// Release of the parameter list
	FreeParamValueList(o);

	if (ret == ERR_NO_ERROR)
	{
		wchar_t unistr[HTTP_CUSTOM_HEADER_MAX_SIZE];
		TOKEN_LIST *tokens = NULL;
		UINT i = 0;
		CT *ct = CtNew();
		CtInsertColumn(ct, _UU("CMD_CT_STD_COLUMN_1"), false);

		tokens = ParseToken(t.ClientOption->CustomHttpHeader, "\r\n");

		for (i = 0; i < tokens->NumTokens; i++)
		{
			StrToUni(unistr, sizeof(unistr), tokens->Token[i]);
			CtInsert(ct, unistr);
		}

		CtFreeEx(ct, c, false);
	}
	else
	{
		// Error has occurred
		CmdPrintError(c, ret);
	}

	CiFreeClientGetAccount(&t);

	return ret;
}