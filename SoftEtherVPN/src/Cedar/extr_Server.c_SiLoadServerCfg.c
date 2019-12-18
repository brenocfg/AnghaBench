#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  set ;
typedef  int /*<<< orphan*/  k ;
typedef  int /*<<< orphan*/  config ;
typedef  int /*<<< orphan*/  X ;
typedef  size_t UINT ;
struct TYPE_20__ {void* Tls_Disable1_2; void* Tls_Disable1_1; void* Tls_Disable1_0; } ;
struct TYPE_25__ {char* OpenVPNDefaultClientOption; int OpenVPNPushDummyIPv4AddressOnL2Mode; int Bridge; char UsernameHubSeparator; int DhParamBits; int /*<<< orphan*/  lock; TYPE_1__ SslAcceptSettings; int /*<<< orphan*/  TrafficLock; int /*<<< orphan*/  Traffic; void* DisableIPv6Listener; } ;
struct TYPE_24__ {int Server; char* ServerName; int ServerPort; int UdpMode; int Interval; int /*<<< orphan*/  lock; void* Enable; } ;
struct TYPE_23__ {int AutoSaveConfigSpan; int BackupConfigOnlyWhenModified; int DisableSSTPServer; int DisableOpenVPNServer; int DisableNatTraversal; int EnableVpnOverIcmp; int EnableVpnOverDns; int SaveDebugLog; int UpdatedServerType; int ServerType; int Weight; char* ControllerName; int ControllerPort; int NumPublicPort; int DisableGetHostNameWhenAcceptTcp; int DisableCoreDumpOnUnix; scalar_t__ OpenVpnServerUdp; void* DisableJsonRpcWebApi; void* StrictSyslogDatetimeFormat; void* EnableVpnAzure; int /*<<< orphan*/ * PublicPorts; int /*<<< orphan*/  PublicIp; int /*<<< orphan*/  MemberPassword; TYPE_8__* Cedar; void* ControllerOnly; int /*<<< orphan*/  HashedPassword; void* NoSendSignature; int /*<<< orphan*/  DebugLog; void* NoDebugDump; void* NoHighPriorityProcess; void* NoLinuxArpFilter; void* UseWebTimePage; void* UseWebUI; int /*<<< orphan*/  Logger; int /*<<< orphan*/  Eraser; void* DisableDeadLockCheck; void* DisableDosProtection; TYPE_7__* Keep; int /*<<< orphan*/  ListenIP; void* DontBackupConfig; } ;
struct TYPE_22__ {char* KeepConnectHost; int KeepConnectPort; int KeepConnectProtocol; int KeepConnectInterval; int SaveType; char* Hostname; int Port; int EnableOpenVPN; int EnableSSTP; char* OpenVPNPortList; char* OpenVPNObfuscationMask; void* OpenVPNObfuscation; void* UseKeepConnect; } ;
struct TYPE_21__ {int NumTokens; int /*<<< orphan*/ * Token; } ;
typedef  TYPE_2__ TOKEN_LIST ;
typedef  TYPE_3__ SYSLOG_SETTING ;
typedef  TYPE_4__ SERVER ;
typedef  TYPE_3__ RPC_KEEP ;
typedef  TYPE_3__ OPENVPN_SSTP_CONFIG ;
typedef  TYPE_7__ KEEP ;
typedef  int /*<<< orphan*/  K ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_8__ CEDAR ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/ * BufToK (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BufToX (int /*<<< orphan*/ *,int) ; 
 char* CLIENT_DEFAULT_KEEPALIVE_HOST ; 
 void* CfgGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * CfgGetBuf (int /*<<< orphan*/ *,char*) ; 
 int CfgGetByte (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * CfgGetFolder (int /*<<< orphan*/ *,char*) ; 
 int CfgGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CfgGetInt64 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CfgGetIp (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CfgGetIp32 (int /*<<< orphan*/ *,char*) ; 
 int CfgGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int CfgIsItem (int /*<<< orphan*/ *,char*) ; 
 int CheckXandK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t DEFAULT_GETIP_THREAD_MAX_NUM ; 
 char DEFAULT_USERNAME_HUB_SEPARATOR ; 
 int DH_PARAM_BITS_DEFAULT ; 
 int /*<<< orphan*/  DhNewFromBits (int) ; 
 int /*<<< orphan*/  DisableGetHostNameWhenAcceptInit () ; 
 void* FARM_DEFAULT_WEIGHT ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeToken (TYPE_2__*) ; 
 int /*<<< orphan*/  FreeX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GSF_DISABLE_SESSION_RECONNECT ; 
 scalar_t__ GetServerCapsBool (TYPE_4__*,char*) ; 
 int IsEmptyStr (char*) ; 
 scalar_t__ IsPrintableAsciiChar (char) ; 
 int KEEP_INTERVAL_DEFAULT ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int MAKESURE (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_PUBLIC_PORT_NUM ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  MsSetEnableMinidump (int) ; 
 int /*<<< orphan*/  NewEraser (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NewTinyLog () ; 
 int /*<<< orphan*/  OPENVPN_UDP_PORT ; 
 int /*<<< orphan*/  OpenVpnServerUdpSetDhParam (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__* ParseToken (char*,char*) ; 
 int SERVER_FILE_SAVE_INTERVAL_DEFAULT ; 
 int /*<<< orphan*/  SERVER_FILE_SAVE_INTERVAL_MAX ; 
 int /*<<< orphan*/  SERVER_FILE_SAVE_INTERVAL_MIN ; 
 int SERVER_TYPE_FARM_CONTROLLER ; 
 int SERVER_TYPE_FARM_MEMBER ; 
 int SERVER_TYPE_STANDALONE ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  SetCedarCert (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetCedarCipherList (TYPE_8__*,char*) ; 
 int /*<<< orphan*/  SetDhParam (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetEraserCheckInterval (int) ; 
 int /*<<< orphan*/  SetGetIpThreadMaxNum (size_t) ; 
 int /*<<< orphan*/  SetGlobalServerFlag (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  SetLogSwitchType (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  SetMaxConnectionsPerIp (int) ; 
 int /*<<< orphan*/  SetMaxLogSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetMaxUnestablishedConnections (int) ; 
 int /*<<< orphan*/  Sha0 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiGenerateDefaultCert (int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SiLoadGlobalParamsCfg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiLoadTraffic (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiSetOpenVPNAndSSTPConfig (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  SiSetSysLogSetting (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  StrCpy (char*,int,char*) ; 
 scalar_t__ StrLen (char*) ; 
 int /*<<< orphan*/  StrUpper (char*) ; 
 int /*<<< orphan*/  ToInt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ToStr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnixDisableCoreDump () ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 
 int /*<<< orphan*/ * ZeroMalloc (int) ; 

void SiLoadServerCfg(SERVER *s, FOLDER *f)
{
	BUF *b;
	CEDAR *c;
	char tmp[MAX_SIZE];
	X *x = NULL;
	K *k = NULL;
	FOLDER *params_folder;
	UINT i;
	// Validate arguments
	if (s == NULL || f == NULL)
	{
		return;
	}

	// Save interval related
	s->AutoSaveConfigSpan = CfgGetInt(f, "AutoSaveConfigSpan") * 1000;
	if (s->AutoSaveConfigSpan == 0)
	{
		s->AutoSaveConfigSpan = SERVER_FILE_SAVE_INTERVAL_DEFAULT;
	}
	else
	{
		s->AutoSaveConfigSpan = MAKESURE(s->AutoSaveConfigSpan, SERVER_FILE_SAVE_INTERVAL_MIN, SERVER_FILE_SAVE_INTERVAL_MAX);
	}

	i = CfgGetInt(f, "MaxConcurrentDnsClientThreads");
	if (i != 0)
	{
		SetGetIpThreadMaxNum(i);
	}
	else
	{
		SetGetIpThreadMaxNum(DEFAULT_GETIP_THREAD_MAX_NUM);
	}

	s->DontBackupConfig = CfgGetBool(f, "DontBackupConfig");
	CfgGetIp(f, "ListenIP", &s->ListenIP);

	if (CfgIsItem(f, "BackupConfigOnlyWhenModified"))
	{
		s->BackupConfigOnlyWhenModified = CfgGetBool(f, "BackupConfigOnlyWhenModified");
	}
	else
	{
		s->BackupConfigOnlyWhenModified = true;
	}

	// Server log switch type
	if (CfgIsItem(f, "ServerLogSwitchType"))
	{
		UINT st = CfgGetInt(f, "ServerLogSwitchType");

		SetLogSwitchType(s->Logger, st);
	}

	SetMaxLogSize(CfgGetInt64(f, "LoggerMaxLogSize"));

	params_folder = CfgGetFolder(f, "GlobalParams");
	SiLoadGlobalParamsCfg(params_folder);

	c = s->Cedar;
	Lock(c->lock);
	{
		OPENVPN_SSTP_CONFIG config;
		FOLDER *syslog_f;
		{
			RPC_KEEP k;

			// Keep-alive related
			Zero(&k, sizeof(k));
			k.UseKeepConnect = CfgGetBool(f, "UseKeepConnect");
			CfgGetStr(f, "KeepConnectHost", k.KeepConnectHost, sizeof(k.KeepConnectHost));
			k.KeepConnectPort = CfgGetInt(f, "KeepConnectPort");
			k.KeepConnectProtocol = CfgGetInt(f, "KeepConnectProtocol");
			k.KeepConnectInterval = CfgGetInt(f, "KeepConnectInterval") * 1000;
			if (k.KeepConnectPort == 0)
			{
				k.KeepConnectPort = 80;
			}
			if (StrLen(k.KeepConnectHost) == 0)
			{
				StrCpy(k.KeepConnectHost, sizeof(k.KeepConnectHost), CLIENT_DEFAULT_KEEPALIVE_HOST);
			}
			if (k.KeepConnectInterval == 0)
			{
				k.KeepConnectInterval = KEEP_INTERVAL_DEFAULT * 1000;
			}
			if (k.KeepConnectInterval < 5000)
			{
				k.KeepConnectInterval = 5000;
			}
			if (k.KeepConnectInterval > 600000)
			{
				k.KeepConnectInterval = 600000;
			}

			Lock(s->Keep->lock);
			{
				KEEP *keep = s->Keep;
				keep->Enable = k.UseKeepConnect;
				keep->Server = true;
				StrCpy(keep->ServerName, sizeof(keep->ServerName), k.KeepConnectHost);
				keep->ServerPort = k.KeepConnectPort;
				keep->UdpMode = k.KeepConnectProtocol;
				keep->Interval = k.KeepConnectInterval;
			}
			Unlock(s->Keep->lock);
		}

		// syslog
		syslog_f = CfgGetFolder(f, "SyslogSettings");
		if (syslog_f != NULL && GetServerCapsBool(s, "b_support_syslog"))
		{
			SYSLOG_SETTING set;

			Zero(&set, sizeof(set));

			set.SaveType = CfgGetInt(syslog_f, "SaveType");
			CfgGetStr(syslog_f, "HostName", set.Hostname, sizeof(set.Hostname));
			set.Port = CfgGetInt(syslog_f, "Port");

			SiSetSysLogSetting(s, &set);
		}

		// Whether to disable the IPv6 listener
		s->Cedar->DisableIPv6Listener = CfgGetBool(f, "DisableIPv6Listener");

		// DoS
		s->DisableDosProtection = CfgGetBool(f, "DisableDosProtection");

		// Num Connections Per IP
		SetMaxConnectionsPerIp(CfgGetInt(f, "MaxConnectionsPerIP"));

		// MaxUnestablishedConnections
		SetMaxUnestablishedConnections(CfgGetInt(f, "MaxUnestablishedConnections"));

		// DeadLock
		s->DisableDeadLockCheck = CfgGetBool(f, "DisableDeadLockCheck");

		// Eraser
		SetEraserCheckInterval(CfgGetInt(f, "AutoDeleteCheckIntervalSecs"));
		s->Eraser = NewEraser(s->Logger, CfgGetInt64(f, "AutoDeleteCheckDiskFreeSpaceMin"));

		// WebUI
		s->UseWebUI = CfgGetBool(f, "UseWebUI");


		// WebTimePage
		s->UseWebTimePage = CfgGetBool(f, "UseWebTimePage");

		// NoLinuxArpFilter
		s->NoLinuxArpFilter = CfgGetBool(f, "NoLinuxArpFilter");

		// NoHighPriorityProcess
		s->NoHighPriorityProcess = CfgGetBool(f, "NoHighPriorityProcess");

		// NoDebugDump
		s->NoDebugDump = CfgGetBool(f, "NoDebugDump");
		if (s->NoDebugDump)
		{
#ifdef	OS_WIN32
			MsSetEnableMinidump(false);
#endif	// OS_WIN32
		}

		// Disable the SSTP server function
		s->DisableSSTPServer = CfgGetBool(f, "DisableSSTPServer");

		// Disable the OpenVPN server function
		s->DisableOpenVPNServer = CfgGetBool(f, "DisableOpenVPNServer");

		// OpenVPN Default Option String
		if (CfgGetStr(f, "OpenVPNDefaultClientOption", tmp, sizeof(tmp)))
		{
			if (IsEmptyStr(tmp) == false)
			{
				StrCpy(c->OpenVPNDefaultClientOption,
					sizeof(c->OpenVPNDefaultClientOption), tmp);
			}
		}

		// OpenVPN Push a dummy IPv4 address on L2 mode
		if (CfgIsItem(f, "OpenVPNPushDummyIPv4AddressOnL2Mode") == false)
		{
			// Default enable
			c->OpenVPNPushDummyIPv4AddressOnL2Mode = true;
		}
		else
		{
			c->OpenVPNPushDummyIPv4AddressOnL2Mode = CfgGetBool(f, "OpenVPNPushDummyIPv4AddressOnL2Mode");
		}

		// Disable the NAT-traversal feature
		s->DisableNatTraversal = CfgGetBool(f, "DisableNatTraversal");

		if (s->Cedar->Bridge == false)
		{
			// Enable the VPN-over-ICMP
			if (CfgIsItem(f, "EnableVpnOverIcmp"))
			{
				s->EnableVpnOverIcmp = CfgGetBool(f, "EnableVpnOverIcmp");
			}
			else
			{
				s->EnableVpnOverIcmp = false;
			}

			// Enable the VPN-over-DNS
			if (CfgIsItem(f, "EnableVpnOverDns"))
			{
				s->EnableVpnOverDns = CfgGetBool(f, "EnableVpnOverDns");
			}
			else
			{
				s->EnableVpnOverDns = false;
			}
		}

		// Debug log
		s->SaveDebugLog = CfgGetBool(f, "SaveDebugLog");
		if (s->SaveDebugLog)
		{
			s->DebugLog = NewTinyLog();
		}

		// Let the client not to send a signature
		s->NoSendSignature = CfgGetBool(f, "NoSendSignature");

		// Server certificate
		b = CfgGetBuf(f, "ServerCert");
		if (b != NULL)
		{
			x = BufToX(b, false);
			FreeBuf(b);
		}

		// Server private key
		b = CfgGetBuf(f, "ServerKey");
		if (b != NULL)
		{
			k = BufToK(b, true, false, NULL);
			FreeBuf(b);
		}

		if (x == NULL || k == NULL || CheckXandK(x, k) == false)
		{
			FreeX(x);
			FreeK(k);
			SiGenerateDefaultCert(&x, &k);

			SetCedarCert(c, x, k);

			FreeX(x);
			FreeK(k);
		}
		else
		{
			SetCedarCert(c, x, k);

			FreeX(x);
			FreeK(k);
		}

		// Character which separates the username from the hub name
		if (CfgGetStr(f, "UsernameHubSeparator", tmp, sizeof(tmp)))
		{
			c->UsernameHubSeparator = IsPrintableAsciiChar(tmp[0]) ? tmp[0] : DEFAULT_USERNAME_HUB_SEPARATOR;
		}

		// Cipher Name
		if (CfgGetStr(f, "CipherName", tmp, sizeof(tmp)))
		{
			StrUpper(tmp);
			SetCedarCipherList(c, tmp);
		}

		// Traffic information
		Lock(c->TrafficLock);
		{
			SiLoadTraffic(f, "ServerTraffic", c->Traffic);
		}
		Unlock(c->TrafficLock);

		// Type of server
		s->UpdatedServerType = s->ServerType = CfgGetInt(f, "ServerType");

		// Password
		if (CfgGetByte(f, "HashedPassword", s->HashedPassword, sizeof(s->HashedPassword)) != sizeof(s->HashedPassword))
		{
			Sha0(s->HashedPassword, "", 0);
		}

		if (s->ServerType != SERVER_TYPE_STANDALONE)
		{
			// Performance ratio of the server
			s->Weight = CfgGetInt(f, "ClusterMemberWeight");
			if (s->Weight == 0)
			{
				s->Weight = FARM_DEFAULT_WEIGHT;
			}
		}
		else
		{
			s->Weight = FARM_DEFAULT_WEIGHT;
		}

		if (s->ServerType == SERVER_TYPE_FARM_CONTROLLER)
		{
			s->ControllerOnly = CfgGetBool(f, "ControllerOnly");
		}

		if (s->ServerType != SERVER_TYPE_STANDALONE)
		{
			// SSTP, OpenVPN, and NAT traversal can not be used in a cluster environment
			s->DisableNatTraversal = true;
			s->DisableSSTPServer = true;
			s->DisableOpenVPNServer = true;
		}

		if (s->Cedar->Bridge)
		{
			// SSTP, OpenVPN, and NAT traversal function can not be used in the bridge environment
			s->DisableNatTraversal = true;
			s->DisableSSTPServer = true;
			s->DisableOpenVPNServer = true;
		}

		// Read the OpenVPN Port List
		if (CfgGetStr(f, "OpenVPN_UdpPortList", tmp, sizeof(tmp)) == false)
		{
			{
				ToStr(tmp, OPENVPN_UDP_PORT);
			}
		}

		// Apply the configuration of SSTP and OpenVPN
		Zero(&config, sizeof(config));
		config.EnableOpenVPN = !s->DisableOpenVPNServer;
		config.EnableSSTP = !s->DisableSSTPServer;
		StrCpy(config.OpenVPNPortList, sizeof(config.OpenVPNPortList), tmp);

		config.OpenVPNObfuscation = CfgGetBool(f, "OpenVPNObfuscation");

		if (CfgGetStr(f, "OpenVPNObfuscationMask", tmp, sizeof(tmp)))
		{
			if (IsEmptyStr(tmp) == false)
			{
				StrCpy(config.OpenVPNObfuscationMask, sizeof(config.OpenVPNObfuscationMask), tmp);
			}
		}

		SiSetOpenVPNAndSSTPConfig(s, &config);

		if (s->ServerType == SERVER_TYPE_FARM_MEMBER)
		{
			char tmp[6 * MAX_PUBLIC_PORT_NUM + 1];
			// Load the settings item in the case of farm members
			CfgGetStr(f, "ControllerName", s->ControllerName, sizeof(s->ControllerName));
			s->ControllerPort = CfgGetInt(f, "ControllerPort");
			CfgGetByte(f, "MemberPassword", s->MemberPassword, SHA1_SIZE);
			s->PublicIp = CfgGetIp32(f, "PublicIp");
			if (CfgGetStr(f, "PublicPorts", tmp, sizeof(tmp)))
			{
				TOKEN_LIST *t = ParseToken(tmp, ", ");
				UINT i;
				s->NumPublicPort = t->NumTokens;
				s->PublicPorts = ZeroMalloc(s->NumPublicPort * sizeof(UINT));
				for (i = 0;i < s->NumPublicPort;i++)
				{
					s->PublicPorts[i] = ToInt(t->Token[i]);
				}
				FreeToken(t);
			}
		}

		// Configuration of VPN Azure Client
		s->EnableVpnAzure = CfgGetBool(f, "EnableVpnAzure");

		// Disable GetHostName when accepting TCP
		s->DisableGetHostNameWhenAcceptTcp = CfgGetBool(f, "DisableGetHostNameWhenAcceptTcp");

		if (s->DisableGetHostNameWhenAcceptTcp)
		{
			DisableGetHostNameWhenAcceptInit();
		}

		// Disable core dump on UNIX
		s->DisableCoreDumpOnUnix = CfgGetBool(f, "DisableCoreDumpOnUnix");

		// Disable session reconnect
		SetGlobalServerFlag(GSF_DISABLE_SESSION_RECONNECT, CfgGetBool(f, "DisableSessionReconnect"));

		c->SslAcceptSettings.Tls_Disable1_0 = CfgGetBool(f, "Tls_Disable1_0");
		c->SslAcceptSettings.Tls_Disable1_1 = CfgGetBool(f, "Tls_Disable1_1");
		c->SslAcceptSettings.Tls_Disable1_2 = CfgGetBool(f, "Tls_Disable1_2");

		s->StrictSyslogDatetimeFormat = CfgGetBool(f, "StrictSyslogDatetimeFormat");

		// Disable JSON-RPC Web API
		s->DisableJsonRpcWebApi = CfgGetBool(f, "DisableJsonRpcWebApi");

		// Bits of Diffie-Hellman parameters
		c->DhParamBits = CfgGetInt(f, "DhParamBits");
		if (c->DhParamBits == 0)
		{
			c->DhParamBits = DH_PARAM_BITS_DEFAULT;
		}

		SetDhParam(DhNewFromBits(c->DhParamBits));
		if (s->OpenVpnServerUdp)
		{
			OpenVpnServerUdpSetDhParam(s->OpenVpnServerUdp, DhNewFromBits(c->DhParamBits));
		}
	}
	Unlock(c->lock);

#ifdef	OS_UNIX
	if (s->DisableCoreDumpOnUnix)
	{
		UnixDisableCoreDump();
	}
#endif	// OS_UNIX
}