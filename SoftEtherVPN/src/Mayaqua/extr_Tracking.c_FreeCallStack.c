#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* name; struct TYPE_4__* next; } ;
typedef  TYPE_1__ CALLSTACK_DATA ;

/* Variables and functions */
 int /*<<< orphan*/  OSMemoryFree (TYPE_1__*) ; 

void FreeCallStack(CALLSTACK_DATA *s)
{
	// Validate arguments
	if (s == NULL)
	{
		return;
	}

	while (true)
	{
		CALLSTACK_DATA *next = s->next;
		OSMemoryFree(s->name);
		OSMemoryFree(s);
		if (next == NULL)
		{
			break;
		}
		s = next;
	}
}