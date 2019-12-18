#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  srfTriangles_t ;
typedef  int /*<<< orphan*/  srfSurfaceFace_t ;
typedef  int /*<<< orphan*/  srfGridMesh_t ;
struct TYPE_6__ {scalar_t__* data; } ;
typedef  TYPE_2__ msurface_t ;
struct TYPE_5__ {int /*<<< orphan*/  c_dlightSurfaces; } ;
struct TYPE_7__ {TYPE_1__ pc; } ;

/* Variables and functions */
 int R_DlightFace (int /*<<< orphan*/ *,int) ; 
 int R_DlightGrid (int /*<<< orphan*/ *,int) ; 
 int R_DlightTrisurf (int /*<<< orphan*/ *,int) ; 
 scalar_t__ SF_FACE ; 
 scalar_t__ SF_GRID ; 
 scalar_t__ SF_TRIANGLES ; 
 TYPE_3__ tr ; 

__attribute__((used)) static int R_DlightSurface( msurface_t *surf, int dlightBits ) {
	if ( *surf->data == SF_FACE ) {
		dlightBits = R_DlightFace( (srfSurfaceFace_t *)surf->data, dlightBits );
	} else if ( *surf->data == SF_GRID ) {
		dlightBits = R_DlightGrid( (srfGridMesh_t *)surf->data, dlightBits );
	} else if ( *surf->data == SF_TRIANGLES ) {
		dlightBits = R_DlightTrisurf( (srfTriangles_t *)surf->data, dlightBits );
	} else {
		dlightBits = 0;
	}

	if ( dlightBits ) {
		tr.pc.c_dlightSurfaces++;
	}

	return dlightBits;
}