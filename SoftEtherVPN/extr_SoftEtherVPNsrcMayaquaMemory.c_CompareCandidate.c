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
struct TYPE_2__ {scalar_t__ LastSelectedTime; int /*<<< orphan*/  Str; } ;
typedef  TYPE_1__ CANDIDATE ;

/* Variables and functions */
 int UniStrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int CompareCandidate(void *p1, void *p2)
{
	CANDIDATE *c1, *c2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	c1 = *(CANDIDATE **)p1;
	c2 = *(CANDIDATE **)p2;
	if (c1 == NULL || c2 == NULL)
	{
		return 0;
	}
	if (c1->LastSelectedTime > c2->LastSelectedTime)
	{
		return -1;
	}
	else if (c1->LastSelectedTime < c2->LastSelectedTime)
	{
		return 1;
	}
	else
	{
		return UniStrCmpi(c1->Str, c2->Str);
	}
}