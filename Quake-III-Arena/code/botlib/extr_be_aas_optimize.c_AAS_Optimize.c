#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int* faceoptimizeindex; int* edgeoptimizeindex; } ;
typedef  TYPE_2__ optimized_t ;
struct TYPE_11__ {int numareas; int reachabilitysize; TYPE_1__* reachability; } ;
struct TYPE_10__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*) ;} ;
struct TYPE_8__ {int traveltype; int facenum; int edgenum; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_OptimizeAlloc (TYPE_2__*) ; 
 int /*<<< orphan*/  AAS_OptimizeArea (TYPE_2__*,int) ; 
 int /*<<< orphan*/  AAS_OptimizeStore (TYPE_2__*) ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int TRAVELTYPE_MASK ; 
 int TRAVEL_ELEVATOR ; 
 int TRAVEL_FUNCBOB ; 
 int TRAVEL_JUMPPAD ; 
 TYPE_4__ aasworld ; 
 size_t abs (int) ; 
 TYPE_3__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*) ; 

void AAS_Optimize(void)
{
	int i, sign;
	optimized_t optimized;

	AAS_OptimizeAlloc(&optimized);
	for (i = 1; i < aasworld.numareas; i++)
	{
		AAS_OptimizeArea(&optimized, i);
	} //end for
	//reset the reachability face pointers
	for (i = 0; i < aasworld.reachabilitysize; i++)
	{
		//NOTE: for TRAVEL_ELEVATOR the facenum is the model number of
		//		the elevator
		if ((aasworld.reachability[i].traveltype & TRAVELTYPE_MASK) == TRAVEL_ELEVATOR) continue;
		//NOTE: for TRAVEL_JUMPPAD the facenum is the Z velocity and the edgenum is the hor velocity
		if ((aasworld.reachability[i].traveltype & TRAVELTYPE_MASK) == TRAVEL_JUMPPAD) continue;
		//NOTE: for TRAVEL_FUNCBOB the facenum and edgenum contain other coded information
		if ((aasworld.reachability[i].traveltype & TRAVELTYPE_MASK) == TRAVEL_FUNCBOB) continue;
		//
		sign = aasworld.reachability[i].facenum;
		aasworld.reachability[i].facenum = optimized.faceoptimizeindex[abs(aasworld.reachability[i].facenum)];
		if (sign < 0) aasworld.reachability[i].facenum = -aasworld.reachability[i].facenum;
		sign = aasworld.reachability[i].edgenum;
		aasworld.reachability[i].edgenum = optimized.edgeoptimizeindex[abs(aasworld.reachability[i].edgenum)];
		if (sign < 0) aasworld.reachability[i].edgenum = -aasworld.reachability[i].edgenum;
	} //end for
	//store the optimized AAS data into aasworld
	AAS_OptimizeStore(&optimized);
	//print some nice stuff :)
	botimport.Print(PRT_MESSAGE, "AAS data optimized.\n");
}