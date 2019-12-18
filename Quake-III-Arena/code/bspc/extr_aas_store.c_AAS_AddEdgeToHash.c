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
struct TYPE_3__ {int /*<<< orphan*/ * v; } ;
typedef  TYPE_1__ aas_edge_t ;
struct TYPE_4__ {TYPE_1__* edges; } ;

/* Variables and functions */
 int AAS_HashEdge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* aas_edgechain ; 
 int* aas_hashedges ; 
 TYPE_2__ aasworld ; 

void AAS_AddEdgeToHash(int edgenum)
{
	int hash;
	aas_edge_t *edge;

	edge = &aasworld.edges[edgenum];

	hash = AAS_HashEdge(edge->v[0], edge->v[1]);

	aas_edgechain[edgenum] = aas_hashedges[hash];
	aas_hashedges[hash] = edgenum;
}