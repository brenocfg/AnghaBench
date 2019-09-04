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
struct TYPE_3__ {void* NicDownOnDisconnect; void* NoChangeWcmNetworkSettingOnWindows8; int /*<<< orphan*/  KeepConnectInterval; void* AllowRemoteConfig; void* KeepConnectProtocol; void* KeepConnectPort; int /*<<< orphan*/  KeepConnectHost; void* UseKeepConnect; } ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_1__ CLIENT_CONFIG ;

/* Variables and functions */
 void* CfgGetBool (int /*<<< orphan*/ *,char*) ; 
 void* CfgGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CfgGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KEEP_INTERVAL_MAX ; 
 int /*<<< orphan*/  KEEP_INTERVAL_MIN ; 
 int /*<<< orphan*/  MAKESURE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void CiLoadClientConfig(CLIENT_CONFIG *c, FOLDER *f)
{
	// Validate arguments
	if (c == NULL || f == NULL)
	{
		return;
	}

	c->UseKeepConnect = CfgGetBool(f, "UseKeepConnect");
	CfgGetStr(f, "KeepConnectHost", c->KeepConnectHost, sizeof(c->KeepConnectHost));
	c->KeepConnectPort = CfgGetInt(f, "KeepConnectPort");
	c->KeepConnectProtocol = CfgGetInt(f, "KeepConnectProtocol");
	c->AllowRemoteConfig = CfgGetBool(f, "AllowRemoteConfig");
	c->KeepConnectInterval = MAKESURE(CfgGetInt(f, "KeepConnectInterval"), KEEP_INTERVAL_MIN, KEEP_INTERVAL_MAX);
	c->NoChangeWcmNetworkSettingOnWindows8 = CfgGetBool(f, "NoChangeWcmNetworkSettingOnWindows8");
	c->NicDownOnDisconnect = CfgGetBool(f, "NicDownOnDisconnect");
}