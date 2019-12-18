#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; } ;
typedef  TYPE_1__ maplocation_t ;
typedef  TYPE_1__ campspot_t ;

/* Variables and functions */
 int /*<<< orphan*/  FreeMemory (TYPE_1__*) ; 
 TYPE_1__* campspots ; 
 TYPE_1__* maplocations ; 

void BotFreeInfoEntities(void)
{
	maplocation_t *ml, *nextml;
	campspot_t *cs, *nextcs;

	for (ml = maplocations; ml; ml = nextml)
	{
		nextml = ml->next;
		FreeMemory(ml);
	} //end for
	maplocations = NULL;
	for (cs = campspots; cs; cs = nextcs)
	{
		nextcs = cs->next;
		FreeMemory(cs);
	} //end for
	campspots = NULL;
}