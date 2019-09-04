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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ELEMENT ;

/* Variables and functions */
 int StrCmpi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ComparePackName(void *p1, void *p2)
{
	ELEMENT *o1, *o2;
	if (p1 == NULL || p2 == NULL)
	{
		return 0;
	}
	o1 = *(ELEMENT **)p1;
	o2 = *(ELEMENT **)p2;
	if (o1 == NULL || o2 == NULL)
	{
		return 0;
	}

	return StrCmpi(o1->name, o2->name);
}