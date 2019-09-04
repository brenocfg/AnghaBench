#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  z ;
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_14__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/ * member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_13__ {int /*<<< orphan*/  RemoteClient; } ;
struct TYPE_12__ {int /*<<< orphan*/  StartupAccount; int /*<<< orphan*/  ServerCert; TYPE_1__* ClientOption; int /*<<< orphan*/  ClientAuth; int /*<<< orphan*/  RetryOnServerCert; int /*<<< orphan*/  CheckServerCert; int /*<<< orphan*/  AccountName; } ;
struct TYPE_11__ {int /*<<< orphan*/  ProxyPassword; int /*<<< orphan*/  ProxyUsername; scalar_t__ ProxyPort; int /*<<< orphan*/  ProxyName; int /*<<< orphan*/  ProxyType; } ;
typedef  TYPE_2__ RPC_CLIENT_GET_ACCOUNT ;
typedef  TYPE_2__ RPC_CLIENT_CREATE_ACCOUNT ;
typedef  TYPE_4__ PC ;
typedef  TYPE_5__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 scalar_t__ CcGetAccount (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ CcSetAccount (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  CiFreeClientGetAccount (TYPE_2__*) ; 
 int /*<<< orphan*/ * CmdEvalHostAndPort ; 
 int /*<<< orphan*/ * CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 char* GetParamStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetParamUniStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PROXY_SOCKS5 ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,TYPE_5__*,int) ; 
 scalar_t__ ParseHostPort (char*,char**,scalar_t__*,int) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 int /*<<< orphan*/ * _UU (char*) ; 

UINT PcAccountProxySocks5(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PC *pc = (PC *)param;
	UINT ret = ERR_NO_ERROR;
	RPC_CLIENT_GET_ACCOUNT t;
	// Parameter list that can be specified
	PARAM args[] =
	{
		{"[name]", CmdPrompt, _UU("CMD_AccountCreate_Prompt_Name"), CmdEvalNotEmpty, NULL},
		{"SERVER", CmdPrompt, _UU("CMD_AccountProxyHttp_Prompt_Server"), CmdEvalHostAndPort, NULL},
		{"USERNAME", CmdPrompt, NULL, NULL, NULL},
		{"PASSWORD", CmdPrompt, NULL, NULL, NULL},
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
		char *host;
		UINT port;

		// Data change
		if (ParseHostPort(GetParamStr(o, "SERVER"), &host, &port, 1080))
		{
			t.ClientOption->ProxyType = PROXY_SOCKS5;
			StrCpy(t.ClientOption->ProxyName, sizeof(t.ClientOption->ProxyName), host);
			t.ClientOption->ProxyPort = port;
			StrCpy(t.ClientOption->ProxyUsername, sizeof(t.ClientOption->ProxyName), GetParamStr(o, "USERNAME"));
			StrCpy(t.ClientOption->ProxyPassword, sizeof(t.ClientOption->ProxyName), GetParamStr(o, "PASSWORD"));
			Free(host);
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