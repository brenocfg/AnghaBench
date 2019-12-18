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
struct TYPE_4__ {void** items; struct TYPE_4__* next; void* nitems; void* number; void* accessing_symbol; } ;
typedef  TYPE_1__ core ;
typedef  void* Value_t ;

/* Variables and functions */
 scalar_t__ MAXYYINT ; 
 scalar_t__ allocate (int) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 void*** kernel_base ; 
 void*** kernel_end ; 
 TYPE_1__* last_state ; 
 scalar_t__ nstates ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static core *
new_state(int symbol)
{
    unsigned n;
    core *p;
    Value_t *isp1;
    Value_t *isp2;
    Value_t *iend;

#ifdef	TRACE
    fprintf(stderr, "Entering new_state(%d)\n", symbol);
#endif

    if (nstates >= MAXYYINT)
	fatal("too many states");

    isp1 = kernel_base[symbol];
    iend = kernel_end[symbol];
    n = (unsigned)(iend - isp1);

    p = (core *)allocate((sizeof(core) + (n - 1) * sizeof(Value_t)));
    p->accessing_symbol = (Value_t)symbol;
    p->number = (Value_t)nstates;
    p->nitems = (Value_t)n;

    isp2 = p->items;
    while (isp1 < iend)
	*isp2++ = *isp1++;

    last_state->next = p;
    last_state = p;

    nstates++;

    return (p);
}