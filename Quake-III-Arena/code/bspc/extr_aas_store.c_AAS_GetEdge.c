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
typedef  int /*<<< orphan*/  vec3_t ;
typedef  int qboolean ;
struct TYPE_6__ {int numedges; TYPE_1__* edges; } ;
struct TYPE_5__ {int max_edges; } ;
struct TYPE_4__ {int* v; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_AddEdgeToHash (int) ; 
 scalar_t__ AAS_FindHashedEdge (int,int,int*) ; 
 int AAS_GetVertex (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  Error (char*,int) ; 
 TYPE_3__ aasworld ; 
 TYPE_2__ max_aas ; 

qboolean AAS_GetEdge(vec3_t v1, vec3_t v2, int *edgenum)
{
	int v1num, v2num;
	qboolean found;

	//the first edge is a dummy
	if (aasworld.numedges == 0) aasworld.numedges = 1;

	found = AAS_GetVertex(v1, &v1num);
	found &= AAS_GetVertex(v2, &v2num);
	//if one of the vertexes was outside the valid range
	if (v1num == -1 || v2num == -1)
	{
		*edgenum = 0;
		return true;
	} //end if
	//if both vertexes are the same or snapped onto each other
	if (v1num == v2num)
	{
		*edgenum = 0;
		return true;
	} //end if
	//if both vertexes where already stored
	if (found)
	{
#ifdef EDGE_HASHING
		if (AAS_FindHashedEdge(v1num, v2num, edgenum)) return true;
#else
		int i;
		for (i = 1; i < aasworld.numedges; i++)
		{
			if (aasworld.edges[i].v[0] == v1num)
			{
				if (aasworld.edges[i].v[1] == v2num)
				{
					*edgenum = i;
					return true;
				} //end if
			} //end if
			else if (aasworld.edges[i].v[1] == v1num)
			{
				if (aasworld.edges[i].v[0] == v2num)
				{
					//negative for a reversed edge
					*edgenum = -i;
					return true;
				} //end if
			} //end else
		} //end for
#endif //EDGE_HASHING
	} //end if
	if (aasworld.numedges >= max_aas.max_edges)
	{
		Error("AAS_MAX_EDGES = %d", max_aas.max_edges);
	} //end if
	aasworld.edges[aasworld.numedges].v[0] = v1num;
	aasworld.edges[aasworld.numedges].v[1] = v2num;
	*edgenum = aasworld.numedges;
#ifdef EDGE_HASHING
	AAS_AddEdgeToHash(*edgenum);
#endif //EDGE_HASHING
	aasworld.numedges++;
	return false;
}