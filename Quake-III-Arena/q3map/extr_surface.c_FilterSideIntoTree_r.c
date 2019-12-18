#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
struct TYPE_9__ {int planenum; } ;
typedef  TYPE_1__ side_t ;
struct TYPE_10__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ plane_t ;
struct TYPE_11__ {int planenum; TYPE_4__* drawSurfReferences; scalar_t__ opaque; struct TYPE_11__** children; } ;
typedef  TYPE_3__ node_t ;
typedef  int /*<<< orphan*/  mapDrawSurface_t ;
struct TYPE_12__ {struct TYPE_12__* nextRef; int /*<<< orphan*/  outputNumber; } ;
typedef  TYPE_4__ drawSurfRef_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClipWindingEpsilon (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  FreeWinding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ON_EPSILON ; 
 int PLANENUM_LEAF ; 
 TYPE_4__* malloc (int) ; 
 TYPE_2__* mapplanes ; 
 int /*<<< orphan*/  numDrawSurfaces ; 

int FilterSideIntoTree_r( winding_t *w, side_t *side, mapDrawSurface_t *ds, node_t *node ) {
	drawSurfRef_t	*dsr;
	plane_t			*plane;
	winding_t		*front, *back;
	int				total;

	if ( !w ) {
		return 0;
	}

	if ( node->planenum != PLANENUM_LEAF ) {
		if ( side->planenum == node->planenum ) {
			return FilterSideIntoTree_r( w, side, ds, node->children[0] );
		}
		if ( side->planenum == ( node->planenum ^ 1) ) {
			return FilterSideIntoTree_r( w, side, ds, node->children[1] );
		}

		plane = &mapplanes[ node->planenum ];
		ClipWindingEpsilon ( w, plane->normal, plane->dist,
				ON_EPSILON, &front, &back );

		total = FilterSideIntoTree_r( front, side, ds, node->children[0] );
		total += FilterSideIntoTree_r( back, side, ds, node->children[1] );

		FreeWinding( w );
		return total;
	}

	// if opaque leaf, don't add
	if ( node->opaque ) {
		return 0;
	}

	dsr = malloc( sizeof( *dsr ) );
	dsr->outputNumber = numDrawSurfaces;
	dsr->nextRef = node->drawSurfReferences;
	node->drawSurfReferences = dsr;

	FreeWinding( w );
	return 1;
}