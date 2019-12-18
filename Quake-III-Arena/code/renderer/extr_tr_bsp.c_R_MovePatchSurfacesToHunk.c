#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ surfaceType; int width; int height; struct TYPE_12__* heightLodError; struct TYPE_12__* widthLodError; } ;
typedef  TYPE_2__ srfGridMesh_t ;
typedef  int /*<<< orphan*/  drawVert_t ;
struct TYPE_14__ {TYPE_2__* (* Hunk_Alloc ) (int,int /*<<< orphan*/ ) ;} ;
struct TYPE_13__ {int numsurfaces; TYPE_1__* surfaces; } ;
struct TYPE_11__ {void* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  R_FreeSurfaceGridMesh (TYPE_2__*) ; 
 scalar_t__ SF_GRID ; 
 int /*<<< orphan*/  h_low ; 
 TYPE_7__ ri ; 
 TYPE_6__ s_worldData ; 
 TYPE_2__* stub1 (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* stub2 (int,int /*<<< orphan*/ ) ; 
 TYPE_2__* stub3 (int,int /*<<< orphan*/ ) ; 

void R_MovePatchSurfacesToHunk(void) {
	int i, size;
	srfGridMesh_t *grid, *hunkgrid;

	for ( i = 0; i < s_worldData.numsurfaces; i++ ) {
		//
		grid = (srfGridMesh_t *) s_worldData.surfaces[i].data;
		// if this surface is not a grid
		if ( grid->surfaceType != SF_GRID )
			continue;
		//
		size = (grid->width * grid->height - 1) * sizeof( drawVert_t ) + sizeof( *grid );
		hunkgrid = ri.Hunk_Alloc( size, h_low );
		Com_Memcpy(hunkgrid, grid, size);

		hunkgrid->widthLodError = ri.Hunk_Alloc( grid->width * 4, h_low );
		Com_Memcpy( hunkgrid->widthLodError, grid->widthLodError, grid->width * 4 );

		hunkgrid->heightLodError = ri.Hunk_Alloc( grid->height * 4, h_low );
		Com_Memcpy( grid->heightLodError, grid->heightLodError, grid->height * 4 );

		R_FreeSurfaceGridMesh( grid );

		s_worldData.surfaces[i].data = (void *) hunkgrid;
	}
}