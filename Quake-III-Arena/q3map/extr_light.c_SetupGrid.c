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
typedef  int* vec3_t ;
struct TYPE_2__ {int* mins; int* maxs; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int MAX_MAP_LIGHTGRID ; 
 int ceil (int) ; 
 TYPE_1__* dmodels ; 
 int floor (int) ; 
 int* gridBounds ; 
 int* gridMins ; 
 int* gridSize ; 
 int numGridPoints ; 
 int /*<<< orphan*/  qprintf (char*,int) ; 

void SetupGrid( void ) {
	int		i;
	vec3_t	maxs;

	for ( i = 0 ; i < 3 ; i++ ) {
		gridMins[i] = gridSize[i] * ceil( dmodels[0].mins[i] / gridSize[i] );
		maxs[i] = gridSize[i] * floor( dmodels[0].maxs[i] / gridSize[i] );
		gridBounds[i] = (maxs[i] - gridMins[i])/gridSize[i] + 1;
	}

	numGridPoints = gridBounds[0] * gridBounds[1] * gridBounds[2];
	if (numGridPoints * 8 >= MAX_MAP_LIGHTGRID)
		Error("MAX_MAP_LIGHTGRID");
	qprintf( "%5i gridPoints\n", numGridPoints );
}