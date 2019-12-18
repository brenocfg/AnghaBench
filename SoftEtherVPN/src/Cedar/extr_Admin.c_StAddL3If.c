#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_16__ {TYPE_1__* Server; } ;
struct TYPE_15__ {int /*<<< orphan*/  lock; } ;
struct TYPE_14__ {int SubnetMask; int IpAddress; int /*<<< orphan*/  Name; int /*<<< orphan*/  HubName; } ;
struct TYPE_13__ {int /*<<< orphan*/ * Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_L3IF ;
typedef  TYPE_3__ L3SW ;
typedef  int /*<<< orphan*/  CEDAR ;
typedef  TYPE_4__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_4__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERR_LAYER3_IF_ADD_FAILED ; 
 int /*<<< orphan*/  ERR_LAYER3_IF_EXISTS ; 
 int /*<<< orphan*/  ERR_LAYER3_SW_NOT_FOUND ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_1__*) ; 
 int IsHostIPAddress32 (int) ; 
 int IsSubnetMask32 (int) ; 
 int L3AddIf (TYPE_3__*,int /*<<< orphan*/ ,int,int) ; 
 TYPE_3__* L3GetSw (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * L3SearchIf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NO_SUPPORT_FOR_BRIDGE ; 
 int /*<<< orphan*/  ReleaseL3Sw (TYPE_3__*) ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 

UINT StAddL3If(ADMIN *a, RPC_L3IF *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	UINT ret = ERR_NO_ERROR;
	L3SW *sw;


	if (IsSubnetMask32(t->SubnetMask) == false || IsHostIPAddress32(t->IpAddress) == false)
	{
		return ERR_INVALID_PARAMETER;
	}
	if ((t->IpAddress & (~t->SubnetMask)) == 0)
	{
		return ERR_INVALID_PARAMETER;
	}

	NO_SUPPORT_FOR_BRIDGE;

	SERVER_ADMIN_ONLY;

	sw = L3GetSw(c, t->Name);

	if (sw == NULL)
	{
		ret = ERR_LAYER3_SW_NOT_FOUND;
	}
	else
	{
		Lock(sw->lock);
		{
			if (L3SearchIf(sw, t->HubName) != NULL)
			{
				// Already exists
				ret = ERR_LAYER3_IF_EXISTS;
			}
			else
			{
				if (L3AddIf(sw, t->HubName, t->IpAddress, t->SubnetMask) == false)
				{
					ret = ERR_LAYER3_IF_ADD_FAILED;
				}
				else
				{
					ALog(a, NULL, "LA_ADD_L3_IF", t->HubName, t->Name);

					IncrementServerConfigRevision(s);
				}
			}
		}
		Unlock(sw->lock);
		ReleaseL3Sw(sw);
	}

	return ret;
}