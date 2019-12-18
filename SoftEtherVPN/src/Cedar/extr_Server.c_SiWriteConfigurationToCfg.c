#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  region ;
typedef  int /*<<< orphan*/  machine_name ;
struct TYPE_17__ {char* ProxyHostName; char* ProxyUsername; char* CustomHttpHeader; int /*<<< orphan*/  ProxyPassword; int /*<<< orphan*/  ProxyPort; int /*<<< orphan*/  ProxyType; } ;
struct TYPE_16__ {scalar_t__ UpdatedServerType; int LedSpecial; int IPsecMessageDisplayed; TYPE_1__* DDnsClient; TYPE_12__* Cedar; scalar_t__ Led; int /*<<< orphan*/  ConfigRevision; } ;
struct TYPE_15__ {TYPE_3__ InternetSetting; int /*<<< orphan*/  Key; } ;
struct TYPE_14__ {int Bridge; } ;
typedef  TYPE_2__ SERVER ;
typedef  TYPE_3__ INTERNET_SETTING ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddBool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  CfgAddBuf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CfgAddByte (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddStr (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * EncryptPassword (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetMachineHostName (char*,int) ; 
 scalar_t__ GetServerCapsBool (TYPE_2__*,char*) ; 
 int IsEmptyStr (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 scalar_t__ SERVER_TYPE_FARM_MEMBER ; 
 int /*<<< orphan*/  SHA1_SIZE ; 
 int /*<<< orphan*/  SiGetCurrentRegion (TYPE_12__*,char*,int) ; 
 int /*<<< orphan*/  SiWriteHubs (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  SiWriteIPsec (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  SiWriteL3Switchs (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  SiWriteLicenseManager (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  SiWriteListeners (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  SiWriteLocalBridges (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  SiWriteServerCfg (int /*<<< orphan*/ *,TYPE_2__*) ; 
 char* TAG_ROOT ; 

FOLDER *SiWriteConfigurationToCfg(SERVER *s)
{
	FOLDER *root;
	char region[128];
	// Validate arguments
	if (s == NULL)
	{
		return NULL;
	}

	root = CfgCreateFolder(NULL, TAG_ROOT);

	SiGetCurrentRegion(s->Cedar, region, sizeof(region));

	CfgAddStr(root, "Region", region);

	CfgAddInt(root, "ConfigRevision", s->ConfigRevision);

	SiWriteListeners(CfgCreateFolder(root, "ListenerList"), s);

	SiWriteLocalBridges(CfgCreateFolder(root, "LocalBridgeList"), s);

	SiWriteServerCfg(CfgCreateFolder(root, "ServerConfiguration"), s);


	if (s->UpdatedServerType != SERVER_TYPE_FARM_MEMBER)
	{
		SiWriteHubs(CfgCreateFolder(root, "VirtualHUB"), s);
	}

	if (s->Cedar->Bridge == false)
	{
		SiWriteL3Switchs(CfgCreateFolder(root, "VirtualLayer3SwitchList"), s);

		if (GetServerCapsBool(s, "b_support_license"))
		{
			SiWriteLicenseManager(CfgCreateFolder(root, "LicenseManager"), s);
		}
	}

	if (s->Led)
	{
		CfgAddBool(root, "Led", true);
		CfgAddBool(root, "LedSpecial", s->LedSpecial);
	}

	if (GetServerCapsBool(s, "b_support_ipsec"))
	{
		SiWriteIPsec(CfgCreateFolder(root, "IPsec"), s);
	}

	if (s->Cedar->Bridge == false)
	{
		FOLDER *ddns_folder = CfgCreateFolder(root, "DDnsClient");

		if (s->DDnsClient == NULL)
		{
			// Disabled
			CfgAddBool(ddns_folder, "Disabled", true);
		}
		else
		{
			char machine_name[MAX_SIZE];
			BUF *pw;
			INTERNET_SETTING *t;
			// Enabled
			CfgAddBool(ddns_folder, "Disabled", false);
			CfgAddByte(ddns_folder, "Key", s->DDnsClient->Key, SHA1_SIZE);

			GetMachineHostName(machine_name, sizeof(machine_name));
			CfgAddStr(ddns_folder, "LocalHostname", machine_name);

			t = &s->DDnsClient->InternetSetting;

			CfgAddInt(ddns_folder, "ProxyType", t->ProxyType);
			CfgAddStr(ddns_folder, "ProxyHostName", t->ProxyHostName);
			CfgAddInt(ddns_folder, "ProxyPort", t->ProxyPort);
			CfgAddStr(ddns_folder, "ProxyUsername", t->ProxyUsername);

			if (IsEmptyStr(t->ProxyPassword) == false)
			{
				pw = EncryptPassword(t->ProxyPassword);

				CfgAddBuf(ddns_folder, "ProxyPassword", pw);

				FreeBuf(pw);
			}

			CfgAddStr(ddns_folder, "CustomHttpHeader", t->CustomHttpHeader);
		}
	}

	CfgAddBool(root, "IPsecMessageDisplayed", s->IPsecMessageDisplayed);


	return root;
}