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
struct TYPE_3__ {int /*<<< orphan*/  OsInfo; int /*<<< orphan*/  ServerFamilyName; int /*<<< orphan*/  ServerBuildDate; int /*<<< orphan*/  ServerType; int /*<<< orphan*/  ServerHostName; int /*<<< orphan*/  ServerBuildInt; int /*<<< orphan*/  ServerVerInt; int /*<<< orphan*/  ServerBuildInfoString; int /*<<< orphan*/  ServerVersionString; int /*<<< orphan*/  ServerProductName; } ;
typedef  TYPE_1__ RPC_SERVER_INFO ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  OutRpcOsInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddTime64 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcServerInfo(PACK *p, RPC_SERVER_INFO *t)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	PackAddStr(p, "ServerProductName", t->ServerProductName);
	PackAddStr(p, "ServerVersionString", t->ServerVersionString);
	PackAddStr(p, "ServerBuildInfoString", t->ServerBuildInfoString);
	PackAddInt(p, "ServerVerInt", t->ServerVerInt);
	PackAddInt(p, "ServerBuildInt", t->ServerBuildInt);
	PackAddStr(p, "ServerHostName", t->ServerHostName);
	PackAddInt(p, "ServerType", t->ServerType);
	PackAddTime64(p, "ServerBuildDate", t->ServerBuildDate);
	PackAddStr(p, "ServerFamilyName", t->ServerFamilyName);
	OutRpcOsInfo(p, &t->OsInfo);
}