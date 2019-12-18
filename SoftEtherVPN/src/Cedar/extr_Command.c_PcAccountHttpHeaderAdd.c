#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  z ;
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  s ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_18__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_17__ {int /*<<< orphan*/  RemoteClient; } ;
struct TYPE_16__ {int /*<<< orphan*/  StartupAccount; int /*<<< orphan*/  ServerCert; TYPE_1__* ClientOption; int /*<<< orphan*/  ClientAuth; int /*<<< orphan*/  RetryOnServerCert; int /*<<< orphan*/  CheckServerCert; int /*<<< orphan*/  AccountName; } ;
struct TYPE_15__ {scalar_t__ NumTokens; int /*<<< orphan*/ * Token; } ;
struct TYPE_14__ {char* CustomHttpHeader; } ;
typedef  TYPE_2__ TOKEN_LIST ;
typedef  TYPE_3__ RPC_CLIENT_GET_ACCOUNT ;
typedef  TYPE_3__ RPC_CLIENT_CREATE_ACCOUNT ;
typedef  TYPE_5__ PC ;
typedef  TYPE_6__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  HTTP_HEADER ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 int /*<<< orphan*/  AddHttpValueStr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ CcGetAccount (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ CcSetAccount (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  CiFreeClientGetAccount (TYPE_3__*) ; 
 int /*<<< orphan*/ * CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 scalar_t__ ERR_OBJECT_EXISTS ; 
 scalar_t__ ERR_TOO_MANT_ITEMS ; 
 int /*<<< orphan*/  EnSafeHttpHeaderValueStr (char*,char) ; 
 int /*<<< orphan*/  Format (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  FreeHttpHeader (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeToken (TYPE_2__*) ; 
 int /*<<< orphan*/ * GetHttpValue (int /*<<< orphan*/ *,char*) ; 
 char* GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetParamUniStr (int /*<<< orphan*/ *,char*) ; 
 int HTTP_CUSTOM_HEADER_MAX_SIZE ; 
 int /*<<< orphan*/ * NewHttpHeader (char*,char*,char*) ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,TYPE_6__*,int) ; 
 TYPE_2__* ParseToken (char*,char*) ; 
 int /*<<< orphan*/  StrCat (char*,int,char*) ; 
 int StrLen (char*) ; 
 int /*<<< orphan*/  Trim (char*) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 
 int /*<<< orphan*/  _UU (char*) ; 

UINT PcAccountHttpHeaderAdd(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PC *pc = (PC *)param;
	UINT ret = ERR_NO_ERROR;
	RPC_CLIENT_GET_ACCOUNT t;

	// Parameter list that can be specified
	PARAM args[] =
	{
		{"[name]", CmdPrompt, _UU("CMD_AccountCreate_Prompt_Name"), CmdEvalNotEmpty, NULL},
		{"NAME", CmdPrompt, _UU("CMD_AccountHttpHeader_Prompt_Name"), CmdEvalNotEmpty, NULL},
		{"DATA", CmdPrompt, _UU("CMD_AccountHttpHeader_Prompt_Data"), NULL, NULL},
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
		UINT i = 0;
		TOKEN_LIST *tokens = NULL;
		HTTP_HEADER *header = NULL;
		char *name = GetParamStr(o, "NAME");

		Trim(name);

		header = NewHttpHeader("", "", "");

		tokens = ParseToken(t.ClientOption->CustomHttpHeader, "\r\n");
		for (i = 0; i < tokens->NumTokens; i++)
		{
			AddHttpValueStr(header, tokens->Token[i]);
		}
		FreeToken(tokens);

		if (GetHttpValue(header, name) == NULL)
		{
			RPC_CLIENT_CREATE_ACCOUNT z;
			char s[HTTP_CUSTOM_HEADER_MAX_SIZE];

			Format(s, sizeof(s), "%s: %s\r\n", name, GetParamStr(o, "DATA"));
			EnSafeHttpHeaderValueStr(s, ' ');

			if ((StrLen(s) + StrLen(t.ClientOption->CustomHttpHeader)) < sizeof(t.ClientOption->CustomHttpHeader)) {
				StrCat(t.ClientOption->CustomHttpHeader, sizeof(s), s);

				Zero(&z, sizeof(z));
				z.CheckServerCert = t.CheckServerCert;
				z.RetryOnServerCert = t.RetryOnServerCert;
				z.ClientAuth = t.ClientAuth;
				z.ClientOption = t.ClientOption;
				z.ServerCert = t.ServerCert;
				z.StartupAccount = t.StartupAccount;

				ret = CcSetAccount(pc->RemoteClient, &z);
			}
			else
			{
				// Error has occurred
				ret = ERR_TOO_MANT_ITEMS;
			}
		}
		else
		{
			// Error has occurred
			ret = ERR_OBJECT_EXISTS;
		}

		FreeHttpHeader(header);
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