#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  numlinks; TYPE_2__* first; } ;
typedef  TYPE_1__ aas_reversedreachability_t ;
struct TYPE_9__ {int areanum; int linknum; struct TYPE_9__* next; } ;
typedef  TYPE_2__ aas_reversedlink_t ;
struct TYPE_10__ {size_t areanum; } ;
typedef  TYPE_3__ aas_reachability_t ;
struct TYPE_11__ {int numreachableareas; int firstreachablearea; } ;
typedef  TYPE_4__ aas_areasettings_t ;
struct TYPE_13__ {int numareas; int reachabilitysize; TYPE_1__* reversedreachability; TYPE_3__* reachability; TYPE_4__* areasettings; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FreeMemory (TYPE_1__*) ; 
 scalar_t__ GetClearedMemory (int) ; 
 int /*<<< orphan*/  PRT_MESSAGE ; 
 int /*<<< orphan*/  PRT_WARNING ; 
 int Sys_MilliSeconds () ; 
 TYPE_6__ aasworld ; 
 TYPE_5__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,char*,int) ; 

void AAS_CreateReversedReachability(void)
{
	int i, n;
	aas_reversedlink_t *revlink;
	aas_reachability_t *reach;
	aas_areasettings_t *settings;
	char *ptr;
#ifdef DEBUG
	int starttime;

	starttime = Sys_MilliSeconds();
#endif
	//free reversed links that have already been created
	if (aasworld.reversedreachability) FreeMemory(aasworld.reversedreachability);
	//allocate memory for the reversed reachability links
	ptr = (char *) GetClearedMemory(aasworld.numareas * sizeof(aas_reversedreachability_t) +
							aasworld.reachabilitysize * sizeof(aas_reversedlink_t));
	//
	aasworld.reversedreachability = (aas_reversedreachability_t *) ptr;
	//pointer to the memory for the reversed links
	ptr += aasworld.numareas * sizeof(aas_reversedreachability_t);
	//check all reachabilities of all areas
	for (i = 1; i < aasworld.numareas; i++)
	{
		//settings of the area
		settings = &aasworld.areasettings[i];
		//
		if (settings->numreachableareas >= 128)
			botimport.Print(PRT_WARNING, "area %d has more than 128 reachabilities\n", i);
		//create reversed links for the reachabilities
		for (n = 0; n < settings->numreachableareas && n < 128; n++)
		{
			//reachability link
			reach = &aasworld.reachability[settings->firstreachablearea + n];
			//
			revlink = (aas_reversedlink_t *) ptr;
			ptr += sizeof(aas_reversedlink_t);
			//
			revlink->areanum = i;
			revlink->linknum = settings->firstreachablearea + n;
			revlink->next = aasworld.reversedreachability[reach->areanum].first;
			aasworld.reversedreachability[reach->areanum].first = revlink;
			aasworld.reversedreachability[reach->areanum].numlinks++;
		} //end for
	} //end for
#ifdef DEBUG
	botimport.Print(PRT_MESSAGE, "reversed reachability %d msec\n", Sys_MilliSeconds() - starttime);
#endif
}