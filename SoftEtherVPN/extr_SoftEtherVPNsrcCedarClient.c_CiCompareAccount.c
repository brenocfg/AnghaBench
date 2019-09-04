#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* ClientOption; } ;
struct TYPE_3__ {int /*<<< orphan*/  AccountName; } ;
typedef  TYPE_2__ ACCOUNT ;

/* Variables and functions */
 int UniStrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int CiCompareAccount(void *p1, void *p2)
{
	ACCOUNT *a1, *a2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	a1 = *(ACCOUNT **)p1;
	a2 = *(ACCOUNT **)p2;
	if (a1 == NULL || a2 == NULL)
	{
		return 0;
	}

	return UniStrCmpi(a1->ClientOption->AccountName, a2->ClientOption->AccountName);
}