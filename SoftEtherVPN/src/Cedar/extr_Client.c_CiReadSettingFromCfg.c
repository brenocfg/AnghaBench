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
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  user_agent ;
typedef  int /*<<< orphan*/  t ;
struct TYPE_19__ {int Enabled; int /*<<< orphan*/  Name; } ;
typedef  TYPE_2__ UNIX_VLAN ;
typedef  scalar_t__ UINT ;
struct TYPE_23__ {scalar_t__ OsType; } ;
struct TYPE_17__ {int /*<<< orphan*/  NicDownOnDisconnect; } ;
struct TYPE_22__ {TYPE_4__* CmSetting; void* DontSavePassword; TYPE_1__* Cedar; void* UseSecureDeviceId; void* PasswordRemoteOnly; int /*<<< orphan*/  EncryptedPassword; int /*<<< orphan*/  UnixVLanList; TYPE_12__ Config; int /*<<< orphan*/  Logger; int /*<<< orphan*/  Eraser; int /*<<< orphan*/  CommonProxySetting; } ;
struct TYPE_21__ {int /*<<< orphan*/  HashedPassword; void* LockMode; void* EasyMode; } ;
struct TYPE_20__ {char* ProxyHostName; char* ProxyUsername; char* CustomHttpHeader; int /*<<< orphan*/  ProxyPassword; void* ProxyPort; void* ProxyType; } ;
struct TYPE_18__ {char* HttpUserAgent; } ;
typedef  TYPE_3__ INTERNET_SETTING ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_4__ CM_SETTING ;
typedef  TYPE_5__ CLIENT ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  Alert (char*,int /*<<< orphan*/ *) ; 
 char* CLIENT_MACOS_TAP_NAME ; 
 int /*<<< orphan*/  CLog (TYPE_5__*,char*) ; 
 void* CfgGetBool (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * CfgGetBuf (int /*<<< orphan*/ *,char*) ; 
 int CfgGetByte (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * CfgGetFolder (int /*<<< orphan*/ *,char*) ; 
 void* CfgGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CfgGetInt64 (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ CfgGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 int /*<<< orphan*/  CiLoadAccountDatabase (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiLoadCAList (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiLoadClientConfig (TYPE_12__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CiLoadVLanList (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,TYPE_3__*,int) ; 
 char* CopyStr (char*) ; 
 char* DecryptPassword (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (char*) ; 
 int /*<<< orphan*/  FreeBuf (int /*<<< orphan*/ *) ; 
 TYPE_8__* GetOsInfo () ; 
 int IsEmptyStr (char*) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  NewEraser (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ OSTYPE_MACOS_X ; 
 scalar_t__ OS_IS_UNIX (scalar_t__) ; 
 scalar_t__ OS_IS_WINDOWS_NT (scalar_t__) ; 
 int SHA1_SIZE ; 
 int /*<<< orphan*/  Sha0 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int UnixVLanCreate (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Zero (TYPE_3__*,int) ; 
 TYPE_2__* ZeroMalloc (int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 

bool CiReadSettingFromCfg(CLIENT *c, FOLDER *root)
{
	FOLDER *config;
	FOLDER *cert;
	FOLDER *db;
	FOLDER *vlan;
	FOLDER *cmsetting;
	FOLDER *proxy;
	char user_agent[MAX_SIZE];
	// Validate arguments
	if (c == NULL || root == NULL)
	{
		return false;
	}

	// Initialize the setting if there isn't either of AccountDatabase and Config
	config = CfgGetFolder(root, "Config");
	if (config == NULL)
	{
		return false;
	}

	db = CfgGetFolder(root, "AccountDatabase");
	if (db == NULL)
	{
		return false;
	}

	cmsetting = CfgGetFolder(root, "ClientManagerSetting");

	CiLoadClientConfig(&c->Config, config);


	proxy = CfgGetFolder(root, "CommonProxySetting");

	if (proxy != NULL)
	{
		INTERNET_SETTING t;
		BUF *pw;

		// Proxy Setting
		Zero(&t, sizeof(t));
		t.ProxyType = CfgGetInt(proxy, "ProxyType");
		CfgGetStr(proxy, "ProxyHostName", t.ProxyHostName, sizeof(t.ProxyHostName));
		t.ProxyPort = CfgGetInt(proxy, "ProxyPort");
		CfgGetStr(proxy, "ProxyUsername", t.ProxyUsername, sizeof(t.ProxyUsername));
		pw = CfgGetBuf(proxy, "ProxyPassword");
		if (pw != NULL)
		{
			char *pw_str = DecryptPassword(pw);
			StrCpy(t.ProxyPassword, sizeof(t.ProxyPassword), pw_str);

			Free(pw_str);
			FreeBuf(pw);
		}

		CfgGetStr(proxy, "CustomHttpHeader", t.CustomHttpHeader, sizeof(t.CustomHttpHeader));

		Copy(&c->CommonProxySetting, &t, sizeof(INTERNET_SETTING));
	}

	// Eraser
	c->Eraser = NewEraser(c->Logger, CfgGetInt64(config, "AutoDeleteCheckDiskFreeSpaceMin"));

	if (OS_IS_UNIX(GetOsInfo()->OsType)
#ifdef	NO_VLAN
	    && GetOsInfo()->OsType != OSTYPE_MACOS_X
#endif	// NO_VLAN
	    )
	{
		// Read the UNIX version virtual LAN card list (except MacOS)
		vlan = CfgGetFolder(root, "UnixVLan");
		if (vlan != NULL)
		{
			CiLoadVLanList(c, vlan);
		}
	}

#ifdef	NO_VLAN
	if (GetOsInfo()->OsType == OSTYPE_MACOS_X)
	{
#ifdef	OS_UNIX
		UNIX_VLAN *uv;

		// Create a Tap for MacOS X
		if (UnixVLanCreate(CLIENT_MACOS_TAP_NAME, NULL, !c->Config.NicDownOnDisconnect) == false)
		{
			// Fail (abort)
			CLog(c, "LC_TAP_NOT_FOUND");
			Alert("tun/tap driver not found.", NULL);
			exit(0);
		}

		uv = ZeroMalloc(sizeof(UNIX_VLAN));
		uv->Enabled = true;
		StrCpy(uv->Name, sizeof(uv->Name), CLIENT_MACOS_TAP_NAME);
		Add(c->UnixVLanList, uv);
#endif	// OS_UNIX
	}
#endif	// NO_VLAN
	CiLoadAccountDatabase(c, db);

	if (CfgGetByte(root, "EncryptedPassword", c->EncryptedPassword, SHA1_SIZE) == false)
	{
		Sha0(c->EncryptedPassword, "", 0);
	}

	c->PasswordRemoteOnly = CfgGetBool(root, "PasswordRemoteOnly");
	c->UseSecureDeviceId = CfgGetInt(root, "UseSecureDeviceId");

	if (CfgGetStr(root, "UserAgent", user_agent, sizeof(user_agent)))
	{
		if (IsEmptyStr(user_agent) == false)
		{
			Free(c->Cedar->HttpUserAgent);
			c->Cedar->HttpUserAgent = CopyStr(user_agent);
		}
	}

	cert = CfgGetFolder(root, "RootCA");
	if (cert != NULL)
	{
		CiLoadCAList(c, cert);
	}

	c->DontSavePassword = CfgGetBool(root, "DontSavePassword");

	if (cmsetting != NULL)
	{
		UINT ostype = GetOsInfo()->OsType;
		// CM_SETTING
		CM_SETTING *s = c->CmSetting;

		if (OS_IS_UNIX(ostype) || OS_IS_WINDOWS_NT(ostype))
		{
			s->EasyMode = CfgGetBool(cmsetting, "EasyMode");
		}

		s->LockMode = CfgGetBool(cmsetting, "LockMode");
		CfgGetByte(cmsetting, "HashedPassword", s->HashedPassword, sizeof(s->HashedPassword));
	}

	return true;
}