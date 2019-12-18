#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
struct TYPE_12__ {int /*<<< orphan*/  headnode; } ;
typedef  TYPE_1__ tree_t ;
struct TYPE_13__ {int planenum; int /*<<< orphan*/ * visibleHull; scalar_t__ bevel; int /*<<< orphan*/ * winding; TYPE_3__* shaderInfo; } ;
typedef  TYPE_2__ side_t ;
struct TYPE_14__ {int surfaceFlags; int contents; scalar_t__ autosprite; } ;
typedef  TYPE_3__ shaderInfo_t ;
struct TYPE_15__ {TYPE_5__* brushes; } ;
typedef  TYPE_4__ entity_t ;
struct TYPE_16__ {int numsides; TYPE_2__* sides; struct TYPE_16__* next; } ;
typedef  TYPE_5__ bspbrush_t ;

/* Variables and functions */
 int CONTENTS_FOG ; 
 int /*<<< orphan*/  ClipSideIntoTree_r (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CopyWinding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DrawSurfaceForSide (TYPE_5__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Error (char*) ; 
 int /*<<< orphan*/ * ReverseWinding (int /*<<< orphan*/ *) ; 
 int SURF_NODRAW ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  qprintf (char*) ; 

void ClipSidesIntoTree( entity_t *e, tree_t *tree ) {
	bspbrush_t		*b;
	int				i;
	winding_t		*w;
	side_t			*side, *newSide;
	shaderInfo_t	*si;

	qprintf( "----- ClipSidesIntoTree -----\n");

	for ( b = e->brushes ; b ; b = b->next ) {
		for ( i = 0 ; i < b->numsides ; i++ ) {
			side = &b->sides[i];
			if ( !side->winding) {
				continue;
			}
			w = CopyWinding( side->winding );
			side->visibleHull = NULL;
			ClipSideIntoTree_r( w, side, tree->headnode );

			w = side->visibleHull;
			if ( !w ) {
				continue;
			}
			si = side->shaderInfo;
			if ( !si ) {
				continue;
			}
			// don't create faces for non-visible sides
			if ( si->surfaceFlags & SURF_NODRAW ) {
				continue;
			}

			// always use the original quad winding for auto sprites
			if ( side->shaderInfo->autosprite ) {
				w = side->winding;
			}
			//
			if ( side->bevel ) {
				Error( "monkey tried to create draw surface for brush bevel" );
			}
			// save this winding as a visible surface
			DrawSurfaceForSide( b, side, w );

			// make a back side for it if needed
			if ( !(si->contents & CONTENTS_FOG) ) {
				continue;
			}

			// duplicate the up-facing side
			w = ReverseWinding( w );
		
			newSide = malloc( sizeof( *side ) );
			*newSide = *side;
			newSide->visibleHull = w;
			newSide->planenum ^= 1;

			// save this winding as a visible surface
			DrawSurfaceForSide( b, newSide, w );

		}
	}
}