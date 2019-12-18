#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ tag; } ;
typedef  TYPE_3__ line_t ;
typedef  scalar_t__ actionf_v ;
struct TYPE_6__ {scalar_t__ acv; } ;
struct TYPE_7__ {TYPE_1__ function; } ;
struct TYPE_9__ {scalar_t__ status; scalar_t__ tag; scalar_t__ oldstatus; TYPE_2__ thinker; } ;

/* Variables and functions */
 int MAXPLATS ; 
 TYPE_4__** activeplats ; 
 scalar_t__ in_stasis ; 

void EV_StopPlat(line_t* line)
{
    int		j;
	
    for (j = 0;j < MAXPLATS;j++)
	if (activeplats[j]
	    && ((activeplats[j])->status != in_stasis)
	    && ((activeplats[j])->tag == line->tag))
	{
	    (activeplats[j])->oldstatus = (activeplats[j])->status;
	    (activeplats[j])->status = in_stasis;
	    (activeplats[j])->thinker.function.acv = (actionf_v)NULL;
	}
}