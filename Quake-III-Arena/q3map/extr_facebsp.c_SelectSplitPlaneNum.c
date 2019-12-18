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
typedef  int* vec3_t ;
struct TYPE_7__ {int type; int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_1__ plane_t ;
struct TYPE_8__ {int* mins; float* maxs; } ;
typedef  TYPE_2__ node_t ;
struct TYPE_9__ {size_t planenum; scalar_t__ hint; scalar_t__ priority; int /*<<< orphan*/  w; void* checked; struct TYPE_9__* next; } ;
typedef  TYPE_3__ bspface_t ;

/* Variables and functions */
 int BLOCK_SIZE ; 
 int FindFloatPlane (int*,float) ; 
 int SIDE_BACK ; 
 int SIDE_CROSS ; 
 int SIDE_FRONT ; 
 int /*<<< orphan*/  VectorClear (int*) ; 
 int WindingOnPlaneSide (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int floor (int) ; 
 void* hintsplit ; 
 TYPE_1__* mapplanes ; 
 void* qfalse ; 
 void* qtrue ; 

int SelectSplitPlaneNum( node_t *node, bspface_t *list ) {
	bspface_t	*split;
	bspface_t	*check;
	bspface_t	*bestSplit;
	int			splits, facing, front, back;
	int			side;
	plane_t		*plane;
	int			value, bestValue;
	int			i;
	vec3_t		normal;
	float		dist;
	int			planenum;

	hintsplit = qfalse;
	// if it is crossing a 1k block boundary, force a split
	for ( i = 0 ; i < 2 ; i++ ) {
		dist = BLOCK_SIZE * ( floor( node->mins[i] / BLOCK_SIZE ) + 1 );	
		if ( node->maxs[i] > dist ) {
			VectorClear( normal );
			normal[i] = 1;
			planenum = FindFloatPlane( normal, dist );
			return planenum;
		}
	}

	// pick one of the face planes
	bestValue = -99999;
	bestSplit = list;

	for ( split = list ; split ; split = split->next ) {
		split->checked = qfalse;
	}

	for ( split = list ; split ; split = split->next ) {
		if ( split->checked ) {
			continue;
		}
		plane = &mapplanes[ split->planenum ];
		splits = 0;
		facing = 0;
		front = 0;
		back = 0;
		for ( check = list ; check ; check = check->next ) {
			if ( check->planenum == split->planenum ) {
				facing++;
				check->checked = qtrue;	// won't need to test this plane again
				continue;
			}
			side = WindingOnPlaneSide( check->w, plane->normal, plane->dist );
			if ( side == SIDE_CROSS ) {
				splits++;
			} else if ( side == SIDE_FRONT ) {
				front++;
			} else if ( side == SIDE_BACK ) {
				back++;
			}
		}
		value =  5*facing - 5*splits; // - abs(front-back);
		if ( plane->type < 3 ) {
			value+=5;		// axial is better
		}
		value += split->priority;		// prioritize hints higher

		if ( value > bestValue ) {
			bestValue = value;
			bestSplit = split;
		}
	}

	if ( bestValue == -99999 ) {
		return -1;
	}

	if (bestSplit->hint)
		hintsplit = qtrue;

	return bestSplit->planenum;
}