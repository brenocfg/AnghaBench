#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tmp ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {int /*<<< orphan*/  Cedar; } ;
struct TYPE_8__ {TYPE_5__* Server; } ;
struct TYPE_7__ {int /*<<< orphan*/  TapMode; int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_LOCALBRIDGE ;
typedef  TYPE_2__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_2__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AddLocalBridge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ERR_INVALID_PARAMETER ; 
 scalar_t__ ERR_LOCAL_BRIDGE_UNSUPPORTED ; 
 scalar_t__ ERR_NO_ERROR ; 
 scalar_t__ ERR_OBJECT_NOT_FOUND ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_5__*) ; 
 scalar_t__ IsEmptyStr (int /*<<< orphan*/ ) ; 
 int IsEthSupported () ; 
 int MAX_SIZE ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 
 scalar_t__ Win32EthGetNameAndIdFromCombinedName (char*,int,int /*<<< orphan*/ ) ; 

UINT StAddLocalBridge(ADMIN *a, RPC_LOCALBRIDGE *t)
{
	if (IsEmptyStr(t->DeviceName) || IsEmptyStr(t->HubName))
	{
		return ERR_INVALID_PARAMETER;
	}

	SERVER_ADMIN_ONLY;


	if (IsEthSupported() == false)
	{
		return ERR_LOCAL_BRIDGE_UNSUPPORTED;
	}

#ifdef	OS_WIN32
	if (true)
	{
		char tmp[MAX_SIZE];
		UINT id = Win32EthGetNameAndIdFromCombinedName(tmp, sizeof(tmp), t->DeviceName);

		if (id == 0)
		{
			// If a ID is not specified in Win32, adding will fail
			return ERR_OBJECT_NOT_FOUND;
		}
	}
#endif	// OS_WIN32

	ALog(a, NULL, "LA_ADD_BRIDGE", t->HubName, t->DeviceName);

	AddLocalBridge(a->Server->Cedar, t->HubName, t->DeviceName, false, false, t->TapMode, NULL, false);

	IncrementServerConfigRevision(a->Server);

	return ERR_NO_ERROR;
}