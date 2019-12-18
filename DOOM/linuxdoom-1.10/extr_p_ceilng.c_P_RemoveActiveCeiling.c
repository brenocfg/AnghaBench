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
struct TYPE_6__ {int /*<<< orphan*/  thinker; TYPE_1__* sector; } ;
typedef  TYPE_2__ ceiling_t ;
struct TYPE_5__ {int /*<<< orphan*/ * specialdata; } ;

/* Variables and functions */
 int MAXCEILINGS ; 
 int /*<<< orphan*/  P_RemoveThinker (int /*<<< orphan*/ *) ; 
 TYPE_2__** activeceilings ; 

void P_RemoveActiveCeiling(ceiling_t* c)
{
    int		i;
	
    for (i = 0;i < MAXCEILINGS;i++)
    {
	if (activeceilings[i] == c)
	{
	    activeceilings[i]->sector->specialdata = NULL;
	    P_RemoveThinker (&activeceilings[i]->thinker);
	    activeceilings[i] = NULL;
	    break;
	}
    }
}