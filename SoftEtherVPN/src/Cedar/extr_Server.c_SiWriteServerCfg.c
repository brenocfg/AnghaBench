#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_8__ ;
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  str ;
typedef  scalar_t__ UINT ;
struct TYPE_16__ {int /*<<< orphan*/  Tls_Disable1_2; int /*<<< orphan*/  Tls_Disable1_1; int /*<<< orphan*/  Tls_Disable1_0; } ;
struct TYPE_23__ {int Build; int Bridge; char* OpenVPNDefaultClientOption; char* CipherList; int DhParamBits; int /*<<< orphan*/  lock; TYPE_1__ SslAcceptSettings; int /*<<< orphan*/  TrafficLock; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  UsernameHubSeparator; int /*<<< orphan*/  ServerK; int /*<<< orphan*/  ServerX; int /*<<< orphan*/  OpenVPNPushDummyIPv4AddressOnL2Mode; int /*<<< orphan*/  DisableIPv6Listener; } ;
struct TYPE_22__ {char* ServerName; int ServerPort; int UdpMode; int Interval; int /*<<< orphan*/  lock; int /*<<< orphan*/  Enable; } ;
struct TYPE_21__ {char* OpenVPNPortList; char* OpenVPNObfuscationMask; int /*<<< orphan*/  OpenVPNObfuscation; } ;
struct TYPE_20__ {int AutoSaveConfigSpanSaved; int ServerType; int UpdatedServerType; char* ControllerName; int ControllerPort; scalar_t__ NumPublicPort; int Weight; int /*<<< orphan*/  DisableJsonRpcWebApi; int /*<<< orphan*/  StrictSyslogDatetimeFormat; int /*<<< orphan*/  DisableCoreDumpOnUnix; int /*<<< orphan*/  DisableGetHostNameWhenAcceptTcp; int /*<<< orphan*/  EnableVpnAzure; int /*<<< orphan*/ * AzureClient; int /*<<< orphan*/  ControllerOnly; int /*<<< orphan*/ * PublicPorts; int /*<<< orphan*/  PublicIp; int /*<<< orphan*/  MemberPassword; int /*<<< orphan*/  HashedPassword; TYPE_8__* Cedar; int /*<<< orphan*/  NoSendSignature; int /*<<< orphan*/  SaveDebugLog; int /*<<< orphan*/  UseWebTimePage; int /*<<< orphan*/  EnableVpnOverDns; int /*<<< orphan*/  EnableVpnOverIcmp; int /*<<< orphan*/  DisableOpenVPNServer; int /*<<< orphan*/  DisableSSTPServer; int /*<<< orphan*/  DisableNatTraversal; int /*<<< orphan*/  NoDebugDump; int /*<<< orphan*/  NoHighPriorityProcess; int /*<<< orphan*/  NoLinuxArpFilter; int /*<<< orphan*/  UseWebUI; TYPE_3__* Eraser; int /*<<< orphan*/  DisableDeadLockCheck; int /*<<< orphan*/  DisableDosProtection; TYPE_7__* Keep; TYPE_2__* Logger; int /*<<< orphan*/  ListenIP; int /*<<< orphan*/  BackupConfigOnlyWhenModified; int /*<<< orphan*/  DontBackupConfig; } ;
struct TYPE_19__ {int SaveType; char* Hostname; int Port; } ;
struct TYPE_18__ {int /*<<< orphan*/  MinFreeSpace; } ;
struct TYPE_17__ {int SwitchType; } ;
struct TYPE_15__ {scalar_t__ OsType; } ;
typedef  TYPE_4__ SYSLOG_SETTING ;
typedef  TYPE_5__ SERVER ;
typedef  TYPE_6__ OPENVPN_SSTP_CONFIG ;
typedef  TYPE_7__ KEEP ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_8__ CEDAR ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddBuf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CfgAddByte (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CfgAddInt (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  CfgAddInt64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddIp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CfgAddIp32 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GSF_DISABLE_SESSION_RECONNECT ; 
 int GetEraserCheckInterval () ; 
 int GetGetIpThreadMaxNum () ; 
 int /*<<< orphan*/  GetGlobalServerFlag (int /*<<< orphan*/ ) ; 
 int GetMaxConnectionsPerIp () ; 
 int /*<<< orphan*/  GetMaxLogSize () ; 
 int GetMaxUnestablishedConnections () ; 
 TYPE_14__* GetOsInfo () ; 
 int /*<<< orphan*/ * KToBuf (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int MAX_PUBLIC_PORT_NUM ; 
 int MAX_SIZE ; 
 scalar_t__ OSTYPE_LINUX ; 
 int SERVER_TYPE_FARM_CONTROLLER ; 
 int SERVER_TYPE_FARM_MEMBER ; 
 int SERVER_TYPE_STANDALONE ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  SiGetOpenVPNAndSSTPConfig (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  SiGetSysLogSetting (TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  SiWriteGlobalParamsCfg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiWriteTraffic (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCat (char*,int,char*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,int /*<<< orphan*/ *) ; 
 int StrLen (char*) ; 
 int /*<<< orphan*/  ToStr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * XToBuf (int /*<<< orphan*/ ,int) ; 

void SiWriteServerCfg(FOLDER *f, SERVER *s)
{
	BUF *b;
	CEDAR *c;
	FOLDER *params_folder;
	// Validate arguments
	if (f == NULL || s == NULL)
	{
		return;
	}

	CfgAddInt(f, "MaxConcurrentDnsClientThreads", GetGetIpThreadMaxNum());

	CfgAddInt(f, "CurrentBuild", s->Cedar->Build);

	CfgAddInt(f, "AutoSaveConfigSpan", s->AutoSaveConfigSpanSaved / 1000);

	CfgAddBool(f, "DontBackupConfig", s->DontBackupConfig);
	CfgAddBool(f, "BackupConfigOnlyWhenModified", s->BackupConfigOnlyWhenModified);

	CfgAddIp(f, "ListenIP", &s->ListenIP);

	if (s->Logger != NULL)
	{
		CfgAddInt(f, "ServerLogSwitchType", s->Logger->SwitchType);
	}

	CfgAddInt64(f, "LoggerMaxLogSize", GetMaxLogSize());

	params_folder = CfgCreateFolder(f, "GlobalParams");

	if (params_folder != NULL)
	{
		SiWriteGlobalParamsCfg(params_folder);
	}

	c = s->Cedar;

	Lock(c->lock);
	{
		FOLDER *syslog_f;
		Lock(s->Keep->lock);
		{
			KEEP *k = s->Keep;
			CfgAddBool(f, "UseKeepConnect", k->Enable);
			CfgAddStr(f, "KeepConnectHost", k->ServerName);
			CfgAddInt(f, "KeepConnectPort", k->ServerPort);
			CfgAddInt(f, "KeepConnectProtocol", k->UdpMode);
			CfgAddInt(f, "KeepConnectInterval", k->Interval / 1000);
		}
		Unlock(s->Keep->lock);

		// syslog
		syslog_f = CfgCreateFolder(f, "SyslogSettings");
		if (syslog_f != NULL)
		{
			SYSLOG_SETTING set;

			SiGetSysLogSetting(s, &set);

			CfgAddInt(syslog_f, "SaveType", set.SaveType);
			CfgAddStr(syslog_f, "HostName", set.Hostname);
			CfgAddInt(syslog_f, "Port", set.Port);
		}

		// IPv6 listener disable setting
		CfgAddBool(f, "DisableIPv6Listener", s->Cedar->DisableIPv6Listener);

		// DoS
		CfgAddBool(f, "DisableDosProtection", s->DisableDosProtection);

		// MaxConnectionsPerIP
		CfgAddInt(f, "MaxConnectionsPerIP", GetMaxConnectionsPerIp());

		// MaxUnestablishedConnections
		CfgAddInt(f, "MaxUnestablishedConnections", GetMaxUnestablishedConnections());

		// DeadLock
		CfgAddBool(f, "DisableDeadLockCheck", s->DisableDeadLockCheck);

		// Eraser related
		CfgAddInt64(f, "AutoDeleteCheckDiskFreeSpaceMin", s->Eraser->MinFreeSpace);
		CfgAddInt(f, "AutoDeleteCheckIntervalSecs", GetEraserCheckInterval());

		// WebUI
		CfgAddBool(f, "UseWebUI", s->UseWebUI);


		// NoLinuxArpFilter
		if (GetOsInfo()->OsType == OSTYPE_LINUX)
		{
			CfgAddBool(f, "NoLinuxArpFilter", s->NoLinuxArpFilter);
		}

		// NoHighPriorityProcess
		CfgAddBool(f, "NoHighPriorityProcess", s->NoHighPriorityProcess);

#ifdef	OS_WIN32
		CfgAddBool(f, "NoDebugDump", s->NoDebugDump);
#endif	// OS_WIN32

		if (s->ServerType == SERVER_TYPE_STANDALONE)
		{
			if (c->Bridge == false)
			{
				// Disable the NAT-traversal feature
				CfgAddBool(f, "DisableNatTraversal", s->DisableNatTraversal);

				// Disable the SSTP server function
				CfgAddBool(f, "DisableSSTPServer", s->DisableSSTPServer);

				// Disable the OpenVPN server function
				CfgAddBool(f, "DisableOpenVPNServer", s->DisableOpenVPNServer);
			}
		}

		CfgAddStr(f, "OpenVPNDefaultClientOption", c->OpenVPNDefaultClientOption);

		CfgAddBool(f, "OpenVPNPushDummyIPv4AddressOnL2Mode", c->OpenVPNPushDummyIPv4AddressOnL2Mode);

		if (c->Bridge == false)
		{
			OPENVPN_SSTP_CONFIG config;

			// VPN over ICMP
			CfgAddBool(f, "EnableVpnOverIcmp", s->EnableVpnOverIcmp);

			// VPN over DNS
			CfgAddBool(f, "EnableVpnOverDns", s->EnableVpnOverDns);

			SiGetOpenVPNAndSSTPConfig(s, &config);

			CfgAddStr(f, "OpenVPN_UdpPortList", config.OpenVPNPortList);

			CfgAddBool(f, "OpenVPNObfuscation", config.OpenVPNObfuscation);
			CfgAddStr(f, "OpenVPNObfuscationMask", config.OpenVPNObfuscationMask);
		}

		// WebTimePage
		CfgAddBool(f, "UseWebTimePage", s->UseWebTimePage);

		// Debug log
		CfgAddBool(f, "SaveDebugLog", s->SaveDebugLog);

		// Let the client not to send a signature
		CfgAddBool(f, "NoSendSignature", s->NoSendSignature);

		// Server certificate
		b = XToBuf(c->ServerX, false);
		CfgAddBuf(f, "ServerCert", b);
		FreeBuf(b);

		// Server private key
		b = KToBuf(c->ServerK, false, NULL);
		CfgAddBuf(f, "ServerKey", b);
		FreeBuf(b);

		{
			// Character which separates the username from the hub name
			char str[2];
			StrCpy(str, sizeof(str), &c->UsernameHubSeparator);
			CfgAddStr(f, "UsernameHubSeparator", str);
		}

		// Traffic information
		Lock(c->TrafficLock);
		{
			SiWriteTraffic(f, "ServerTraffic", c->Traffic);
		}
		Unlock(c->TrafficLock);

		// Type of server
		if (s->Cedar->Bridge == false)
		{
			CfgAddInt(f, "ServerType", s->UpdatedServerType);
		}

		// Cipher Name
		CfgAddStr(f, "CipherName", s->Cedar->CipherList);

		// Password
		CfgAddByte(f, "HashedPassword", s->HashedPassword, sizeof(s->HashedPassword));

		if (s->UpdatedServerType == SERVER_TYPE_FARM_MEMBER)
		{
			char tmp[6 * MAX_PUBLIC_PORT_NUM + 1];
			UINT i;
			// Setting items in the case of farm members
			CfgAddStr(f, "ControllerName", s->ControllerName);
			CfgAddInt(f, "ControllerPort", s->ControllerPort);
			CfgAddByte(f, "MemberPassword", s->MemberPassword, SHA1_SIZE);
			CfgAddIp32(f, "PublicIp", s->PublicIp);
			tmp[0] = 0;
			for (i = 0;i < s->NumPublicPort;i++)
			{
				char tmp2[MAX_SIZE];
				ToStr(tmp2, s->PublicPorts[i]);
				StrCat(tmp, sizeof(tmp), tmp2);
				StrCat(tmp, sizeof(tmp), ",");
			}
			if (StrLen(tmp) >= 1)
			{
				if (tmp[StrLen(tmp) - 1] == ',')
				{
					tmp[StrLen(tmp) - 1] = 0;
				}
			}
			CfgAddStr(f, "PublicPorts", tmp);
		}

		if (s->UpdatedServerType != SERVER_TYPE_STANDALONE)
		{
			CfgAddInt(f, "ClusterMemberWeight", s->Weight);
		}

		if (s->UpdatedServerType == SERVER_TYPE_FARM_CONTROLLER)
		{
			CfgAddBool(f, "ControllerOnly", s->ControllerOnly);
		}

		// VPN Azure Client
		if (s->AzureClient != NULL)
		{
			CfgAddBool(f, "EnableVpnAzure", s->EnableVpnAzure);
		}

		CfgAddBool(f, "DisableGetHostNameWhenAcceptTcp", s->DisableGetHostNameWhenAcceptTcp);
		CfgAddBool(f, "DisableCoreDumpOnUnix", s->DisableCoreDumpOnUnix);

		CfgAddBool(f, "Tls_Disable1_0", c->SslAcceptSettings.Tls_Disable1_0);
		CfgAddBool(f, "Tls_Disable1_1", c->SslAcceptSettings.Tls_Disable1_1);
		CfgAddBool(f, "Tls_Disable1_2", c->SslAcceptSettings.Tls_Disable1_2);
		CfgAddInt(f, "DhParamBits", c->DhParamBits);

		// Disable session reconnect
		CfgAddBool(f, "DisableSessionReconnect", GetGlobalServerFlag(GSF_DISABLE_SESSION_RECONNECT));

		CfgAddBool(f, "StrictSyslogDatetimeFormat", s->StrictSyslogDatetimeFormat);

		// Disable JSON-RPC Web API
		CfgAddBool(f, "DisableJsonRpcWebApi", s->DisableJsonRpcWebApi);
	}
	Unlock(c->lock);
}