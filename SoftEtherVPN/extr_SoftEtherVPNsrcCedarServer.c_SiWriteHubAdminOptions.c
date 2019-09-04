#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_6__ {int /*<<< orphan*/  Value; int /*<<< orphan*/  Name; } ;
struct TYPE_5__ {int /*<<< orphan*/  AdminOptionList; } ;
typedef  TYPE_1__ HUB ;
typedef  int /*<<< orphan*/  FOLDER ;
typedef  TYPE_2__ ADMIN_OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  CfgAddInt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* LIST_DATA (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ LIST_NUM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 

void SiWriteHubAdminOptions(FOLDER *f, HUB *h)
{
	// Validate arguments
	if (f == NULL || h == NULL)
	{
		return;
	}

	LockList(h->AdminOptionList);
	{
		UINT i;
		for (i = 0;i < LIST_NUM(h->AdminOptionList);i++)
		{
			ADMIN_OPTION *a = LIST_DATA(h->AdminOptionList, i);

			CfgAddInt(f, a->Name, a->Value);
		}
	}
	UnlockList(h->AdminOptionList);
}