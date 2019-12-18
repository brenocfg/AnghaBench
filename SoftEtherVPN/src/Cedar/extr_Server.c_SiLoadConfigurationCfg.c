#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  machine_name2 ;
typedef  int /*<<< orphan*/  machine_name ;
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_23__ {int Bridge; } ;
struct TYPE_22__ {char* ProxyHostName; char* ProxyUsername; char* CustomHttpHeader; int /*<<< orphan*/  ProxyPassword; void* ProxyPort; void* ProxyType; } ;
struct TYPE_21__ {scalar_t__ ServerType; void* IPsecMessageDisplayed; TYPE_4__* Cedar; void* DDnsClient; void* ConfigRevision; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ INTERNET_SETTING ;
typedef  int /*<<< orphan*/  HUB ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 void* CfgGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * CfgGetBuf (int /*<<< orphan*/ *,char*) ; 
 int CfgGetByte (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * CfgGetFolder (int /*<<< orphan*/ *,char*) ; 
 void* CfgGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CfgGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 scalar_t__ CfgIsItem (int /*<<< orphan*/ *,char*) ; 
 char* DecryptPassword (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DelHub (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DestroyServerCapsCache (TYPE_1__*) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetHub (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetMachineHostName (char*,int) ; 
 scalar_t__ GetServerCapsBool (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  InitEth () ; 
 int /*<<< orphan*/  LockHubList (TYPE_4__*) ; 
 int MAX_SIZE ; 
 void* NewDDNSClient (TYPE_4__*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  ReleaseHub (int /*<<< orphan*/ *) ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  SLog (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  SiLoadHubs (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiLoadIPsec (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiLoadL3Switchs (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiLoadLicenseManager (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiLoadListeners (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiLoadLocalBridges (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiLoadServerCfg (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  StopHub (int /*<<< orphan*/ *) ; 
 scalar_t__ StrCmpi (char*,char*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  UnlockHubList (TYPE_4__*) ; 
 int /*<<< orphan*/  VG_HUBNAME ; 
 int /*<<< orphan*/  Win32SetEnableSeLow (int) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

bool SiLoadConfigurationCfg(SERVER *s, FOLDER *root)
{
	FOLDER *f1, *f2, *f3, *f4, *f5, *f6, *f7, *f8, *f;
	// Validate arguments
	if (s == NULL || root == NULL)
	{
		return false;
	}

	f = NULL;


	f1 = CfgGetFolder(root, "ServerConfiguration");
	f2 = CfgGetFolder(root, "VirtualHUB");
	f3 = CfgGetFolder(root, "ListenerList");
	f4 = CfgGetFolder(root, "LocalBridgeList");
	f5 = CfgGetFolder(root, "VirtualLayer3SwitchList");
	f6 = CfgGetFolder(root, "LicenseManager");
	f7 = CfgGetFolder(root, "IPsec");
	f8 = CfgGetFolder(root, "DDnsClient");

	if (f1 == NULL)
	{
		SLog(s->Cedar, "LS_BAD_CONFIG");
		return false;
	}

#ifdef	OS_WIN32
	if (f4 != NULL)
	{
		// Read the flag of using the SeLow driver
		bool b = true;

		if (CfgIsItem(f4, "EnableSoftEtherKernelModeDriver"))
		{
			b = CfgGetBool(f4, "EnableSoftEtherKernelModeDriver");
		}

		Win32SetEnableSeLow(b);
	}
#endif	// OS_WIN32

	// Ethernet initialization
	InitEth();

	s->ConfigRevision = CfgGetInt(root, "ConfigRevision");

	if (s->Cedar->Bridge == false && f6 != NULL)
	{
		if (GetServerCapsBool(s, "b_support_license"))
		{
			SiLoadLicenseManager(s, f6);
		}
	}

	DestroyServerCapsCache(s);

	SiLoadServerCfg(s, f1);

	if (s->ServerType != SERVER_TYPE_FARM_MEMBER)
	{
		SiLoadHubs(s, f2);
	}

	SiLoadListeners(s, f3);

	if (f4 != NULL)
	{
		SiLoadLocalBridges(s, f4);
	}

	if (s->Cedar->Bridge == false && f5 != NULL)
	{
		SiLoadL3Switchs(s, f5);
	}

	if (f7 != NULL && GetServerCapsBool(s, "b_support_ipsec"))
	{
		SiLoadIPsec(s, f7);
	}

	if (s->Cedar->Bridge == false)
	{
		if (f8 == NULL)
		{
			// Create a DDNS client with a new key
			s->DDnsClient = NewDDNSClient(s->Cedar, NULL, NULL);
		}
		else
		{
			// Create by reading the setting of the DDNS client
			UCHAR key[SHA1_SIZE];
			if (CfgGetBool(f8, "Disabled"))
			{
				// Disabled
			}
			else
			{
				char machine_name[MAX_SIZE];
				char machine_name2[MAX_SIZE];
				INTERNET_SETTING t;
				BUF *pw;

				// Proxy Setting
				Zero(&t, sizeof(t));
				t.ProxyType = CfgGetInt(f8, "ProxyType");
				CfgGetStr(f8, "ProxyHostName", t.ProxyHostName, sizeof(t.ProxyHostName));
				t.ProxyPort = CfgGetInt(f8, "ProxyPort");
				CfgGetStr(f8, "ProxyUsername", t.ProxyUsername, sizeof(t.ProxyUsername));
				pw = CfgGetBuf(f8, "ProxyPassword");
				if (pw != NULL)
				{
					char *pw_str = DecryptPassword(pw);
					StrCpy(t.ProxyPassword, sizeof(t.ProxyPassword), pw_str);

					Free(pw_str);
					FreeBuf(pw);
				}

				CfgGetStr(f8, "CustomHttpHeader", t.CustomHttpHeader, sizeof(t.CustomHttpHeader));

				GetMachineHostName(machine_name, sizeof(machine_name));

				CfgGetStr(f8, "LocalHostname", machine_name2, sizeof(machine_name2));

				if (CfgGetByte(f8, "Key", key, sizeof(key)) != sizeof(key) || StrCmpi(machine_name, machine_name2) != 0)
				{
					// Create a DDNS client with a new key
					s->DDnsClient = NewDDNSClient(s->Cedar, NULL, &t);
				}
				else
				{
					// Create the DDNS client with stored key
					s->DDnsClient = NewDDNSClient(s->Cedar, key, &t);
				}
			}
		}
	}


	{
		HUB *h = NULL;

		// Remove the virtual HUB "VPNGATE" when VGS disabled
		LockHubList(s->Cedar);
		{
			h = GetHub(s->Cedar, VG_HUBNAME);
		}
		UnlockHubList(s->Cedar);

		if (h != NULL)
		{
			StopHub(h);
			DelHub(s->Cedar, h);
			ReleaseHub(h);
		}
	}

	s->IPsecMessageDisplayed = CfgGetBool(root, "IPsecMessageDisplayed");


	return true;
}