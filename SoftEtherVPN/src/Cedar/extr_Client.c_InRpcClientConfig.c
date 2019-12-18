#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int UseKeepConnect; int AllowRemoteConfig; int /*<<< orphan*/  KeepConnectHost; int /*<<< orphan*/  NicDownOnDisconnect; scalar_t__ KeepConnectInterval; scalar_t__ KeepConnectProtocol; scalar_t__ KeepConnectPort; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ CLIENT_CONFIG ;

/* Variables and functions */
 int /*<<< orphan*/  PackGetBool (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcClientConfig(CLIENT_CONFIG *c, PACK *p)
{
	// Validate arguments
	if (c == NULL || p == NULL)
	{
		return;
	}

	Zero(c, sizeof(CLIENT_CONFIG));
	c->UseKeepConnect = PackGetInt(p, "UseKeepConnect") == 0 ? false : true;
	c->KeepConnectPort = PackGetInt(p, "KeepConnectPort");
	c->KeepConnectProtocol = PackGetInt(p, "KeepConnectProtocol");
	c->KeepConnectInterval = PackGetInt(p, "KeepConnectInterval");
	c->AllowRemoteConfig = PackGetInt(p, "AllowRemoteConfig") == 0 ? false : true;
	c->NicDownOnDisconnect = PackGetBool(p, "NicDownOnDisconnect");
	PackGetStr(p, "KeepConnectHost", c->KeepConnectHost, sizeof(c->KeepConnectHost));
}