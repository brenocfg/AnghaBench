#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  p ;
typedef  int /*<<< orphan*/  id ;
struct TYPE_24__ {int IsL3Mode; int BridgeMode; int /*<<< orphan*/  Mss; int /*<<< orphan*/  Layer; int /*<<< orphan*/ * ClientCertificate; int /*<<< orphan*/  ClientHostname; int /*<<< orphan*/  CryptName; int /*<<< orphan*/  ServerPort; int /*<<< orphan*/  ServerIp; int /*<<< orphan*/  ClientPort; int /*<<< orphan*/  ClientIp; int /*<<< orphan*/  Password; int /*<<< orphan*/  HubName; int /*<<< orphan*/  UserName; int /*<<< orphan*/  Postfix; int /*<<< orphan*/  ClientName; } ;
struct TYPE_20__ {int /*<<< orphan*/ * X; } ;
struct TYPE_19__ {int /*<<< orphan*/  Password; int /*<<< orphan*/  Username; int /*<<< orphan*/  PeerInfo; } ;
struct TYPE_23__ {TYPE_3__ ClientCert; TYPE_2__ ClientKey; TYPE_1__* CipherEncrypt; } ;
struct TYPE_22__ {int /*<<< orphan*/  SockEvent; int /*<<< orphan*/  Cedar; } ;
struct TYPE_21__ {scalar_t__ Mode; int /*<<< orphan*/ * IpcAsync; int /*<<< orphan*/  ServerPort; int /*<<< orphan*/  ServerIp; int /*<<< orphan*/  ClientPort; int /*<<< orphan*/  ClientIp; int /*<<< orphan*/ * Ipc; } ;
struct TYPE_18__ {int IsNullCipher; int /*<<< orphan*/  Name; } ;
typedef  TYPE_4__ OPENVPN_SESSION ;
typedef  TYPE_5__ OPENVPN_SERVER ;
typedef  TYPE_6__ OPENVPN_CHANNEL ;
typedef  int /*<<< orphan*/  LIST ;
typedef  TYPE_7__ IPC_PARAM ;
typedef  int /*<<< orphan*/  IP ;
typedef  TYPE_7__ ETHERIP_ID ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Debug (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ EntryListHasKey (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  EntryListStrValue (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  FreeEntryList (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeIPC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPC_LAYER_2 ; 
 int /*<<< orphan*/  IPC_LAYER_3 ; 
 scalar_t__ IsEmptyStr (int /*<<< orphan*/ ) ; 
 int IsIPCConnected (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * NewEntryList (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/ * NewIPCAsync (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENVPN_IPC_CLIENT_NAME ; 
 int /*<<< orphan*/  OPENVPN_IPC_POSTFIX_L2 ; 
 int /*<<< orphan*/  OPENVPN_IPC_POSTFIX_L3 ; 
 scalar_t__ OPENVPN_MODE_L2 ; 
 scalar_t__ OPENVPN_MODE_L3 ; 
 int /*<<< orphan*/  OvsCalcTcpMss (TYPE_5__*,TYPE_4__*,TYPE_6__*) ; 
 int /*<<< orphan*/  PPPParseUsername (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_7__*,int) ; 

void OvsBeginIPCAsyncConnectionIfEmpty(OPENVPN_SERVER *s, OPENVPN_SESSION *se, OPENVPN_CHANNEL *c)
{
	// Validate arguments
	if (s == NULL || se == NULL || c == NULL)
	{
		return;
	}

	if (IsIPCConnected(se->Ipc) == false)
	{
		FreeIPC(se->Ipc);

		se->Ipc = NULL;
	}

	if (se->IpcAsync == NULL)
	{
		LIST *pi;
		IPC_PARAM p;
		ETHERIP_ID id;

		Zero(&p, sizeof(p));
		Zero(&id, sizeof(id));

		// Parse the user name
		PPPParseUsername(s->Cedar, c->ClientKey.Username, &id);


		// Build IPC connection parameters
		StrCpy(p.ClientName, sizeof(p.ClientName), OPENVPN_IPC_CLIENT_NAME);
		StrCpy(p.Postfix, sizeof(p.Postfix), (se->Mode == OPENVPN_MODE_L3 ? OPENVPN_IPC_POSTFIX_L3 : OPENVPN_IPC_POSTFIX_L2));

		StrCpy(p.UserName, sizeof(p.UserName), id.UserName);
		StrCpy(p.HubName, sizeof(p.HubName), id.HubName);
		StrCpy(p.Password, sizeof(p.Password), c->ClientKey.Password);

		Copy(&p.ClientIp, &se->ClientIp, sizeof(IP));
		p.ClientPort = se->ClientPort;

		Copy(&p.ServerIp, &se->ServerIp, sizeof(IP));
		p.ServerPort = se->ServerPort;

		if (c->CipherEncrypt->IsNullCipher == false)
		{
			StrCpy(p.CryptName, sizeof(p.CryptName), c->CipherEncrypt->Name);
		}

		// OpenVPN sends the default gateway's MAC address,
		// if the option --push-peer-info is enabled.
		// It also sends all of the client's environment
		// variables whose names start with "UV_".
		pi = NewEntryList(c->ClientKey.PeerInfo, "\n", "=\t");

		// Check presence of custom hostname
		if (EntryListHasKey(pi, "UV_HOSTNAME"))
		{
			StrCpy(p.ClientHostname, sizeof(p.ClientHostname), EntryListStrValue(pi, "UV_HOSTNAME"));
		}
		else // Use the default gateway's MAC address
		{
			StrCpy(p.ClientHostname, sizeof(p.ClientHostname), EntryListStrValue(pi, "IV_HWADDR"));
		}

		FreeEntryList(pi);

		if (se->Mode == OPENVPN_MODE_L3)
		{
			// L3 Mode
			p.IsL3Mode = true;
		}
		else
		{
			// L2 Mode
			p.BridgeMode = true;
		}

		if (IsEmptyStr(c->ClientKey.Username) || IsEmptyStr(c->ClientKey.Password))
		{
			// OpenVPN X.509 certificate authentication will be used only when no username / password is specified
			if (c->ClientCert.X != NULL)
			{
				p.ClientCertificate = c->ClientCert.X;
			}
		}

		p.Layer = (se->Mode == OPENVPN_MODE_L2) ? IPC_LAYER_2 : IPC_LAYER_3;

		// Calculate the MSS
		p.Mss = OvsCalcTcpMss(s, se, c);
		Debug("MSS=%u\n", p.Mss);

		// Start an IPC connection
		se->IpcAsync = NewIPCAsync(s->Cedar, &p, s->SockEvent);
	}
}