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
struct TYPE_5__ {size_t areanum; int /*<<< orphan*/  backcluster; int /*<<< orphan*/  frontcluster; } ;
typedef  TYPE_2__ aas_portal_t ;
struct TYPE_6__ {int numportals; TYPE_1__* areasettings; TYPE_2__* portals; } ;
struct TYPE_4__ {int /*<<< orphan*/  contents; } ;

/* Variables and functions */
 int /*<<< orphan*/  AREACONTENTS_CLUSTERPORTAL ; 
 int /*<<< orphan*/  Log_Write (char*,size_t) ; 
 TYPE_3__ aasworld ; 
 int qfalse ; 
 int qtrue ; 

int AAS_TestPortals(void)
{
	int i;
	aas_portal_t *portal;

	for (i = 1; i < aasworld.numportals; i++)
	{
		portal = &aasworld.portals[i];
		if (!portal->frontcluster)
		{
			aasworld.areasettings[portal->areanum].contents &= ~AREACONTENTS_CLUSTERPORTAL;
			Log_Write("portal area %d has no front cluster\r\n", portal->areanum);
			return qfalse;
		} //end if
		if (!portal->backcluster)
		{
			aasworld.areasettings[portal->areanum].contents &= ~AREACONTENTS_CLUSTERPORTAL;
			Log_Write("portal area %d has no back cluster\r\n", portal->areanum);
			return qfalse;
		} //end if
	} //end for
	return qtrue;
}