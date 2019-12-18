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
struct TYPE_3__ {int /*<<< orphan*/  contents; } ;

/* Variables and functions */
 int /*<<< orphan*/  AREACONTENTS_CLUSTERPORTAL ; 
 TYPE_2__ aasworld ; 

void AAS_RemoveAllPortals(void)
{
	int i;

	for (i = 1; i < aasworld.numareas; i++)
	{
		aasworld.areasettings[i].contents &= ~AREACONTENTS_CLUSTERPORTAL;
	} //end for
}