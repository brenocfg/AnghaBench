#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int reachabilitysize; TYPE_1__* reachability; } ;
struct TYPE_3__ {int traveltype; int facenum; } ;

/* Variables and functions */
 int TRAVELTYPE_MASK ; 
 int TRAVEL_ELEVATOR ; 
 int TRAVEL_FUNCBOB ; 
 TYPE_2__ aasworld ; 

int AAS_NextModelReachability(int num, int modelnum)
{
	int i;

	if (num <= 0) num = 1;
	else if (num >= aasworld.reachabilitysize) return 0;
	else num++;
	//
	for (i = num; i < aasworld.reachabilitysize; i++)
	{
		if ((aasworld.reachability[i].traveltype & TRAVELTYPE_MASK) == TRAVEL_ELEVATOR)
		{
			if (aasworld.reachability[i].facenum == modelnum) return i;
		} //end if
		else if ((aasworld.reachability[i].traveltype & TRAVELTYPE_MASK) == TRAVEL_FUNCBOB)
		{
			if ((aasworld.reachability[i].facenum & 0x0000FFFF) == modelnum) return i;
		} //end if
	} //end for
	return 0;
}