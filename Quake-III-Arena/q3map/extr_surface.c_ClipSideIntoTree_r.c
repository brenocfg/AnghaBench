#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
struct TYPE_7__ {int planenum; int /*<<< orphan*/  visibleHull; } ;
typedef  TYPE_1__ side_t ;
struct TYPE_8__ {int /*<<< orphan*/  normal; int /*<<< orphan*/  dist; } ;
typedef  TYPE_2__ plane_t ;
struct TYPE_9__ {int planenum; int /*<<< orphan*/  opaque; struct TYPE_9__** children; } ;
typedef  TYPE_3__ node_t ;

/* Variables and functions */
 int /*<<< orphan*/  AddWindingToConvexHull (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClipWindingEpsilon (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  FreeWinding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ON_EPSILON ; 
 int PLANENUM_LEAF ; 
 TYPE_2__* mapplanes ; 

void ClipSideIntoTree_r( winding_t *w, side_t *side, node_t *node ) {
	plane_t			*plane;
	winding_t		*front, *back;

	if ( !w ) {
		return;
	}

	if ( node->planenum != PLANENUM_LEAF ) {
		if ( side->planenum == node->planenum ) {
			ClipSideIntoTree_r( w, side, node->children[0] );
			return;
		}
		if ( side->planenum == ( node->planenum ^ 1) ) {
			ClipSideIntoTree_r( w, side, node->children[1] );
			return;
		}

		plane = &mapplanes[ node->planenum ];
		ClipWindingEpsilon ( w, plane->normal, plane->dist,
				ON_EPSILON, &front, &back );
		FreeWinding( w );

		ClipSideIntoTree_r( front, side, node->children[0] );
		ClipSideIntoTree_r( back, side, node->children[1] );

		return;
	}

	// if opaque leaf, don't add
	if ( !node->opaque ) {
		AddWindingToConvexHull( w, &side->visibleHull, mapplanes[ side->planenum ].normal );
	}

	FreeWinding( w );
	return;
}