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
struct TYPE_5__ {int areanum; scalar_t__ backcluster; scalar_t__ frontcluster; } ;
typedef  TYPE_2__ aas_portal_t ;
struct TYPE_6__ {int numareas; size_t numportals; TYPE_2__* portals; TYPE_1__* areasettings; } ;
struct TYPE_4__ {int contents; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_Error (char*) ; 
 size_t AAS_MAX_PORTALS ; 
 int AREACONTENTS_CLUSTERPORTAL ; 
 TYPE_3__ aasworld ; 

void AAS_CreatePortals(void)
{
	int i;
	aas_portal_t *portal;

	for (i = 1; i < aasworld.numareas; i++)
	{
		//if the area is a cluster portal
		if (aasworld.areasettings[i].contents & AREACONTENTS_CLUSTERPORTAL)
		{
			if (aasworld.numportals >= AAS_MAX_PORTALS)
			{
				AAS_Error("AAS_MAX_PORTALS");
				return;
			} //end if
			portal = &aasworld.portals[aasworld.numportals];
			portal->areanum = i;
			portal->frontcluster = 0;
			portal->backcluster = 0;
			aasworld.numportals++;
		} //end if
	} //end for
}