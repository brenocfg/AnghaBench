#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {TYPE_2__* headnode; } ;
typedef  TYPE_1__ tree_t ;
struct TYPE_24__ {TYPE_4__* brushlist; int /*<<< orphan*/  planenum; } ;
typedef  TYPE_2__ node_t ;
struct TYPE_25__ {TYPE_4__* brushes; int /*<<< orphan*/  firstDrawSurf; } ;
typedef  TYPE_3__ entity_t ;
struct TYPE_26__ {struct TYPE_26__* next; } ;
typedef  TYPE_4__ bspbrush_t ;

/* Variables and functions */
 TYPE_2__* AllocNode () ; 
 TYPE_1__* AllocTree () ; 
 int /*<<< orphan*/  AllocateLightmaps (TYPE_3__*) ; 
 int /*<<< orphan*/  BeginModel () ; 
 int /*<<< orphan*/  ClipSidesIntoTree (TYPE_3__*,TYPE_1__*) ; 
 TYPE_4__* CopyBrush (TYPE_4__*) ; 
 int /*<<< orphan*/  EndModel (TYPE_2__*) ; 
 int /*<<< orphan*/  FilterDrawsurfsIntoTree (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  FixTJunctions (TYPE_3__*) ; 
 int /*<<< orphan*/  FreeTree (TYPE_1__*) ; 
 int /*<<< orphan*/  MergeSides (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  PLANENUM_LEAF ; 
 int /*<<< orphan*/  PatchMapDrawSurfs (TYPE_3__*) ; 
 int /*<<< orphan*/  SubdivideDrawSurfs (TYPE_3__*,TYPE_1__*) ; 
 TYPE_3__* entities ; 
 size_t entity_num ; 
 int /*<<< orphan*/  nomerge ; 
 int /*<<< orphan*/  nosubdivide ; 
 int /*<<< orphan*/  notjunc ; 
 int /*<<< orphan*/  numMapDrawSurfs ; 

void ProcessSubModel( void ) {
	entity_t	*e;
	tree_t		*tree;
	bspbrush_t	*b, *bc;
	node_t		*node;

	BeginModel ();

	e = &entities[entity_num];
	e->firstDrawSurf = numMapDrawSurfs;

	PatchMapDrawSurfs( e );

	// just put all the brushes in an empty leaf
	// FIXME: patches?
	node = AllocNode();
	node->planenum = PLANENUM_LEAF;
	for ( b = e->brushes ; b ; b = b->next ) {
		bc = CopyBrush( b );
		bc->next = node->brushlist;
		node->brushlist = bc;
	}

	tree = AllocTree();
	tree->headnode = node;

	ClipSidesIntoTree( e, tree );

	// subdivide each drawsurf as required by shader tesselation or fog
	if ( !nosubdivide ) {
		SubdivideDrawSurfs( e, tree );
	}

	// merge together all common shaders on the same plane and remove 
	// all colinear points, so extra tjunctions won't be generated
	if ( !nomerge ) {
		MergeSides( e, tree );		// !@# testing
	}

	// add in any vertexes required to fix tjunctions
	if ( !notjunc ) {
		FixTJunctions( e );
	}

	// allocate lightmaps for faces and patches
	AllocateLightmaps( e );

	// add references to the final drawsurfs in the apropriate clusters
	FilterDrawsurfsIntoTree( e, tree );

	EndModel ( node );

	FreeTree( tree );
}