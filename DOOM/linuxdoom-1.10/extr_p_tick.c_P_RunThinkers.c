#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ acv; int /*<<< orphan*/  (* acp1 ) (TYPE_3__*) ;} ;
struct TYPE_9__ {struct TYPE_9__* next; TYPE_1__ function; TYPE_2__* prev; } ;
typedef  TYPE_3__ thinker_t ;
typedef  scalar_t__ actionf_v ;
struct TYPE_8__ {TYPE_3__* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  Z_Free (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 TYPE_3__ thinkercap ; 

void P_RunThinkers (void)
{
    thinker_t*	currentthinker;

    currentthinker = thinkercap.next;
    while (currentthinker != &thinkercap)
    {
	if ( currentthinker->function.acv == (actionf_v)(-1) )
	{
	    // time to remove it
	    currentthinker->next->prev = currentthinker->prev;
	    currentthinker->prev->next = currentthinker->next;
	    Z_Free (currentthinker);
	}
	else
	{
	    if (currentthinker->function.acp1)
		currentthinker->function.acp1 (currentthinker);
	}
	currentthinker = currentthinker->next;
    }
}