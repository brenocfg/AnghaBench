#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_9__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_24__ {char* AccountName; scalar_t__ ProxyType; scalar_t__ DisableQoS; scalar_t__ NoRoutingTracking; scalar_t__ RequireMonitorMode; scalar_t__ RequireBridgeRoutingMode; scalar_t__ UseCompress; scalar_t__ UseEncrypt; scalar_t__ HalfConnection; int /*<<< orphan*/  ConnectionDisconnectSpan; int /*<<< orphan*/  AdditionalConnectionInterval; int /*<<< orphan*/  MaxConnection; int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  ProxyUsername; int /*<<< orphan*/  ProxyPort; int /*<<< orphan*/  ProxyName; int /*<<< orphan*/  HubName; int /*<<< orphan*/  Port; int /*<<< orphan*/  Hostname; } ;
struct TYPE_23__ {int /*<<< orphan*/  (* Write ) (TYPE_5__*,char*) ;} ;
struct TYPE_22__ {char* member_0; char* member_2; int /*<<< orphan*/ * member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_1; } ;
struct TYPE_21__ {int /*<<< orphan*/  Rpc; int /*<<< orphan*/ * HubName; } ;
struct TYPE_20__ {int /*<<< orphan*/  Policy; TYPE_9__* ClientOption; TYPE_1__* ClientAuth; int /*<<< orphan*/ * ServerCert; scalar_t__ CheckServerCert; int /*<<< orphan*/  HubName; } ;
struct TYPE_19__ {scalar_t__ AuthType; int /*<<< orphan*/ * ClientX; int /*<<< orphan*/  Username; } ;
typedef  TYPE_2__ RPC_CREATE_LINK ;
typedef  TYPE_3__ PS ;
typedef  TYPE_4__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  TYPE_5__ CONSOLE ;
typedef  int /*<<< orphan*/  CLIENT_OPTION ;

/* Variables and functions */
 scalar_t__ CLIENT_AUTHTYPE_CERT ; 
 int /*<<< orphan*/  CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdPrintError (TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * CtNewStandard () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeRpcCreateLink (TYPE_2__*) ; 
 int /*<<< orphan*/  GetAllNameFromX (char*,int,int /*<<< orphan*/ *) ; 
 char* GetClientAuthTypeStr (scalar_t__) ; 
 char* GetParamUniStr (int /*<<< orphan*/ *,char*) ; 
 char* GetProxyTypeStr (scalar_t__) ; 
 int MAX_SIZE ; 
 scalar_t__ PROXY_DIRECT ; 
 int /*<<< orphan*/ * ParseCommandList (TYPE_5__*,char*,char*,TYPE_4__*,int) ; 
 int /*<<< orphan*/  PrintPolicy (TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ScGetLink (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StrToUni (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniStrCpy (char*,int,char*) ; 
 int /*<<< orphan*/  UniToStru (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 
 TYPE_9__* ZeroMalloc (int) ; 
 char* _UU (char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  stub2 (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  stub3 (TYPE_5__*,char*) ; 

UINT PsCascadeGet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PS *ps = (PS *)param;
	UINT ret = 0;
	RPC_CREATE_LINK t;
	// Parameter list that can be specified
	PARAM args[] =
	{
		// "name", prompt_proc, prompt_param, eval_proc, eval_param
		{"[name]", CmdPrompt, _UU("CMD_CascadeCreate_Prompt_Name"), CmdEvalNotEmpty, NULL},
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
	t.ClientOption = ZeroMalloc(sizeof(CLIENT_OPTION));
	UniStrCpy(t.ClientOption->AccountName, sizeof(t.ClientOption->AccountName),
		GetParamUniStr(o, "[name]"));

	// RPC call
	ret = ScGetLink(ps->Rpc, &t);

	if (ret != ERR_NO_ERROR)
	{
		// An error has occured
		CmdPrintError(c, ret);
		FreeParamValueList(o);
		return ret;
	}
	else
	{
		// Show the contents of the connection settings
		wchar_t tmp[MAX_SIZE];

		CT *ct = CtNewStandard();

		// Connection settings name
		CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_NAME"), t.ClientOption->AccountName);

		// Host name of the destination VPN Server
		StrToUni(tmp, sizeof(tmp), t.ClientOption->Hostname);
		CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_HOSTNAME"), tmp);

		// The port number to connect to VPN Server
		UniToStru(tmp, t.ClientOption->Port);
		CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_PORT"), tmp);

		// Virtual HUB name of the destination VPN Server
		StrToUni(tmp, sizeof(tmp), t.ClientOption->HubName);
		CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_HUBNAME"), tmp);

		// Type of proxy server to go through
		CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_PROXY_TYPE"), GetProxyTypeStr(t.ClientOption->ProxyType));

		if (t.ClientOption->ProxyType != PROXY_DIRECT)
		{
			// Host name of the proxy server
			StrToUni(tmp, sizeof(tmp), t.ClientOption->ProxyName);
			CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_PROXY_HOSTNAME"), tmp);

			// Port number of the proxy server
			UniToStru(tmp, t.ClientOption->ProxyPort);
			CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_PROXY_PORT"), tmp);

			// User name of the proxy server
			StrToUni(tmp, sizeof(tmp), t.ClientOption->ProxyUsername);
			CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_PROXY_USERNAME"), tmp);
		}

		// To verify the server certificate
		CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_SERVER_CERT_USE"),
			t.CheckServerCert ? _UU("CMD_MSG_ENABLE") : _UU("CMD_MSG_DISABLE"));

		// Registered specific certificate
		if (t.ServerCert != NULL)
		{
			GetAllNameFromX(tmp, sizeof(tmp), t.ServerCert);
			CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_SERVER_CERT_NAME"), tmp);
		}

		// Device name to be used for the connection
		StrToUni(tmp, sizeof(tmp), t.ClientOption->DeviceName);
		CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_DEVICE_NAME"), tmp);

		// Authentication type
		CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_AUTH_TYPE"), GetClientAuthTypeStr(t.ClientAuth->AuthType));

		// User name
		StrToUni(tmp, sizeof(tmp), t.ClientAuth->Username);
		CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_AUTH_USERNAME"), tmp);

		if (t.ClientAuth->AuthType == CLIENT_AUTHTYPE_CERT)
		{
			if (t.ClientAuth->ClientX != NULL)
			{
				// Client certificate name
				GetAllNameFromX(tmp, sizeof(tmp), t.ClientAuth->ClientX);
				CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_AUTH_CERT_NAME"), tmp);
			}
		}

		// Number of TCP connections to be used for VPN communication
		UniToStru(tmp, t.ClientOption->MaxConnection);
		CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_NUMTCP"), tmp);

		// Establishment interval of each TCP connection
		UniToStru(tmp, t.ClientOption->AdditionalConnectionInterval);
		CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_TCP_INTERVAL"), tmp);

		// Life span of each TCP connection
		if (t.ClientOption->ConnectionDisconnectSpan != 0)
		{
			UniToStru(tmp, t.ClientOption->ConnectionDisconnectSpan);
		}
		else
		{
			UniStrCpy(tmp, sizeof(tmp), _UU("CMD_MSG_INFINITE"));
		}
		CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_TCP_TTL"), tmp);

		// Use of half-duplex mode
		CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_TCP_HALF"),
			t.ClientOption->HalfConnection ? _UU("CMD_MSG_ENABLE") : _UU("CMD_MSG_DISABLE"));

		// Encryption by SSL
		CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_ENCRYPT"),
			t.ClientOption->UseEncrypt ? _UU("CMD_MSG_ENABLE") : _UU("CMD_MSG_DISABLE"));

		// Data compression
		CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_COMPRESS"),
			t.ClientOption->UseCompress ? _UU("CMD_MSG_ENABLE") : _UU("CMD_MSG_DISABLE"));

		// Connect in bridge / router mode
		CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_BRIDGE_ROUTER"),
			t.ClientOption->RequireBridgeRoutingMode ? _UU("CMD_MSG_ENABLE") : _UU("CMD_MSG_DISABLE"));

		// Connect in monitoring mode
		CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_MONITOR"),
			t.ClientOption->RequireMonitorMode ? _UU("CMD_MSG_ENABLE") : _UU("CMD_MSG_DISABLE"));

		// Not to rewrite the routing table
		CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_NO_TRACKING"),
			t.ClientOption->NoRoutingTracking ? _UU("CMD_MSG_ENABLE") : _UU("CMD_MSG_DISABLE"));

		// Disable the QoS control
		CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_QOS_DISABLE"),
			t.ClientOption->DisableQoS ? _UU("CMD_MSG_ENABLE") : _UU("CMD_MSG_DISABLE"));

		CtFree(ct, c);

		// Security policy
		c->Write(c, L"");
		c->Write(c, _UU("CMD_CascadeGet_Policy"));
		PrintPolicy(c, &t.Policy, true);
	}

	FreeRpcCreateLink(&t);

	FreeParamValueList(o);

	return 0;
}