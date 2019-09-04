#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  t ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_8__ {int /*<<< orphan*/  Value; int /*<<< orphan*/  Name; } ;
struct TYPE_7__ {int /*<<< orphan*/  AdminOptionList; } ;
typedef  TYPE_1__ HUB ;
typedef  TYPE_2__ ADMIN_OPTION ;

/* Variables and functions */
 int /*<<< orphan*/  LockList (int /*<<< orphan*/ ) ; 
 TYPE_2__* Search (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  StrCpy (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  Trim (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UnlockList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Zero (TYPE_2__*,int) ; 

UINT GetHubAdminOptionEx(HUB *h, char *name, UINT default_value)
{
	UINT ret = default_value;
	// Validate arguments
	if (h == NULL || name == NULL)
	{
		return 0;
	}

	LockList(h->AdminOptionList);
	{
		ADMIN_OPTION *a, t;

		Zero(&t, sizeof(t));
		StrCpy(t.Name, sizeof(t.Name), name);
		Trim(t.Name);

		a = Search(h->AdminOptionList, &t);

		if (a != NULL)
		{
			ret = a->Value;
		}
	}
	UnlockList(h->AdminOptionList);

	return ret;
}