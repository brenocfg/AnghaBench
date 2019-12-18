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
struct TYPE_4__ {scalar_t__ action_code; int number; int symbol; struct TYPE_4__* next; } ;
typedef  TYPE_1__ action ;

/* Variables and functions */
 scalar_t__ MaySuppress (TYPE_1__*) ; 
 scalar_t__ REDUCE ; 
 scalar_t__ SHIFT ; 
 TYPE_1__** parser ; 

__attribute__((used)) static int
sole_reduction(int stateno)
{
    int count, ruleno;
    action *p;

    count = 0;
    ruleno = 0;
    for (p = parser[stateno]; p; p = p->next)
    {
	if (p->action_code == SHIFT && MaySuppress(p))
	    return (0);
	else if ((p->action_code == REDUCE) && MaySuppress(p))
	{
	    if (ruleno > 0 && p->number != ruleno)
		return (0);
	    if (p->symbol != 1)
		++count;
	    ruleno = p->number;
	}
    }

    if (count == 0)
	return (0);
    return (ruleno);
}