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
struct TYPE_4__ {float time; int /*<<< orphan*/  numframes; scalar_t__ frameroutingupdates; } ;
struct TYPE_3__ {scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_ContinueInit (float) ; 
 int /*<<< orphan*/  AAS_InvalidateEntities () ; 
 int /*<<< orphan*/  AAS_RoutingInfo () ; 
 int /*<<< orphan*/  AAS_UnlinkInvalidEntities () ; 
 int /*<<< orphan*/  AAS_WriteRouteCache () ; 
 int BLERR_NOERROR ; 
 scalar_t__ LibVarGetValue (char*) ; 
 int /*<<< orphan*/  LibVarSet (char*,char*) ; 
 int /*<<< orphan*/  PrintMemoryLabels () ; 
 int /*<<< orphan*/  PrintUsedMemorySize () ; 
 TYPE_2__ aasworld ; 
 scalar_t__ bot_developer ; 
 TYPE_1__* saveroutingcache ; 

int AAS_StartFrame(float time)
{
	aasworld.time = time;
	//unlink all entities that were not updated last frame
	AAS_UnlinkInvalidEntities();
	//invalidate the entities
	AAS_InvalidateEntities();
	//initialize AAS
	AAS_ContinueInit(time);
	//
	aasworld.frameroutingupdates = 0;
	//
	if (bot_developer)
	{
		if (LibVarGetValue("showcacheupdates"))
		{
			AAS_RoutingInfo();
			LibVarSet("showcacheupdates", "0");
		} //end if
		if (LibVarGetValue("showmemoryusage"))
		{
			PrintUsedMemorySize();
			LibVarSet("showmemoryusage", "0");
		} //end if
		if (LibVarGetValue("memorydump"))
		{
			PrintMemoryLabels();
			LibVarSet("memorydump", "0");
		} //end if
	} //end if
	//
	if (saveroutingcache->value)
	{
		AAS_WriteRouteCache();
		LibVarSet("saveroutingcache", "0");
	} //end if
	//
	aasworld.numframes++;
	return BLERR_NOERROR;
}