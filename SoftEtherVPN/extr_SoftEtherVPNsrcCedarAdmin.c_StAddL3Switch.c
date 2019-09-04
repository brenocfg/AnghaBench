#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_15__ {TYPE_1__* Server; } ;
struct TYPE_14__ {int /*<<< orphan*/  L3SwList; } ;
struct TYPE_13__ {int /*<<< orphan*/  Name; } ;
struct TYPE_12__ {TYPE_3__* Cedar; } ;
typedef  TYPE_1__ SERVER ;
typedef  TYPE_2__ RPC_L3SW ;
typedef  int /*<<< orphan*/  L3SW ;
typedef  TYPE_3__ CEDAR ;
typedef  TYPE_4__ ADMIN ;

/* Variables and functions */
 int /*<<< orphan*/  ALog (TYPE_4__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  ERR_LAYER3_SW_EXISTS ; 
 int /*<<< orphan*/  ERR_NO_ERROR ; 
 scalar_t__ GetServerCapsInt (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  IncrementServerConfigRevision (TYPE_1__*) ; 
 scalar_t__ IsEmptyStr (int /*<<< orphan*/ ) ; 
 int IsSafeStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * L3AddSw (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * L3GetSw (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NO_SUPPORT_FOR_BRIDGE ; 
 int /*<<< orphan*/  ReleaseL3Sw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SERVER_ADMIN_ONLY ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

UINT StAddL3Switch(ADMIN *a, RPC_L3SW *t)
{
	SERVER *s = a->Server;
	CEDAR *c = s->Cedar;
	UINT ret = ERR_NO_ERROR;
	L3SW *sw;

	NO_SUPPORT_FOR_BRIDGE;

	if (IsEmptyStr(t->Name))
	{
		return ERR_INVALID_PARAMETER;
	}

	if (IsSafeStr(t->Name) == false)
	{
		return ERR_INVALID_PARAMETER;
	}

	SERVER_ADMIN_ONLY;

	// Duplication check
	sw = L3GetSw(c, t->Name);
	if (sw != NULL)
	{
		// Already exists
		ReleaseL3Sw(sw);
		ret = ERR_LAYER3_SW_EXISTS;
	}
	else
	{
		LockList(c->L3SwList);
		{
			if (LIST_NUM(c->L3SwList) >= GetServerCapsInt(s, "i_max_l3_sw"))
			{
				// No more virtual interfaces
				sw = NULL;
			}
			else
			{
				// Create
				sw = L3AddSw(c, t->Name);

				if (sw != NULL)
				{
					ALog(a, NULL, "LA_ADD_L3_SW", t->Name);

					IncrementServerConfigRevision(s);
				}
			}
		}
		UnlockList(c->L3SwList);

		if (sw == NULL)
		{
			// Failed
			ret = ERR_INTERNAL_ERROR;
		}
		else
		{
			// Success
			ReleaseL3Sw(sw);
		}
	}

	return ret;
}