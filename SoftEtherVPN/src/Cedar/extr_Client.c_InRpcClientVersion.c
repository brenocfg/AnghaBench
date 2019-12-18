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
struct TYPE_4__ {int /*<<< orphan*/  ClientId; void* ShowVgcLink; void* IsVgcSupported; void* IsVLanNameRegulated; void* OsType; void* ProcessId; void* ClientBuildInt; void* ClientVerInt; int /*<<< orphan*/  ClientBuildInfoString; int /*<<< orphan*/  ClientVersionString; int /*<<< orphan*/  ClientProductName; } ;
typedef  TYPE_1__ RPC_CLIENT_VERSION ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 void* PackGetBool (int /*<<< orphan*/ *,char*) ; 
 void* PackGetInt (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  PackGetStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Zero (TYPE_1__*,int) ; 

void InRpcClientVersion(RPC_CLIENT_VERSION *ver, PACK *p)
{
	// Validate arguments
	if (ver == NULL || p == NULL)
	{
		return;
	}

	Zero(ver, sizeof(RPC_CLIENT_VERSION));
	PackGetStr(p, "ClientProductName", ver->ClientProductName, sizeof(ver->ClientProductName));
	PackGetStr(p, "ClientVersionString", ver->ClientVersionString, sizeof(ver->ClientVersionString));
	PackGetStr(p, "ClientBuildInfoString", ver->ClientBuildInfoString, sizeof(ver->ClientBuildInfoString));
	ver->ClientVerInt = PackGetInt(p, "ClientVerInt");
	ver->ClientBuildInt = PackGetInt(p, "ClientBuildInt");
	ver->ProcessId = PackGetInt(p, "ProcessId");
	ver->OsType = PackGetInt(p, "OsType");
	ver->IsVLanNameRegulated = PackGetBool(p, "IsVLanNameRegulated");
	ver->IsVgcSupported = PackGetBool(p, "IsVgcSupported");
	ver->ShowVgcLink = PackGetBool(p, "ShowVgcLink");
	PackGetStr(p, "ClientId", ver->ClientId, sizeof(ver->ClientId));
}