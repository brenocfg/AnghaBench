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
struct TYPE_3__ {int /*<<< orphan*/  ProxyPort; int /*<<< orphan*/  ProxyIpAddress6; int /*<<< orphan*/  ProxyIpAddress; int /*<<< orphan*/  ServerPort; int /*<<< orphan*/  ServerIpAddress6; int /*<<< orphan*/  ServerIpAddress; int /*<<< orphan*/  ClientPort; int /*<<< orphan*/  ClientIpAddress6; int /*<<< orphan*/  ClientIpAddress; int /*<<< orphan*/  ServerProductBuild; int /*<<< orphan*/  ServerProductVer; int /*<<< orphan*/  ClientProductBuild; int /*<<< orphan*/  ClientProductVer; int /*<<< orphan*/  UniqueId; int /*<<< orphan*/  HubName; int /*<<< orphan*/  ProxyHostname; int /*<<< orphan*/  ServerHostname; int /*<<< orphan*/  ClientHostname; int /*<<< orphan*/  ClientOsProductId; int /*<<< orphan*/  ClientOsVer; int /*<<< orphan*/  ClientOsName; int /*<<< orphan*/  ServerProductName; int /*<<< orphan*/  ClientProductName; } ;
typedef  int /*<<< orphan*/  PACK ;
typedef  TYPE_1__ NODE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddData (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddIp32 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcNodeInfo(PACK *p, NODE_INFO *t)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddStr(p, "ClientProductName", t->ClientProductName);
	PackAddStr(p, "ServerProductName", t->ServerProductName);
	PackAddStr(p, "ClientOsName", t->ClientOsName);
	PackAddStr(p, "ClientOsVer", t->ClientOsVer);
	PackAddStr(p, "ClientOsProductId", t->ClientOsProductId);
	PackAddStr(p, "ClientHostname", t->ClientHostname);
	PackAddStr(p, "ServerHostname", t->ServerHostname);
	PackAddStr(p, "ProxyHostname", t->ProxyHostname);
	PackAddStr(p, "HubName", t->HubName);
	PackAddData(p, "UniqueId", t->UniqueId, sizeof(t->UniqueId));

	PackAddInt(p, "ClientProductVer", t->ClientProductVer);
	PackAddInt(p, "ClientProductBuild", t->ClientProductBuild);
	PackAddInt(p, "ServerProductVer", t->ServerProductVer);
	PackAddInt(p, "ServerProductBuild", t->ServerProductBuild);
	PackAddIp32(p, "ClientIpAddress", t->ClientIpAddress);
	PackAddData(p, "ClientIpAddress6", t->ClientIpAddress6, sizeof(t->ClientIpAddress6));
	PackAddInt(p, "ClientPort", t->ClientPort);
	PackAddIp32(p, "ServerIpAddress", t->ServerIpAddress);
	PackAddData(p, "ServerIpAddress6", t->ServerIpAddress6, sizeof(t->ServerIpAddress6));
	PackAddInt(p, "ServerPort2", t->ServerPort);
	PackAddIp32(p, "ProxyIpAddress", t->ProxyIpAddress);
	PackAddData(p, "ProxyIpAddress6", t->ProxyIpAddress6, sizeof(t->ProxyIpAddress6));
	PackAddInt(p, "ProxyPort", t->ProxyPort);
}