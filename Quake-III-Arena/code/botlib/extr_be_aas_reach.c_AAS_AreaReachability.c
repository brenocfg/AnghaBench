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
struct TYPE_4__ {int numareas; TYPE_1__* areasettings; } ;
struct TYPE_3__ {int numreachableareas; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_Error (char*,int) ; 
 TYPE_2__ aasworld ; 

int AAS_AreaReachability(int areanum)
{
	if (areanum < 0 || areanum >= aasworld.numareas)
	{
		AAS_Error("AAS_AreaReachability: areanum %d out of range", areanum);
		return 0;
	} //end if
	return aasworld.areasettings[areanum].numreachableareas;
}