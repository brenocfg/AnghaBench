#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;

/* Type definitions */
struct TYPE_29__ {int /*<<< orphan*/  headnode; } ;
typedef  TYPE_1__ tree_t ;
typedef  int /*<<< orphan*/  qboolean ;
struct TYPE_30__ {int /*<<< orphan*/  brushes; scalar_t__ firstDrawSurf; } ;
typedef  TYPE_2__ entity_t ;
typedef  int /*<<< orphan*/  bspface_t ;

/* Variables and functions */
 int /*<<< orphan*/  AddTriangleModels (TYPE_1__*) ; 
 int /*<<< orphan*/  AllocateLightmaps (TYPE_2__*) ; 
 int /*<<< orphan*/  BeginModel () ; 
 int /*<<< orphan*/  ClipSidesIntoTree (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  EndModel (int /*<<< orphan*/ ) ; 
 TYPE_1__* FaceBSP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FillOutside (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FilterDetailBrushesIntoTree (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  FilterDrawsurfsIntoTree (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  FilterStructuralBrushesIntoTree (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  FixTJunctions (TYPE_2__*) ; 
 int /*<<< orphan*/  FloodAreas (TYPE_1__*) ; 
 scalar_t__ FloodEntities (TYPE_1__*) ; 
 int /*<<< orphan*/  FogDrawSurfs () ; 
 int /*<<< orphan*/  FreeTree (TYPE_1__*) ; 
 int /*<<< orphan*/  LeakFile (TYPE_1__*) ; 
 int /*<<< orphan*/ * MakeStructuralBspFaceList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MakeTreePortals (TYPE_1__*) ; 
 int /*<<< orphan*/ * MakeVisibleBspFaceList (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MergeSides (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  NumberClusters (TYPE_1__*) ; 
 int /*<<< orphan*/  PatchMapDrawSurfs (TYPE_2__*) ; 
 int /*<<< orphan*/  SubdivideDrawSurfs (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  WriteGLView (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WritePortalFile (TYPE_1__*) ; 
 int /*<<< orphan*/  _printf (char*) ; 
 TYPE_2__* entities ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ glview ; 
 scalar_t__ leaktest ; 
 int /*<<< orphan*/  nofog ; 
 int /*<<< orphan*/  nomerge ; 
 int /*<<< orphan*/  nosubdivide ; 
 int /*<<< orphan*/  notjunc ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 int /*<<< orphan*/  source ; 

void ProcessWorldModel( void ) {
	entity_t	*e;
	tree_t		*tree;
	bspface_t	*faces;
	qboolean	leaked;

	BeginModel();

	e = &entities[0];
	e->firstDrawSurf = 0;//numMapDrawSurfs;

	// check for patches with adjacent edges that need to LOD together
	PatchMapDrawSurfs( e );

	// build an initial bsp tree using all of the sides
	// of all of the structural brushes
	faces = MakeStructuralBspFaceList ( entities[0].brushes );
	tree = FaceBSP( faces );
	MakeTreePortals (tree);
	FilterStructuralBrushesIntoTree( e, tree );

	// see if the bsp is completely enclosed
	if ( FloodEntities (tree) ) {
		// rebuild a better bsp tree using only the
		// sides that are visible from the inside
		FillOutside (tree->headnode);

		// chop the sides to the convex hull of
		// their visible fragments, giving us the smallest
		// polygons 
		ClipSidesIntoTree( e, tree );

		faces = MakeVisibleBspFaceList( entities[0].brushes );
		FreeTree (tree);
		tree = FaceBSP( faces );
		MakeTreePortals( tree );
		FilterStructuralBrushesIntoTree( e, tree );
		leaked = qfalse;
	} else {
		_printf ("**********************\n");
		_printf ("******* leaked *******\n");
		_printf ("**********************\n");
		LeakFile (tree);
		if ( leaktest ) {
			_printf ("--- MAP LEAKED, ABORTING LEAKTEST ---\n");
			exit (0);
		}
		leaked = qtrue;

		// chop the sides to the convex hull of
		// their visible fragments, giving us the smallest
		// polygons 
		ClipSidesIntoTree( e, tree );
	}

	// save out information for visibility processing
	NumberClusters( tree );
	if ( !leaked ) {
		WritePortalFile( tree );
	}
	if ( glview ) {
		// dump the portals for debugging
		WriteGLView( tree, source );
	}
	FloodAreas (tree);

	// add references to the detail brushes
	FilterDetailBrushesIntoTree( e, tree );

	// create drawsurfs for triangle models
	AddTriangleModels( tree );

	// drawsurfs that cross fog boundaries will need to
	// be split along the bound
	if ( !nofog ) {
		FogDrawSurfs();		// may fragment drawsurfs
	}

	// subdivide each drawsurf as required by shader tesselation
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

	EndModel( tree->headnode );

	FreeTree (tree);
}