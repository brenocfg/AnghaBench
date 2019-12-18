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
struct TYPE_3__ {int /*<<< orphan*/  KeepConnectHost; int /*<<< orphan*/  NicDownOnDisconnect; int /*<<< orphan*/  AllowRemoteConfig; int /*<<< orphan*/  KeepConnectInterval; int /*<<< orphan*/  KeepConnectProtocol; int /*<<< orphan*/  KeepConnectPort; int /*<<< orphan*/  UseKeepConnect; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ CLIENT_CONFIG ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcClientConfig(PACK *p, CLIENT_CONFIG *c)
{
	// Validate arguments
	if (c == NULL || p == NULL)
	{
		return;
	}

	PackAddInt(p, "UseKeepConnect", c->UseKeepConnect);
	PackAddInt(p, "KeepConnectPort", c->KeepConnectPort);
	PackAddInt(p, "KeepConnectProtocol", c->KeepConnectProtocol);
	PackAddInt(p, "KeepConnectInterval", c->KeepConnectInterval);
	PackAddInt(p, "AllowRemoteConfig", c->AllowRemoteConfig);
	PackAddBool(p, "NicDownOnDisconnect", c->NicDownOnDisconnect);
	PackAddStr(p, "KeepConnectHost", c->KeepConnectHost);
}