#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__* vec3_t ;
struct TYPE_5__ {int /*<<< orphan*/  maxs; int /*<<< orphan*/  mins; struct TYPE_5__* next; } ;
typedef  TYPE_1__ bspbrush_t ;
struct TYPE_6__ {TYPE_1__* brushes; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddPointToBounds (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  ClearBounds (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  Error (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  GetVectorForKey (TYPE_2__*,char*,scalar_t__*) ; 
 char* ValueForKey (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  VectorSubtract (scalar_t__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ floor (scalar_t__) ; 
 TYPE_2__* mapent ; 

void CalcTerrainSize( vec3_t mins, vec3_t maxs, vec3_t size ) {
	bspbrush_t	*brush;
	int			i;
	const char  *key;

	// calculate the size of the terrain
	ClearBounds( mins, maxs );
	for( brush = mapent->brushes; brush != NULL; brush = brush->next ) {
		AddPointToBounds( brush->mins, mins, maxs );
		AddPointToBounds( brush->maxs, mins, maxs );
	}

	key = ValueForKey( mapent, "min" ); 
	if ( key[ 0 ] ) {
		GetVectorForKey( mapent, "min", mins );
	}

	key = ValueForKey( mapent, "max" ); 
	if ( key[ 0 ] ) {
		GetVectorForKey( mapent, "max", maxs );
	}

	for( i = 0; i < 3; i++ ) {
		mins[ i ] =  floor( mins[ i ] + 0.1 );
		maxs[ i ] =  floor( maxs[ i ] + 0.1 );
	}

	VectorSubtract( maxs, mins, size );

	if ( ( size[ 0 ] <= 0 ) || ( size[ 1 ] <= 0 ) ) {
		Error ("CalcTerrainSize: Invalid terrain size: %fx%f", size[ 0 ], size[ 1 ] );
	}
}