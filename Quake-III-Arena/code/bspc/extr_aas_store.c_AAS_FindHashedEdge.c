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
typedef  int qboolean ;
struct TYPE_3__ {int* v; } ;
typedef  TYPE_1__ aas_edge_t ;
struct TYPE_4__ {TYPE_1__* edges; } ;

/* Variables and functions */
 int AAS_HashEdge (int,int) ; 
 int* aas_edgechain ; 
 int* aas_hashedges ; 
 TYPE_2__ aasworld ; 

qboolean AAS_FindHashedEdge(int v1num, int v2num, int *edgenum)
{
	int e, hash;
	aas_edge_t *edge;

	hash = AAS_HashEdge(v1num, v2num);
	for (e = aas_hashedges[hash]; e >= 0; e = aas_edgechain[e])
	{
		edge = &aasworld.edges[e];
		if (edge->v[0] == v1num)
		{
			if (edge->v[1] == v2num)
			{
				*edgenum = e;
				return true;
			} //end if
		} //end if
		else if (edge->v[1] == v1num)
		{
			if (edge->v[0] == v2num)
			{
				//negative for a reversed edge
				*edgenum = -e;
				return true;
			} //end if
		} //end else
	} //end for
	return false;
}