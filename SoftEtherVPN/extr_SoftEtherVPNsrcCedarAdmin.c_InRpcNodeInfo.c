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
struct TYPE_4__ {void* ProxyPort; int /*<<< orphan*/  ProxyIpAddress6; void* ProxyIpAddress; void* ServerPort; int /*<<< orphan*/  ServerIpAddress6; void* ServerIpAddress; void* ClientPort; int /*<<< orphan*/  ClientIpAddress6; void* ClientIpAddress; void* ServerProductBuild; void* ServerProductVer; void* ClientProductBuild; void* ClientProductVer; int /*<<< orphan*/  UniqueId; int /*<<< orphan*/  HubName; int /*<<< orphan*/  ProxyHostname; int /*<<< orphan*/  ServerHostname; int /*<<< orphan*/  ClientHostname; int /*<<< orphan*/  ClientOsProductId; int /*<<< orphan*/  ClientOsVer; int /*<<< orphan*/  ClientOsName; int /*<<< orphan*/  ServerProductName; int /*<<< orphan*/  ClientProductName; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ NODE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  PackGetData2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 void* PackGetIp32 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcNodeInfo(NODE_INFO *t, PACK *p)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(NODE_INFO));
	PackGetStr(p, "ClientProductName", t->ClientProductName, sizeof(t->ClientProductName));
	PackGetStr(p, "ServerProductName", t->ServerProductName, sizeof(t->ServerProductName));
	PackGetStr(p, "ClientOsName", t->ClientOsName, sizeof(t->ClientOsName));
	PackGetStr(p, "ClientOsVer", t->ClientOsVer, sizeof(t->ClientOsVer));
	PackGetStr(p, "ClientOsProductId", t->ClientOsProductId, sizeof(t->ClientOsProductId));
	PackGetStr(p, "ClientHostname", t->ClientHostname, sizeof(t->ClientHostname));
	PackGetStr(p, "ServerHostname", t->ServerHostname, sizeof(t->ServerHostname));
	PackGetStr(p, "ProxyHostname", t->ProxyHostname, sizeof(t->ProxyHostname));
	PackGetStr(p, "HubName", t->HubName, sizeof(t->HubName));
	PackGetData2(p, "UniqueId", t->UniqueId, sizeof(t->UniqueId));

	t->ClientProductVer = PackGetInt(p, "ClientProductVer");
	t->ClientProductBuild = PackGetInt(p, "ClientProductBuild");
	t->ServerProductVer = PackGetInt(p, "ServerProductVer");
	t->ServerProductBuild = PackGetInt(p, "ServerProductBuild");
	t->ClientIpAddress = PackGetIp32(p, "ClientIpAddress");
	PackGetData2(p, "ClientIpAddress6", t->ClientIpAddress6, sizeof(t->ClientIpAddress6));
	t->ClientPort = PackGetInt(p, "ClientPort");
	t->ServerIpAddress = PackGetIp32(p, "ServerIpAddress");
	PackGetData2(p, "ServerIpAddress6", t->ServerIpAddress6, sizeof(t->ServerIpAddress6));
	t->ServerPort = PackGetInt(p, "ServerPort2");
	t->ProxyIpAddress = PackGetIp32(p, "ProxyIpAddress");
	PackGetData2(p, "ProxyIpAddress6", t->ProxyIpAddress6, sizeof(t->ProxyIpAddress6));
	t->ProxyPort = PackGetInt(p, "ProxyPort");
}