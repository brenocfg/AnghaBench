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
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  args ;
typedef  scalar_t__ UINT ;
struct TYPE_14__ {char* member_0; int /*<<< orphan*/ * member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; } ;
struct TYPE_13__ {int /*<<< orphan*/  RemoteClient; } ;
struct TYPE_12__ {TYPE_2__* ClientOption; TYPE_1__* ClientAuth; scalar_t__ RetryOnServerCert; scalar_t__ CheckServerCert; int /*<<< orphan*/ * ServerCert; int /*<<< orphan*/ * AccountName; } ;
struct TYPE_11__ {scalar_t__ ProxyType; scalar_t__ NoUdpAcceleration; scalar_t__ DisableQoS; scalar_t__ NoRoutingTracking; scalar_t__ RequireMonitorMode; scalar_t__ RequireBridgeRoutingMode; scalar_t__ UseCompress; scalar_t__ UseEncrypt; scalar_t__ HalfConnection; int /*<<< orphan*/  ConnectionDisconnectSpan; int /*<<< orphan*/  AdditionalConnectionInterval; int /*<<< orphan*/  MaxConnection; int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  ProxyUsername; int /*<<< orphan*/  ProxyPort; int /*<<< orphan*/  ProxyName; int /*<<< orphan*/  HubName; int /*<<< orphan*/  Port; int /*<<< orphan*/  Hostname; int /*<<< orphan*/ * AccountName; } ;
struct TYPE_10__ {scalar_t__ AuthType; int /*<<< orphan*/ * ClientX; int /*<<< orphan*/  Username; } ;
typedef  TYPE_3__ RPC_CLIENT_GET_ACCOUNT ;
typedef  TYPE_4__ PC ;
typedef  TYPE_5__ PARAM ;
typedef  int /*<<< orphan*/  LIST ;
typedef  int /*<<< orphan*/  CT ;
typedef  int /*<<< orphan*/  CONSOLE ;

/* Variables and functions */
 scalar_t__ CLIENT_AUTHTYPE_CERT ; 
 scalar_t__ CcGetAccount (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  CiFreeClientGetAccount (TYPE_3__*) ; 
 int /*<<< orphan*/  CmdEvalNotEmpty ; 
 int /*<<< orphan*/  CmdPrintError (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  CmdPrompt ; 
 int /*<<< orphan*/  CtFree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtInsert (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CtNewStandard () ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_NO_ERROR ; 
 int /*<<< orphan*/  FreeParamValueList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetAllNameFromX (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetClientAuthTypeStr (scalar_t__) ; 
 int /*<<< orphan*/ * GetParamUniStr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * GetProxyTypeStr (scalar_t__) ; 
 int MAX_SIZE ; 
 scalar_t__ PROXY_DIRECT ; 
 int /*<<< orphan*/ * ParseCommandList (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,TYPE_5__*,int) ; 
 int /*<<< orphan*/  StrToUni (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UniStrCpy (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UniToStru (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 
 int /*<<< orphan*/ * _UU (char*) ; 

UINT PcAccountGet(CONSOLE *c, char *cmd_name, wchar_t *str, void *param)
{
	LIST *o;
	PC *pc = (PC *)param;
	UINT ret = ERR_NO_ERROR;
	RPC_CLIENT_GET_ACCOUNT t;
	// Parameter list that can be specified
	PARAM args[] =
	{
		{"[name]", CmdPrompt, _UU("CMD_AccountCreate_Prompt_Name"), CmdEvalNotEmpty, NULL},
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

		// Verify the server certificate
		CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_SERVER_CERT_USE"),
			t.CheckServerCert ? _UU("CMD_MSG_ENABLE") : _UU("CMD_MSG_DISABLE"));

		// Registered specific certificate
		if (t.ServerCert != NULL)
		{
			GetAllNameFromX(tmp, sizeof(tmp), t.ServerCert);
			CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_SERVER_CERT_NAME"), tmp);
		}

		if (t.CheckServerCert)
		{
			CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_RETRY_ON_SERVER_CERT"),
				t.RetryOnServerCert ? _UU("CMD_MSG_ENABLE") : _UU("CMD_MSG_DISABLE"));
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
			
		// Disable UDP Acceleration
		CtInsert(ct, _UU("CMD_ACCOUNT_COLUMN_DISABLEUDP"),
			t.ClientOption->NoUdpAcceleration ? _UU("CMD_MSG_ENABLE") : _UU("CMD_MSG_DISABLE"));	

		CtFree(ct, c);
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