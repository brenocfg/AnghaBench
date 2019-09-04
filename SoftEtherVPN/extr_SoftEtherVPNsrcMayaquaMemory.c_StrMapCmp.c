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
typedef  TYPE_1__ STRMAP_ENTRY ;

/* Variables and functions */
 int StrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int StrMapCmp(void *p1, void *p2)
{
	STRMAP_ENTRY *s1, *s2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	s1 = *(STRMAP_ENTRY **)p1;
	s2 = *(STRMAP_ENTRY **)p2;
	if (s1 == NULL || s2 == NULL)
	{
		return 0;
	}
	return StrCmpi(s1->Name, s2->Name);
}