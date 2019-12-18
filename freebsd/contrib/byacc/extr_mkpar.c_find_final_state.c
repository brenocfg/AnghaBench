#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t* shift; int nshifts; } ;
typedef  TYPE_1__ shifts ;
typedef  size_t Value_t ;

/* Variables and functions */
 int* accessing_symbol ; 
 size_t final_state ; 
 int* ritem ; 
 TYPE_1__** shift_table ; 

__attribute__((used)) static void
find_final_state(void)
{
    int goal, i;
    Value_t *to_state2;
    shifts *p;

    p = shift_table[0];
    to_state2 = p->shift;
    goal = ritem[1];
    for (i = p->nshifts - 1; i >= 0; --i)
    {
	final_state = to_state2[i];
	if (accessing_symbol[final_state] == goal)
	    break;
    }
}