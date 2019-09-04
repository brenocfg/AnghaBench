#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;
typedef  struct TYPE_22__   TYPE_18__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  secret_str ;
typedef  int /*<<< orphan*/  o ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  g ;
typedef  scalar_t__ UINT ;
struct TYPE_26__ {int Size; int /*<<< orphan*/  Buf; } ;
struct TYPE_25__ {char* RadiusSuffixFilter; char* RadiusRealm; scalar_t__ Type; int CurrentVersion; int LastVersion; scalar_t__ LastCommTime; scalar_t__ LastLoginTime; int Offline; int /*<<< orphan*/  PacketLogger; int /*<<< orphan*/  SecurityLogger; void* NumLogin; void* CreatedTime; TYPE_1__* Cedar; int /*<<< orphan*/  SecureNATOption; int /*<<< orphan*/  Traffic; int /*<<< orphan*/  SecurePassword; int /*<<< orphan*/  HashedPassword; int /*<<< orphan*/  RadiusOptionLock; void* RadiusUsePeapInsteadOfEap; void* RadiusConvertAllMsChapv2AuthRequestToEap; } ;
struct TYPE_24__ {scalar_t__ ServerType; int /*<<< orphan*/ * Cedar; } ;
struct TYPE_23__ {int Bridge; TYPE_18__* Server; } ;
struct TYPE_22__ {scalar_t__ ServerType; } ;
typedef  TYPE_2__ SERVER ;
typedef  char HUB_OPTION ;
typedef  char HUB_LOG ;
typedef  TYPE_3__ HUB ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_4__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  ADMINISTRATOR_USERNAME ; 
 int /*<<< orphan*/  AddHub (int /*<<< orphan*/ *,TYPE_3__*) ; 
 void* CfgGetBool (int /*<<< orphan*/ *,char*) ; 
 TYPE_4__* CfgGetBuf (int /*<<< orphan*/ *,char*) ; 
 int CfgGetByte (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * CfgGetFolder (int /*<<< orphan*/ *,char*) ; 
 void* CfgGetInt (int /*<<< orphan*/ *,char*) ; 
 void* CfgGetInt64 (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ CfgGetStr (int /*<<< orphan*/ *,char*,char*,int) ; 
 scalar_t__ CfgGetUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  Copy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FreeBuf (TYPE_4__*) ; 
 scalar_t__ GetServerCapsBool (TYPE_18__*,char*) ; 
 int HUB_MAXMSG_LEN ; 
 scalar_t__ HUB_TYPE_FARM_DYNAMIC ; 
 scalar_t__ HUB_TYPE_STANDALONE ; 
 int /*<<< orphan*/  HashPassword (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/ * Malloc (int) ; 
 TYPE_3__* NewHub (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  NiClearUnsupportedVhOptionForDynamicHub (int /*<<< orphan*/ ,int) ; 
 scalar_t__ RADIUS_RETRY_INTERVAL ; 
 int /*<<< orphan*/  ReleaseHub (TYPE_3__*) ; 
 scalar_t__ SERVER_TYPE_FARM_CONTROLLER ; 
 scalar_t__ SERVER_TYPE_STANDALONE ; 
 int /*<<< orphan*/  SetHubLogSetting (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  SetHubMsg (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetHubOffline (TYPE_3__*) ; 
 int /*<<< orphan*/  SetHubOnline (TYPE_3__*) ; 
 int /*<<< orphan*/  SetRadiusServerEx (TYPE_3__*,char*,scalar_t__,char*,scalar_t__) ; 
 int /*<<< orphan*/  Sha0 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiLoadHubAccessLists (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiLoadHubAdminOptions (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiLoadHubDb (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiLoadHubLinks (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiLoadHubLogCfg (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiLoadHubOptionCfg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SiLoadSecureNAT (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiLoadTraffic (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 void* SystemTime64 () ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WaitLogFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (char*,int) ; 

void SiLoadHubCfg(SERVER *s, FOLDER *f, char *name)
{
	HUB *h;
	CEDAR *c;
	HUB_OPTION o;
	bool online;
	UINT hub_old_type = 0;
	// Validate arguments
	if (s == NULL || f == NULL || name == NULL)
	{
		return;
	}

	c = s->Cedar;

	// Get the option
	Zero(&o, sizeof(o));
	SiLoadHubOptionCfg(CfgGetFolder(f, "Option"), &o);

	// Create a HUB
	h = NewHub(c, name, &o);
	if (h != NULL)
	{
		HUB_LOG g;
		// Radius server settings
		Lock(h->RadiusOptionLock);
		{
			char name[MAX_SIZE];
			BUF *secret;
			UINT port;
			UINT interval;

			port = CfgGetInt(f, "RadiusServerPort");
			interval = CfgGetInt(f, "RadiusRetryInterval");

			CfgGetStr(f, "RadiusSuffixFilter", h->RadiusSuffixFilter, sizeof(h->RadiusSuffixFilter));
			CfgGetStr(f, "RadiusRealm", h->RadiusRealm, sizeof(h->RadiusRealm));

			h->RadiusConvertAllMsChapv2AuthRequestToEap = CfgGetBool(f, "RadiusConvertAllMsChapv2AuthRequestToEap");
			h->RadiusUsePeapInsteadOfEap = CfgGetBool(f, "RadiusUsePeapInsteadOfEap");

			if (interval == 0)
			{
				interval = RADIUS_RETRY_INTERVAL;
			}

			if (port != 0 && CfgGetStr(f, "RadiusServerName", name, sizeof(name)))
			{
				secret = CfgGetBuf(f, "RadiusSecret");
				if (secret != NULL)
				{
					char secret_str[MAX_SIZE];
					Zero(secret_str, sizeof(secret_str));
					if (secret->Size < sizeof(secret_str))
					{
						Copy(secret_str, secret->Buf, secret->Size);
					}
					secret_str[sizeof(secret_str) - 1] = 0;
					//SetRadiusServer(h, name, port, secret_str);
					SetRadiusServerEx(h, name, port, secret_str, interval);
					FreeBuf(secret);
				}
			}
		}
		Unlock(h->RadiusOptionLock);

		// Password
		if (CfgGetByte(f, "HashedPassword", h->HashedPassword, sizeof(h->HashedPassword)) != sizeof(h->HashedPassword))
		{
			Sha0(h->HashedPassword, "", 0);
		}
		if (CfgGetByte(f, "SecurePassword", h->SecurePassword, sizeof(h->SecurePassword)) != sizeof(h->SecurePassword))
		{
			HashPassword(h->SecurePassword, ADMINISTRATOR_USERNAME, "");
		}

		// Log Settings
		Zero(&g, sizeof(g));
		SiLoadHubLogCfg(&g, CfgGetFolder(f, "LogSetting"));
		SetHubLogSetting(h, &g);

		// Online / Offline flag
		if (h->Cedar->Bridge == false)
		{
			online = CfgGetBool(f, "Online");
		}
		else
		{
			online = true;
		}

		// Traffic information
		SiLoadTraffic(f, "Traffic", h->Traffic);

		// Access list
		SiLoadHubAccessLists(h, CfgGetFolder(f, "AccessList"));

		// Type of HUB
		hub_old_type = h->Type = CfgGetInt(f, "Type");

		if (s->ServerType == SERVER_TYPE_STANDALONE)
		{
			if (h->Type != HUB_TYPE_STANDALONE)
			{
				// Change the type of all HUB to a stand-alone if the server is a stand-alone
				h->Type = HUB_TYPE_STANDALONE;
			}
		}
		else
		{
			if (h->Type == HUB_TYPE_STANDALONE)
			{
				// If the server is a farm controller, change the type of HUB to the farm supported types
				h->Type = HUB_TYPE_FARM_DYNAMIC;
			}
		}

		if (h->Type == HUB_TYPE_FARM_DYNAMIC)
		{
			h->CurrentVersion = h->LastVersion = 1;
		}

		// Message
		{
			FOLDER *folder = CfgGetFolder(f, "Message");
			if (folder != NULL)
			{
				wchar_t *tmp = Malloc(sizeof(wchar_t) * (HUB_MAXMSG_LEN + 1));
				if (CfgGetUniStr(folder, "MessageText", tmp, sizeof(wchar_t) * (HUB_MAXMSG_LEN + 1)))
				{
					SetHubMsg(h, tmp);
				}
				Free(tmp);
			}
		}

		// Link list
		if (h->Type == HUB_TYPE_STANDALONE)
		{
			// The link list is used only on stand-alone HUB
			// In VPN Gate hubs, don't load this
			{
				SiLoadHubLinks(h, CfgGetFolder(f, "CascadeList"));
			}
		}

		// SecureNAT
		if (GetServerCapsBool(h->Cedar->Server, "b_support_securenat"))
		{
			if (h->Type == HUB_TYPE_STANDALONE || h->Type == HUB_TYPE_FARM_DYNAMIC)
			{
				// SecureNAT is used only in the case of dynamic HUB or standalone HUB
				SiLoadSecureNAT(h, CfgGetFolder(f, "SecureNAT"));

				if (h->Type != HUB_TYPE_STANDALONE && h->Cedar != NULL && h->Cedar->Server != NULL &&
					h->Cedar->Server->ServerType == SERVER_TYPE_FARM_CONTROLLER)
				{
					NiClearUnsupportedVhOptionForDynamicHub(h->SecureNATOption,
						hub_old_type == HUB_TYPE_STANDALONE);
				}

			}
		}

		// Administration options
		SiLoadHubAdminOptions(h, CfgGetFolder(f, "AdminOption"));

		// Database
		if (h->Cedar->Bridge == false)
		{
			SiLoadHubDb(h, CfgGetFolder(f, "SecurityAccountDatabase"));
		}

		// Usage status
		h->LastCommTime = CfgGetInt64(f, "LastCommTime");
		if (h->LastCommTime == 0)
		{
			h->LastCommTime = SystemTime64();
		}
		h->LastLoginTime = CfgGetInt64(f, "LastLoginTime");
		if (h->LastLoginTime == 0)
		{
			h->LastLoginTime = SystemTime64();
		}
		h->CreatedTime = CfgGetInt64(f, "CreatedTime");
		h->NumLogin = CfgGetInt(f, "NumLogin");

		// Start the operation of the HUB
		AddHub(c, h);

		if (online)
		{
			h->Offline = true;
			SetHubOnline(h);
		}
		else
		{
			h->Offline = false;
			SetHubOffline(h);
		}

		WaitLogFlush(h->SecurityLogger);
		WaitLogFlush(h->PacketLogger);

		ReleaseHub(h);
	}
}