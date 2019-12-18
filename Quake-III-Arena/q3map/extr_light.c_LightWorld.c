#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  CreateEntityLights () ; 
 float FloatForKey (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  GetVectorForKey (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RunThreadsOnIndividual (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetupGrid () ; 
 int /*<<< orphan*/  TraceGrid ; 
 int /*<<< orphan*/  TraceLtm ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ ,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ambientColor ; 
 int /*<<< orphan*/  c_occluded ; 
 int /*<<< orphan*/  c_visible ; 
 int /*<<< orphan*/ * entities ; 
 int /*<<< orphan*/ * gridBounds ; 
 int /*<<< orphan*/  nogridlighting ; 
 int /*<<< orphan*/  numAreaLights ; 
 int /*<<< orphan*/  numDrawSurfaces ; 
 int /*<<< orphan*/  numGridPoints ; 
 int /*<<< orphan*/  numPointLights ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 
 int /*<<< orphan*/  qtrue ; 

void LightWorld (void) {
	float		f;

	// determine the number of grid points
	SetupGrid();

	// find the optional world ambient
	GetVectorForKey( &entities[0], "_color", ambientColor );
	f = FloatForKey( &entities[0], "ambient" );
	VectorScale( ambientColor, f, ambientColor );

	// create lights out of patches and lights
	qprintf ("--- CreateLights ---\n");
	CreateEntityLights ();
	qprintf ("%i point lights\n", numPointLights);
	qprintf ("%i area lights\n", numAreaLights);

	if (!nogridlighting) {
		qprintf ("--- TraceGrid ---\n");
		RunThreadsOnIndividual( numGridPoints, qtrue, TraceGrid );
		qprintf( "%i x %i x %i = %i grid\n", gridBounds[0], gridBounds[1],
			gridBounds[2], numGridPoints);
	}

	qprintf ("--- TraceLtm ---\n");
	RunThreadsOnIndividual( numDrawSurfaces, qtrue, TraceLtm );
	qprintf( "%5i visible samples\n", c_visible );
	qprintf( "%5i occluded samples\n", c_occluded );
}