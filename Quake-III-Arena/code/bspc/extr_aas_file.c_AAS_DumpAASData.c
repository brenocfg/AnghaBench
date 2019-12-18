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
struct TYPE_2__ {int loaded; } ;

/* Variables and functions */
 TYPE_1__ aasworld ; 

void AAS_DumpAASData(void)
{
	/*
	if (aasworld.vertexes) FreeMemory(aasworld.vertexes);
	aasworld.vertexes = NULL;
	if (aasworld.planes) FreeMemory(aasworld.planes);
	aasworld.planes = NULL;
	if (aasworld.edges) FreeMemory(aasworld.edges);
	aasworld.edges = NULL;
	if (aasworld.edgeindex) FreeMemory(aasworld.edgeindex);
	aasworld.edgeindex = NULL;
	if (aasworld.faces) FreeMemory(aasworld.faces);
	aasworld.faces = NULL;
	if (aasworld.faceindex) FreeMemory(aasworld.faceindex);
	aasworld.faceindex = NULL;
	if (aasworld.areas) FreeMemory(aasworld.areas);
	aasworld.areas = NULL;
	if (aasworld.areasettings) FreeMemory(aasworld.areasettings);
	aasworld.areasettings = NULL;
	if (aasworld.reachability) FreeMemory(aasworld.reachability);
	aasworld.reachability = NULL;
	*/
	aasworld.loaded = false;
}