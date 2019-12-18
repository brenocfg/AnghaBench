#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ OsType; } ;
struct TYPE_13__ {int /*<<< orphan*/  CustomHttpHeader; int /*<<< orphan*/  ProxyPassword; int /*<<< orphan*/  ProxyUsername; int /*<<< orphan*/  ProxyPort; int /*<<< orphan*/  ProxyHostName; int /*<<< orphan*/  ProxyType; } ;
struct TYPE_15__ {TYPE_4__* CmSetting; TYPE_2__* Cedar; int /*<<< orphan*/  DontSavePassword; int /*<<< orphan*/  UseSecureDeviceId; int /*<<< orphan*/  PasswordRemoteOnly; int /*<<< orphan*/  EncryptedPassword; TYPE_3__ CommonProxySetting; TYPE_1__* Eraser; int /*<<< orphan*/  Config; } ;
struct TYPE_14__ {int /*<<< orphan*/  HashedPassword; int /*<<< orphan*/  LockMode; int /*<<< orphan*/  EasyMode; } ;
struct TYPE_12__ {int /*<<< orphan*/  HttpUserAgent; } ;
struct TYPE_11__ {int /*<<< orphan*/  MinFreeSpace; } ;
typedef  TYPE_3__ INTERNET_SETTING ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_4__ CM_SETTING ;
typedef  TYPE_5__ CLIENT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddBuf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CfgAddByte (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CfgAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddInt64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CiWriteAccountDatabase (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiWriteCAList (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiWriteClientConfig (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiWriteVLanList (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EncryptPassword (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 TYPE_6__* GetOsInfo () ; 
 int IsEmptyStr (int /*<<< orphan*/ ) ; 
 int IsZero (int /*<<< orphan*/ ,int) ; 
 scalar_t__ OSTYPE_MACOS_X ; 
 scalar_t__ OS_IS_UNIX (scalar_t__) ; 
 int SHA1_SIZE ; 

void CiWriteSettingToCfg(CLIENT *c, FOLDER *root)
{
	FOLDER *cc;
	FOLDER *account_database;
	FOLDER *ca;
	FOLDER *vlan;
	FOLDER *cmsetting;
	FOLDER *proxy;
	// Validate arguments
	if (c == NULL || root == NULL)
	{
		return;
	}

	cmsetting = CfgCreateFolder(root, "ClientManagerSetting");

	// CLIENT_CONFIG
	cc = CfgCreateFolder(root, "Config");
	CiWriteClientConfig(cc, &c->Config);


	// Eraser
	CfgAddInt64(cc, "AutoDeleteCheckDiskFreeSpaceMin", c->Eraser->MinFreeSpace);

	// Account Database
	account_database = CfgCreateFolder(root, "AccountDatabase");
	CiWriteAccountDatabase(c, account_database);

	// Proxy
	proxy = CfgCreateFolder(root, "CommonProxySetting");
	if (proxy != NULL)
	{
		INTERNET_SETTING *t = &c->CommonProxySetting;
		BUF *pw;

		CfgAddInt(proxy, "ProxyType", t->ProxyType);
		CfgAddStr(proxy, "ProxyHostName", t->ProxyHostName);
		CfgAddInt(proxy, "ProxyPort", t->ProxyPort);
		CfgAddStr(proxy, "ProxyUsername", t->ProxyUsername);

		if (IsEmptyStr(t->ProxyPassword) == false)
		{
			pw = EncryptPassword(t->ProxyPassword);

			CfgAddBuf(proxy, "ProxyPassword", pw);

			FreeBuf(pw);
		}

		CfgAddStr(proxy, "CustomHttpHeader", t->CustomHttpHeader);
	}

	// CA
	ca = CfgCreateFolder(root, "RootCA");
	CiWriteCAList(c, ca);

	// VLAN
	if (OS_IS_UNIX(GetOsInfo()->OsType)
#ifdef	NO_VLAN
	    && GetOsInfo()->OsType != OSTYPE_MACOS_X
#endif	// NO_VLAN
	    )
	{
		vlan = CfgCreateFolder(root, "UnixVLan");
		CiWriteVLanList(c, vlan);
	}

	// Password
	CfgAddByte(root, "EncryptedPassword", c->EncryptedPassword, SHA1_SIZE);
	CfgAddBool(root, "PasswordRemoteOnly", c->PasswordRemoteOnly);

	// UseSecureDeviceId
	CfgAddInt(root, "UseSecureDeviceId", c->UseSecureDeviceId);

	// DontSavePassword
	CfgAddBool(root, "DontSavePassword", c->DontSavePassword);

	// UserAgent
	if (c->Cedar != NULL)
	{
		CfgAddStr(root, "UserAgent", c->Cedar->HttpUserAgent);
	}

	if (cmsetting != NULL)
	{
		CM_SETTING *s = c->CmSetting;

		CfgAddBool(cmsetting, "EasyMode", s->EasyMode);
		CfgAddBool(cmsetting, "LockMode", s->LockMode);

		if (IsZero(s->HashedPassword, sizeof(s->HashedPassword)) == false)
		{
			CfgAddByte(cmsetting, "HashedPassword", s->HashedPassword, sizeof(s->HashedPassword));
		}
	}
}