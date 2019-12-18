#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* portalmaxtraveltimes; int numportals; } ;

/* Variables and functions */
 int AAS_PortalMaxTravelTime (int) ; 
 int /*<<< orphan*/  FreeMemory (int*) ; 
 scalar_t__ GetClearedMemory (int) ; 
 TYPE_1__ aasworld ; 

void AAS_InitPortalMaxTravelTimes(void)
{
	int i;

	if (aasworld.portalmaxtraveltimes) FreeMemory(aasworld.portalmaxtraveltimes);

	aasworld.portalmaxtraveltimes = (int *) GetClearedMemory(aasworld.numportals * sizeof(int));

	for (i = 0; i < aasworld.numportals; i++)
	{
		aasworld.portalmaxtraveltimes[i] = AAS_PortalMaxTravelTime(i);
		//botimport.Print(PRT_MESSAGE, "portal %d max tt = %d\n", i, aasworld.portalmaxtraveltimes[i]);
	} //end for
}