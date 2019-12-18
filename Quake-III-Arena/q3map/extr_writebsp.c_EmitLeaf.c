#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* drawSurfReferences; scalar_t__ opaque; TYPE_5__* brushlist; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  area; int /*<<< orphan*/  cluster; } ;
typedef  TYPE_2__ node_t ;
struct TYPE_10__ {int /*<<< orphan*/  outputNumber; struct TYPE_10__* nextRef; } ;
typedef  TYPE_3__ drawSurfRef_t ;
struct TYPE_11__ {size_t firstLeafBrush; size_t numLeafBrushes; size_t firstLeafSurface; size_t numLeafSurfaces; int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; int /*<<< orphan*/  area; int /*<<< orphan*/  cluster; } ;
typedef  TYPE_4__ dleaf_t ;
struct TYPE_12__ {TYPE_1__* original; struct TYPE_12__* next; } ;
typedef  TYPE_5__ bspbrush_t ;
struct TYPE_8__ {int /*<<< orphan*/  outputNumber; } ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 size_t MAX_MAP_LEAFBRUSHES ; 
 size_t MAX_MAP_LEAFFACES ; 
 size_t MAX_MAP_LEAFS ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dleafbrushes ; 
 TYPE_4__* dleafs ; 
 int /*<<< orphan*/ * dleafsurfaces ; 
 size_t numleafbrushes ; 
 size_t numleafs ; 
 size_t numleafsurfaces ; 

void EmitLeaf (node_t *node)
{
	dleaf_t				*leaf_p;
	bspbrush_t			*b;
	drawSurfRef_t		*dsr;

	// emit a leaf
	if (numleafs >= MAX_MAP_LEAFS)
		Error ("MAX_MAP_LEAFS");

	leaf_p = &dleafs[numleafs];
	numleafs++;

	leaf_p->cluster = node->cluster;
	leaf_p->area = node->area;

	//
	// write bounding box info
	//	
	VectorCopy (node->mins, leaf_p->mins);
	VectorCopy (node->maxs, leaf_p->maxs);
	
	//
	// write the leafbrushes
	//
	leaf_p->firstLeafBrush = numleafbrushes;
	for ( b = node->brushlist ; b ; b = b->next ) {
		if ( numleafbrushes >= MAX_MAP_LEAFBRUSHES ) {
			Error( "MAX_MAP_LEAFBRUSHES" );
		}
		dleafbrushes[numleafbrushes] = b->original->outputNumber;
		numleafbrushes++;
	}
	leaf_p->numLeafBrushes = numleafbrushes - leaf_p->firstLeafBrush;

	//
	// write the surfaces visible in this leaf
	//
	if ( node->opaque ) {
		return;		// no leaffaces in solids
	}
	
	// add the drawSurfRef_t drawsurfs
	leaf_p->firstLeafSurface = numleafsurfaces;
	for ( dsr = node->drawSurfReferences ; dsr ; dsr = dsr->nextRef ) {
		if ( numleafsurfaces >= MAX_MAP_LEAFFACES)
			Error ("MAX_MAP_LEAFFACES");
		dleafsurfaces[numleafsurfaces] = dsr->outputNumber;
		numleafsurfaces++;			
	}


	leaf_p->numLeafSurfaces = numleafsurfaces - leaf_p->firstLeafSurface;
}