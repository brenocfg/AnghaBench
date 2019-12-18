#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  NicDownOnDisconnect; int /*<<< orphan*/  NoChangeWcmNetworkSettingOnWindows8; int /*<<< orphan*/  KeepConnectInterval; int /*<<< orphan*/  AllowRemoteConfig; int /*<<< orphan*/  KeepConnectProtocol; int /*<<< orphan*/  KeepConnectPort; int /*<<< orphan*/  KeepConnectHost; int /*<<< orphan*/  UseKeepConnect; } ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_1__ CLIENT_CONFIG ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CfgAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void CiWriteClientConfig(FOLDER *cc, CLIENT_CONFIG *config)
{
	// Validate arguments
	if (cc == NULL || config == NULL)
	{
		return;
	}

	CfgAddBool(cc, "UseKeepConnect", config->UseKeepConnect);
	CfgAddStr(cc, "KeepConnectHost", config->KeepConnectHost);
	CfgAddInt(cc, "KeepConnectPort", config->KeepConnectPort);
	CfgAddInt(cc, "KeepConnectProtocol", config->KeepConnectProtocol);
	CfgAddBool(cc, "AllowRemoteConfig", config->AllowRemoteConfig);
	CfgAddInt(cc, "KeepConnectInterval", config->KeepConnectInterval);
	CfgAddBool(cc, "NoChangeWcmNetworkSettingOnWindows8", config->NoChangeWcmNetworkSettingOnWindows8);
	CfgAddBool(cc, "NicDownOnDisconnect", config->NicDownOnDisconnect);
}