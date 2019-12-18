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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_9__ {int /*<<< orphan*/  Cedar; } ;
struct TYPE_8__ {TYPE_5__* Server; } ;
struct TYPE_7__ {int /*<<< orphan*/  DeviceName; int /*<<< orphan*/  HubName; } ;
typedef  TYPE_1__ RPC_LOCALBRIDGE ;
typedef  TYPE_2__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_2__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DeleteLocalBridge (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  ERR_OBJECT_NOT_FOUND ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_5__*) ; 
 scalar_t__ IsEmptyStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 

UINT StDeleteLocalBridge(ADMIN *a, RPC_LOCALBRIDGE *t)
{
	if (IsEmptyStr(t->DeviceName) || IsEmptyStr(t->HubName))
	{
		return ERR_INVALID_PARAMETER;
	}

	SERVER_ADMIN_ONLY;

	ALog(a, NULL, "LA_DELETE_BRIDGE", t->HubName, t->DeviceName);

	if (DeleteLocalBridge(a->Server->Cedar, t->HubName, t->DeviceName) == false)
	{
		return ERR_OBJECT_NOT_FOUND;
	}

	IncrementServerConfigRevision(a->Server);

	return ERR_NO_ERROR;
}