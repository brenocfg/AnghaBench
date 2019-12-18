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
typedef  int /*<<< orphan*/  mapDrawSurface_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 size_t MAX_MAP_DRAW_SURFS ; 
 int /*<<< orphan*/ * mapDrawSurfs ; 
 size_t numMapDrawSurfs ; 

mapDrawSurface_t	*AllocDrawSurf( void ) {
	mapDrawSurface_t	*ds;

	if ( numMapDrawSurfs >= MAX_MAP_DRAW_SURFS ) {
		Error( "MAX_MAP_DRAW_SURFS");
	}
	ds = &mapDrawSurfs[ numMapDrawSurfs ];
	numMapDrawSurfs++;

	return ds;
}