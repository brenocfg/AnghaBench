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
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_7__ {float dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_1__ plane_t ;
struct TYPE_8__ {size_t planenum; TYPE_3__* drawSurfReferences; scalar_t__ opaque; struct TYPE_8__** children; } ;
typedef  TYPE_2__ node_t ;
typedef  int /*<<< orphan*/  mapDrawSurface_t ;
struct TYPE_9__ {scalar_t__ outputNumber; struct TYPE_9__* nextRef; } ;
typedef  TYPE_3__ drawSurfRef_t ;

/* Variables and functions */
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float ON_EPSILON ; 
 size_t PLANENUM_LEAF ; 
 TYPE_3__* malloc (int) ; 
 TYPE_1__* mapplanes ; 
 scalar_t__ numDrawSurfaces ; 

int FilterMapDrawSurfIntoTree( vec3_t point, mapDrawSurface_t *ds, node_t *node ) {
	drawSurfRef_t	*dsr;
	float			d;
	plane_t			*plane;
	int				c;

	if ( node->planenum != PLANENUM_LEAF ) {
		plane = &mapplanes[ node->planenum ];
		d = DotProduct( point, plane->normal ) - plane->dist;
		c = 0;
		if ( d >= -ON_EPSILON ) {
			c += FilterMapDrawSurfIntoTree( point, ds, node->children[0] );
		}
		if ( d <= ON_EPSILON ) {
			c += FilterMapDrawSurfIntoTree( point, ds, node->children[1] );
		}
		return c;
	}

	// if opaque leaf, don't add
	if ( node->opaque ) {
		return 0;
	}

	// add the drawsurf if it hasn't been already
	for ( dsr = node->drawSurfReferences ; dsr ; dsr = dsr->nextRef ) {
		if ( dsr->outputNumber == numDrawSurfaces ) {
			return 0;		// already referenced
		}
	}

	dsr = malloc( sizeof( *dsr ) );
	dsr->outputNumber = numDrawSurfaces;
	dsr->nextRef = node->drawSurfReferences;
	node->drawSurfReferences = dsr;
	return 1;
}