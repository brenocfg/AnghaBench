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
struct TYPE_3__ {int /*<<< orphan*/  ClientId; int /*<<< orphan*/  ShowVgcLink; int /*<<< orphan*/  IsVgcSupported; int /*<<< orphan*/  IsVLanNameRegulated; int /*<<< orphan*/  OsType; int /*<<< orphan*/  ProcessId; int /*<<< orphan*/  ClientBuildInt; int /*<<< orphan*/  ClientVerInt; int /*<<< orphan*/  ClientBuildInfoString; int /*<<< orphan*/  ClientVersionString; int /*<<< orphan*/  ClientProductName; } ;
typedef  TYPE_1__ RPC_CLIENT_VERSION ;
typedef  int /*<<< orphan*/  PACK ;

/* Variables and functions */
 int /*<<< orphan*/  PackAddBool (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddInt (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PackAddStr (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void OutRpcClientVersion(PACK *p, RPC_CLIENT_VERSION *ver)
{
	// Validate arguments
	if (ver == NULL || p == NULL)
	{
		return;
	}

	PackAddStr(p, "ClientProductName", ver->ClientProductName);
	PackAddStr(p, "ClientVersionString", ver->ClientVersionString);
	PackAddStr(p, "ClientBuildInfoString", ver->ClientBuildInfoString);
	PackAddInt(p, "ClientVerInt", ver->ClientVerInt);
	PackAddInt(p, "ClientBuildInt", ver->ClientBuildInt);
	PackAddInt(p, "ProcessId", ver->ProcessId);
	PackAddInt(p, "OsType", ver->OsType);
	PackAddBool(p, "IsVLanNameRegulated", ver->IsVLanNameRegulated);
	PackAddBool(p, "IsVgcSupported", ver->IsVgcSupported);
	PackAddBool(p, "ShowVgcLink", ver->ShowVgcLink);
	PackAddStr(p, "ClientId", ver->ClientId);
}