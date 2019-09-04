#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_5__ {struct TYPE_5__* name; struct TYPE_5__* next; } ;
typedef  TYPE_1__ CALLSTACK_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  OSMemoryFree (TYPE_1__*) ; 

CALLSTACK_DATA *WalkDownCallStack(CALLSTACK_DATA *s, UINT num)
{
	CALLSTACK_DATA *cs, *tmp;
	UINT i;
	// Validate arguments
	if (s == NULL)
	{
		return NULL;
	}

	cs = s;
	i = 0;

	while (true)
	{
		if (i >= num)
		{
			return cs;
		}
		i++;
		tmp = cs;
		cs = tmp->next;
		OSMemoryFree(tmp->name);
		OSMemoryFree(tmp);

		if (cs == NULL)
		{
			return NULL;
		}
	}
}