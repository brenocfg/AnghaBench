#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int Active; int /*<<< orphan*/  lock; int /*<<< orphan*/  TableList; TYPE_1__* Cedar; } ;
struct TYPE_12__ {scalar_t__ Metric; int GatewayAddress; } ;
struct TYPE_11__ {int /*<<< orphan*/  Server; } ;
typedef  TYPE_2__ L3TABLE ;
typedef  TYPE_3__ L3SW ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (TYPE_2__*,TYPE_2__*,int) ; 
 scalar_t__ GetServerCapsInt (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Insert (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * Search (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  Unlock (int /*<<< orphan*/ ) ; 
 TYPE_2__* ZeroMalloc (int) ; 

bool L3AddTable(L3SW *s, L3TABLE *tbl)
{
	bool ret = false;
	// Validate arguments
	if (s == NULL || tbl == NULL)
	{
		return false;
	}

	if (tbl->Metric == 0 || tbl->GatewayAddress == 0 || tbl->GatewayAddress == 0xffffffff)
	{
		return false;
	}

	Lock(s->lock);
	{
		if (LIST_NUM(s->TableList) >= GetServerCapsInt(s->Cedar->Server, "i_max_l3_table"))
		{
			// Too many
		}
		else
		{
			// Create
			if (s->Active == false)
			{
				if (Search(s->TableList, tbl) == NULL)
				{
					L3TABLE *t = ZeroMalloc(sizeof(L3TABLE));

					Copy(t, tbl, sizeof(L3TABLE));

					Insert(s->TableList, t);

					ret = true;
				}
			}
		}
	}
	Unlock(s->lock);

	return ret;
}