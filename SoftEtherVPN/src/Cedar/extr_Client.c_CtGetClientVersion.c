#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  OsType; } ;
struct TYPE_10__ {TYPE_1__* Cedar; } ;
struct TYPE_9__ {int /*<<< orphan*/  OsType; int /*<<< orphan*/  IsVLanNameRegulated; int /*<<< orphan*/  ProcessId; int /*<<< orphan*/  ClientBuildInt; int /*<<< orphan*/  ClientVerInt; int /*<<< orphan*/  ClientBuildInfoString; int /*<<< orphan*/  ClientVersionString; int /*<<< orphan*/  ClientProductName; } ;
struct TYPE_8__ {int /*<<< orphan*/  Build; int /*<<< orphan*/  Version; int /*<<< orphan*/  BuildInfo; int /*<<< orphan*/  VerString; } ;
typedef  TYPE_2__ RPC_CLIENT_VERSION ;
typedef  TYPE_3__ CLIENT ;

/* Variables and functions */
 int /*<<< orphan*/  CEDAR_CLIENT_STR ; 
 TYPE_5__* GetOsInfo () ; 
 int /*<<< orphan*/  MsGetProcessId () ; 
 int /*<<< orphan*/  MsIsInfCatalogRequired () ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

bool CtGetClientVersion(CLIENT *c, RPC_CLIENT_VERSION *ver)
{
	// Validate arguments
	if (ver == NULL)
	{
		return false;
	}

	Zero(ver, sizeof(RPC_CLIENT_VERSION));
	StrCpy(ver->ClientProductName, sizeof(ver->ClientProductName), CEDAR_CLIENT_STR);
	StrCpy(ver->ClientVersionString, sizeof(ver->ClientVersionString), c->Cedar->VerString);
	StrCpy(ver->ClientBuildInfoString, sizeof(ver->ClientBuildInfoString), c->Cedar->BuildInfo);
	ver->ClientVerInt = c->Cedar->Version;
	ver->ClientBuildInt = c->Cedar->Build;


#ifdef	OS_WIN32
	ver->ProcessId = MsGetProcessId();
	ver->IsVLanNameRegulated = MsIsInfCatalogRequired();

#endif	// OS_WIN32

	ver->OsType = GetOsInfo()->OsType;

	return true;
}