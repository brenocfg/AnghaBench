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
struct TYPE_4__ {int /*<<< orphan*/  OsInfo; int /*<<< orphan*/  ServerFamilyName; int /*<<< orphan*/  ServerBuildDate; void* ServerType; int /*<<< orphan*/  ServerHostName; void* ServerBuildInt; void* ServerVerInt; int /*<<< orphan*/  ServerBuildInfoString; int /*<<< orphan*/  ServerVersionString; int /*<<< orphan*/  ServerProductName; } ;
typedef  TYPE_1__ RPC_SERVER_INFO ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  InRpcOsInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetInt64 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcServerInfo(RPC_SERVER_INFO *t, PACK *p)
{
	// Validate arguments
	if (t == NULL || p == NULL)
	{
		return;
	}

	Zero(t, sizeof(RPC_SERVER_INFO));

	PackGetStr(p, "ServerProductName", t->ServerProductName, sizeof(t->ServerProductName));
	PackGetStr(p, "ServerVersionString", t->ServerVersionString, sizeof(t->ServerVersionString));
	PackGetStr(p, "ServerBuildInfoString", t->ServerBuildInfoString, sizeof(t->ServerBuildInfoString));
	t->ServerVerInt = PackGetInt(p, "ServerVerInt");
	t->ServerBuildInt = PackGetInt(p, "ServerBuildInt");
	PackGetStr(p, "ServerHostName", t->ServerHostName, sizeof(t->ServerHostName));
	t->ServerType = PackGetInt(p, "ServerType");
	t->ServerBuildDate = PackGetInt64(p, "ServerBuildDate");
	PackGetStr(p, "ServerFamilyName", t->ServerFamilyName, sizeof(t->ServerFamilyName));
	InRpcOsInfo(&t->OsInfo, p);
}