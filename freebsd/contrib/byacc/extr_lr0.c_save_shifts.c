#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; scalar_t__* shift; scalar_t__ nshifts; int /*<<< orphan*/  number; } ;
typedef  TYPE_1__ shifts ;
typedef  scalar_t__ Value_t ;
struct TYPE_6__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 scalar_t__ allocate (int) ; 
 TYPE_1__* first_shift ; 
 TYPE_1__* last_shift ; 
 int nshifts ; 
 scalar_t__* shiftset ; 
 TYPE_2__* this_state ; 

__attribute__((used)) static void
save_shifts(void)
{
    shifts *p;
    Value_t *sp1;
    Value_t *sp2;
    Value_t *send;

    p = (shifts *)allocate((sizeof(shifts) +
			      (unsigned)(nshifts - 1) * sizeof(Value_t)));

    p->number = this_state->number;
    p->nshifts = (Value_t)nshifts;

    sp1 = shiftset;
    sp2 = p->shift;
    send = shiftset + nshifts;

    while (sp1 < send)
	*sp2++ = *sp1++;

    if (last_shift)
    {
	last_shift->next = p;
	last_shift = p;
    }
    else
    {
	first_shift = p;
	last_shift = p;
    }
}