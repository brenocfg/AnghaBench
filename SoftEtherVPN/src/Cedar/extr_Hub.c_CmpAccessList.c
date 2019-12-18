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
typedef  scalar_t__ UINT64 ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_2__ {scalar_t__ Priority; scalar_t__ Discard; int /*<<< orphan*/  Active; int /*<<< orphan*/  UniqueId; } ;
typedef  TYPE_1__ ACCESS ;

/* Variables and functions */
 int Cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int CmpAccessList(void *p1, void *p2)
{
	ACCESS *a1, *a2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	a1 = *(ACCESS **)p1;
	a2 = *(ACCESS **)p2;
	if (a1 == NULL || a2 == NULL)
	{
		return 0;
	}
	// Sort by priority
	if (a1->Priority > a2->Priority)
	{
		return 1;
	}
	else if (a1->Priority < a2->Priority)
	{
		return -1;
	}
	else if (a1->Discard > a2->Discard)
	{
		return 1;
	}
	else if (a1->Discard < a2->Discard)
	{
		return -1;
	}
	else
	{
		UINT64 size64 = ((UINT64)(&a1->UniqueId) - (UINT64)(&a1->Active));
		UINT size32 = (UINT)size64;

		return Cmp(&a1->Active, &a2->Active, size32);
	}
}