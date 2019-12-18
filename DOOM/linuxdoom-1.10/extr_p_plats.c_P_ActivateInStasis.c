#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ actionf_p1 ;
struct TYPE_4__ {scalar_t__ acp1; } ;
struct TYPE_5__ {TYPE_1__ function; } ;
struct TYPE_6__ {int tag; scalar_t__ status; scalar_t__ oldstatus; TYPE_2__ thinker; } ;

/* Variables and functions */
 int MAXPLATS ; 
 scalar_t__ T_PlatRaise ; 
 TYPE_3__** activeplats ; 
 scalar_t__ in_stasis ; 

void P_ActivateInStasis(int tag)
{
    int		i;
	
    for (i = 0;i < MAXPLATS;i++)
	if (activeplats[i]
	    && (activeplats[i])->tag == tag
	    && (activeplats[i])->status == in_stasis)
	{
	    (activeplats[i])->status = (activeplats[i])->oldstatus;
	    (activeplats[i])->thinker.function.acp1
	      = (actionf_p1) T_PlatRaise;
	}
}