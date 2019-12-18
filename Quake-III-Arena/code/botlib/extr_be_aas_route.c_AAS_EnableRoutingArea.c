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
struct TYPE_6__ {int numareas; TYPE_1__* areasettings; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* Print ) (int /*<<< orphan*/ ,char*,int) ;} ;
struct TYPE_4__ {int areaflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_RemoveRoutingCacheUsingArea (int) ; 
 int AREA_DISABLED ; 
 int /*<<< orphan*/  PRT_ERROR ; 
 TYPE_3__ aasworld ; 
 scalar_t__ bot_developer ; 
 TYPE_2__ botimport ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,char*,int) ; 

int AAS_EnableRoutingArea(int areanum, int enable)
{
	int flags;

	if (areanum <= 0 || areanum >= aasworld.numareas)
	{
		if (bot_developer)
		{
			botimport.Print(PRT_ERROR, "AAS_EnableRoutingArea: areanum %d out of range\n", areanum);
		} //end if
		return 0;
	} //end if
	flags = aasworld.areasettings[areanum].areaflags & AREA_DISABLED;
	if (enable < 0)
		return !flags;

	if (enable)
		aasworld.areasettings[areanum].areaflags &= ~AREA_DISABLED;
	else
		aasworld.areasettings[areanum].areaflags |= AREA_DISABLED;
	// if the status of the area changed
	if ( (flags & AREA_DISABLED) != (aasworld.areasettings[areanum].areaflags & AREA_DISABLED) )
	{
		//remove all routing cache involving this area
		AAS_RemoveRoutingCacheUsingArea( areanum );
	} //end if
	return !flags;
}