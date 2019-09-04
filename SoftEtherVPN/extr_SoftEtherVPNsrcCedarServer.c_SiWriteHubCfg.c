#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ RadiusServerPort; scalar_t__ RadiusRetryInterval; int RadiusConvertAllMsChapv2AuthRequestToEap; int RadiusUsePeapInsteadOfEap; int HubIsOnlineButHalting; scalar_t__ Type; scalar_t__ NumLogin; int /*<<< orphan*/  CreatedTime; int /*<<< orphan*/  LastLoginTime; int /*<<< orphan*/  LastCommTime; int /*<<< orphan*/  HubDb; TYPE_1__* Cedar; int /*<<< orphan*/  LogSetting; int /*<<< orphan*/  Msg; int /*<<< orphan*/  Option; int /*<<< orphan*/  Traffic; scalar_t__ Offline; int /*<<< orphan*/  SecurePassword; int /*<<< orphan*/  HashedPassword; int /*<<< orphan*/  RadiusOptionLock; int /*<<< orphan*/ * RadiusRealm; int /*<<< orphan*/ * RadiusSuffixFilter; int /*<<< orphan*/  RadiusSecret; int /*<<< orphan*/ * RadiusServerName; } ;
struct TYPE_8__ {int Bridge; int /*<<< orphan*/  Server; } ;
typedef  TYPE_2__ HUB ;
typedef  int /*<<< orphan*/  FOLDER ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddBool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  CfgAddBuf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddByte (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CfgAddInt (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  CfgAddInt64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CfgAddUniStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CfgCreateFolder (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ GetServerCapsBool (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ HUB_TYPE_FARM_STATIC ; 
 scalar_t__ HUB_TYPE_STANDALONE ; 
 int IsEmptyUniStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiWriteHubAccessLists (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  SiWriteHubAdminOptions (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  SiWriteHubDb (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SiWriteHubLinks (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  SiWriteHubLogCfg (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiWriteHubOptionCfg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SiWriteSecureNAT (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SiWriteTraffic (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

void SiWriteHubCfg(FOLDER *f, HUB *h)
{
	// Validate arguments
	if (f == NULL || h == NULL)
	{
		return;
	}

	// Radius server name
	Lock(h->RadiusOptionLock);
	{
		if (h->RadiusServerName != NULL)
		{
			CfgAddStr(f, "RadiusServerName", h->RadiusServerName);
			CfgAddBuf(f, "RadiusSecret", h->RadiusSecret);
		}
		CfgAddInt(f, "RadiusServerPort", h->RadiusServerPort);
		CfgAddInt(f, "RadiusRetryInterval", h->RadiusRetryInterval);
		CfgAddStr(f, "RadiusSuffixFilter", h->RadiusSuffixFilter);
		CfgAddStr(f, "RadiusRealm", h->RadiusRealm);

		CfgAddBool(f, "RadiusConvertAllMsChapv2AuthRequestToEap", h->RadiusConvertAllMsChapv2AuthRequestToEap);
		CfgAddBool(f, "RadiusUsePeapInsteadOfEap", h->RadiusUsePeapInsteadOfEap);
	}
	Unlock(h->RadiusOptionLock);

	// Password
	CfgAddByte(f, "HashedPassword", h->HashedPassword, sizeof(h->HashedPassword));
	CfgAddByte(f, "SecurePassword", h->SecurePassword, sizeof(h->SecurePassword));

	// Online / Offline flag
	if (h->Cedar->Bridge == false)
	{
		CfgAddBool(f, "Online", (h->Offline && (h->HubIsOnlineButHalting == false)) ? false : true);
	}

	// Traffic information
	SiWriteTraffic(f, "Traffic", h->Traffic);

	// HUB options
	SiWriteHubOptionCfg(CfgCreateFolder(f, "Option"), h->Option);

	// Message
	{
		FOLDER *folder = CfgCreateFolder(f, "Message");

		if (IsEmptyUniStr(h->Msg) == false)
		{
			CfgAddUniStr(folder, "MessageText", h->Msg);
		}
	}

	// HUB_LOG
	SiWriteHubLogCfg(CfgCreateFolder(f, "LogSetting"), &h->LogSetting);

	if (h->Type == HUB_TYPE_STANDALONE)
	{
		// Link list
		SiWriteHubLinks(CfgCreateFolder(f, "CascadeList"), h);
	}

	if (h->Type != HUB_TYPE_FARM_STATIC)
	{
		if (GetServerCapsBool(h->Cedar->Server, "b_support_securenat"))
		{
			// SecureNAT
			SiWriteSecureNAT(h, CfgCreateFolder(f, "SecureNAT"));
		}
	}

	// Access list
	SiWriteHubAccessLists(CfgCreateFolder(f, "AccessList"), h);

	// Administration options
	SiWriteHubAdminOptions(CfgCreateFolder(f, "AdminOption"), h);

	// Type of HUB
	CfgAddInt(f, "Type", h->Type);

	// Database
	if (h->Cedar->Bridge == false)
	{
		SiWriteHubDb(CfgCreateFolder(f, "SecurityAccountDatabase"), h->HubDb,
			false
			);
	}

	// Usage status
	CfgAddInt64(f, "LastCommTime", h->LastCommTime);
	CfgAddInt64(f, "LastLoginTime", h->LastLoginTime);
	CfgAddInt64(f, "CreatedTime", h->CreatedTime);
	CfgAddInt(f, "NumLogin", h->NumLogin);
}