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
 int /*<<< orphan*/  CreateFilters () ; 
 int /*<<< orphan*/  CreateSurfaceLights () ; 
 int /*<<< orphan*/  FindSkyBrushes () ; 
 int /*<<< orphan*/  InitTrace () ; 
 int /*<<< orphan*/  RunThreadsOnIndividual (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetupGrid () ; 
 int /*<<< orphan*/  TraceGrid ; 
 int /*<<< orphan*/  TriSoupLightingThread ; 
 int /*<<< orphan*/  VertexLightingThread ; 
 int /*<<< orphan*/  _printf (char*) ; 
 int /*<<< orphan*/  nogridlighting ; 
 int /*<<< orphan*/  novertexlighting ; 
 int /*<<< orphan*/  numDrawSurfaces ; 
 int /*<<< orphan*/  numGridPoints ; 
 int /*<<< orphan*/  qtrue ; 

void GridAndVertexLighting(void) {
	SetupGrid();

	FindSkyBrushes();
	CreateFilters();
	InitTrace();
	CreateEntityLights ();
	CreateSurfaceLights();

	if (!nogridlighting) {
		_printf ("--- TraceGrid ---\n");
		RunThreadsOnIndividual( numGridPoints, qtrue, TraceGrid );
	}

	if (!novertexlighting) {
		_printf ("--- Vertex Lighting ---\n");
		RunThreadsOnIndividual( numDrawSurfaces, qtrue, VertexLightingThread );
	}

	_printf("--- Model Lighting ---\n");
	RunThreadsOnIndividual( numDrawSurfaces, qtrue, TriSoupLightingThread );
}