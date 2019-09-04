#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  Name; } ;
typedef  TYPE_1__ ADMIN_OPTION ;

/* Variables and functions */
 int StrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int CompareAdminOption(void *p1, void *p2)
{
	ADMIN_OPTION *a1, *a2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	a1 = *(ADMIN_OPTION **)p1;
	a2 = *(ADMIN_OPTION **)p2;
	if (a1 == NULL || a2 == NULL)
	{
		return 0;
	}
	return StrCmpi(a1->Name, a2->Name);
}