#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */

void AddBackSides( void ) {
/*
	bspbrush_t	*b;
	int			i, originalSides;
	side_t		*s;
	side_t		*newSide;

	b = buildBrush;
	originalSides = b->numsides;
	for ( i = 0 ; i < originalSides ; i++ ) {
		s = &b->sides[i];
		if ( !s->shaderInfo ) {
			continue;
		}
		if ( !(s->shaderInfo->contents & CONTENTS_FOG) ) {
			continue;
		}

		// duplicate the up-facing side
		if ( mapplanes[ s->planenum ].normal[2] == 1 ) {
			newSide = &b->sides[ b->numsides ];
			b->numsides++;

			*newSide = *s;
			newSide->backSide = qtrue;
			newSide->planenum = s->planenum ^ 1;	// opposite side
		}
	}
*/
}