#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
struct TYPE_10__ {int IpAddress; int SubnetMask; int /*<<< orphan*/  HubName; TYPE_2__* Switch; } ;
struct TYPE_9__ {int Active; int /*<<< orphan*/  lock; int /*<<< orphan*/  IfList; TYPE_1__* Cedar; int /*<<< orphan*/  TableList; } ;
struct TYPE_8__ {int /*<<< orphan*/  Server; } ;
typedef  TYPE_2__ L3SW ;
typedef  TYPE_3__ L3IF ;

/* Variables and functions */
 scalar_t__ GetServerCapsInt (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int IsSafeStr (char*) ; 
 int /*<<< orphan*/ * L3SearchIf (TYPE_2__*,char*) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 TYPE_3__* ZeroMalloc (int) ; 

bool L3AddIf(L3SW *s, char *hubname, UINT ip, UINT subnet)
{
	L3IF *f;
	bool ret = false;
	// Validate arguments
	if (s == NULL || hubname == NULL || IsSafeStr(hubname) == false ||
		ip == 0 || ip == 0xffffffff)
	{
		return false;
	}

	Lock(s->lock);
	{
		if (LIST_NUM(s->TableList) >= GetServerCapsInt(s->Cedar->Server, "i_max_l3_if"))
		{
			// Too many
		}
		else
		{
			if (s->Active == false)
			{
				// Examine whether the interface is already in the same Virtual HUB
				if (L3SearchIf(s, hubname) == NULL)
				{
					// Add
					f = ZeroMalloc(sizeof(L3IF));

					f->Switch = s;
					StrCpy(f->HubName, sizeof(f->HubName), hubname);
					f->IpAddress = ip;
					f->SubnetMask = subnet;

					Insert(s->IfList, f);

					ret = true;
				}
			}
		}
	}
	Unlock(s->lock);

	return ret;
}