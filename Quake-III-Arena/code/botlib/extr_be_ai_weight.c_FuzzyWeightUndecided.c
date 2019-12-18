#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* weights; } ;
typedef  TYPE_2__ weightconfig_t ;
struct TYPE_8__ {size_t index; int value; float minweight; int maxweight; struct TYPE_8__* next; struct TYPE_8__* child; } ;
typedef  TYPE_3__ fuzzyseperator_t ;
struct TYPE_6__ {TYPE_3__* firstseperator; } ;

/* Variables and functions */
 float FuzzyWeightUndecided_r (int*,TYPE_3__*) ; 
 int random () ; 

float FuzzyWeightUndecided(int *inventory, weightconfig_t *wc, int weightnum)
{
#ifdef EVALUATERECURSIVELY
	return FuzzyWeightUndecided_r(inventory, wc->weights[weightnum].firstseperator);
#else
	fuzzyseperator_t *s;

	s = wc->weights[weightnum].firstseperator;
	if (!s) return 0;
	while(1)
	{
		if (inventory[s->index] < s->value)
		{
			if (s->child) s = s->child;
			else return s->minweight + random() * (s->maxweight - s->minweight);
		} //end if
		else
		{
			if (s->next) s = s->next;
			else return s->minweight + random() * (s->maxweight - s->minweight);
		} //end else
	} //end if
	return 0;
#endif
}