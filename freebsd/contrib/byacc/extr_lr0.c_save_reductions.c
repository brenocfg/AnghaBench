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
struct TYPE_5__ {size_t nreds; size_t* rules; struct TYPE_5__* next; int /*<<< orphan*/  number; } ;
typedef  TYPE_1__ reductions ;
typedef  size_t Value_t ;
struct TYPE_6__ {int /*<<< orphan*/  number; } ;

/* Variables and functions */
 scalar_t__ allocate (int) ; 
 TYPE_1__* first_reduction ; 
 size_t* itemset ; 
 size_t* itemsetend ; 
 TYPE_1__* last_reduction ; 
 size_t* redset ; 
 int* ritem ; 
 TYPE_2__* this_state ; 

__attribute__((used)) static void
save_reductions(void)
{
    Value_t *isp;
    Value_t *rp1;
    Value_t *rp2;
    int item;
    Value_t count;
    reductions *p;
    Value_t *rend;

    count = 0;
    for (isp = itemset; isp < itemsetend; isp++)
    {
	item = ritem[*isp];
	if (item < 0)
	{
	    redset[count++] = (Value_t)-item;
	}
    }

    if (count)
    {
	p = (reductions *)allocate((sizeof(reductions) +
				      (unsigned)(count - 1) *
				    sizeof(Value_t)));

	p->number = this_state->number;
	p->nreds = count;

	rp1 = redset;
	rp2 = p->rules;
	rend = rp1 + count;

	while (rp1 < rend)
	    *rp2++ = *rp1++;

	if (last_reduction)
	{
	    last_reduction->next = p;
	    last_reduction = p;
	}
	else
	{
	    first_reduction = p;
	    last_reduction = p;
	}
    }
}