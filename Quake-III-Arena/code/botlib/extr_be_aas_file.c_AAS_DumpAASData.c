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
struct TYPE_2__ {void* savefile; void* initialized; void* loaded; scalar_t__ numclusters; int /*<<< orphan*/ * clusters; scalar_t__ portalindexsize; int /*<<< orphan*/ * portalindex; scalar_t__ numportals; int /*<<< orphan*/ * portals; int /*<<< orphan*/ * nodes; scalar_t__ numnodes; int /*<<< orphan*/ * reachability; scalar_t__ reachabilitysize; int /*<<< orphan*/ * areasettings; scalar_t__ numareasettings; int /*<<< orphan*/ * areas; scalar_t__ numareas; int /*<<< orphan*/ * faceindex; scalar_t__ faceindexsize; int /*<<< orphan*/ * faces; scalar_t__ numfaces; int /*<<< orphan*/ * edgeindex; scalar_t__ edgeindexsize; int /*<<< orphan*/ * edges; scalar_t__ numedges; int /*<<< orphan*/ * planes; scalar_t__ numplanes; int /*<<< orphan*/ * vertexes; scalar_t__ numvertexes; int /*<<< orphan*/ * bboxes; scalar_t__ numbboxes; } ;

/* Variables and functions */
 int /*<<< orphan*/  FreeMemory (int /*<<< orphan*/ *) ; 
 TYPE_1__ aasworld ; 
 void* qfalse ; 

void AAS_DumpAASData(void)
{
	aasworld.numbboxes = 0;
	if (aasworld.bboxes) FreeMemory(aasworld.bboxes);
	aasworld.bboxes = NULL;
	aasworld.numvertexes = 0;
	if (aasworld.vertexes) FreeMemory(aasworld.vertexes);
	aasworld.vertexes = NULL;
	aasworld.numplanes = 0;
	if (aasworld.planes) FreeMemory(aasworld.planes);
	aasworld.planes = NULL;
	aasworld.numedges = 0;
	if (aasworld.edges) FreeMemory(aasworld.edges);
	aasworld.edges = NULL;
	aasworld.edgeindexsize = 0;
	if (aasworld.edgeindex) FreeMemory(aasworld.edgeindex);
	aasworld.edgeindex = NULL;
	aasworld.numfaces = 0;
	if (aasworld.faces) FreeMemory(aasworld.faces);
	aasworld.faces = NULL;
	aasworld.faceindexsize = 0;
	if (aasworld.faceindex) FreeMemory(aasworld.faceindex);
	aasworld.faceindex = NULL;
	aasworld.numareas = 0;
	if (aasworld.areas) FreeMemory(aasworld.areas);
	aasworld.areas = NULL;
	aasworld.numareasettings = 0;
	if (aasworld.areasettings) FreeMemory(aasworld.areasettings);
	aasworld.areasettings = NULL;
	aasworld.reachabilitysize = 0;
	if (aasworld.reachability) FreeMemory(aasworld.reachability);
	aasworld.reachability = NULL;
	aasworld.numnodes = 0;
	if (aasworld.nodes) FreeMemory(aasworld.nodes);
	aasworld.nodes = NULL;
	aasworld.numportals = 0;
	if (aasworld.portals) FreeMemory(aasworld.portals);
	aasworld.portals = NULL;
	aasworld.numportals = 0;
	if (aasworld.portalindex) FreeMemory(aasworld.portalindex);
	aasworld.portalindex = NULL;
	aasworld.portalindexsize = 0;
	if (aasworld.clusters) FreeMemory(aasworld.clusters);
	aasworld.clusters = NULL;
	aasworld.numclusters = 0;
	//
	aasworld.loaded = qfalse;
	aasworld.initialized = qfalse;
	aasworld.savefile = qfalse;
}