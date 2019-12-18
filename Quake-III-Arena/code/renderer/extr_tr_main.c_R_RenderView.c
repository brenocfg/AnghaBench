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
struct TYPE_6__ {scalar_t__ viewportWidth; scalar_t__ viewportHeight; int /*<<< orphan*/  frameCount; int /*<<< orphan*/  frameSceneNum; } ;
typedef  TYPE_2__ viewParms_t ;
struct TYPE_5__ {int numDrawSurfs; scalar_t__ drawSurfs; } ;
struct TYPE_7__ {TYPE_1__ refdef; int /*<<< orphan*/  viewCount; int /*<<< orphan*/  frameCount; TYPE_2__ viewParms; int /*<<< orphan*/  frameSceneNum; } ;

/* Variables and functions */
 int /*<<< orphan*/  R_DebugGraphics () ; 
 int /*<<< orphan*/  R_GenerateDrawSurfs () ; 
 int /*<<< orphan*/  R_RotateForViewer () ; 
 int /*<<< orphan*/  R_SetupFrustum () ; 
 int /*<<< orphan*/  R_SortDrawSurfs (scalar_t__,int) ; 
 TYPE_3__ tr ; 

void R_RenderView (viewParms_t *parms) {
	int		firstDrawSurf;

	if ( parms->viewportWidth <= 0 || parms->viewportHeight <= 0 ) {
		return;
	}

	tr.viewCount++;

	tr.viewParms = *parms;
	tr.viewParms.frameSceneNum = tr.frameSceneNum;
	tr.viewParms.frameCount = tr.frameCount;

	firstDrawSurf = tr.refdef.numDrawSurfs;

	tr.viewCount++;

	// set viewParms.world
	R_RotateForViewer ();

	R_SetupFrustum ();

	R_GenerateDrawSurfs();

	R_SortDrawSurfs( tr.refdef.drawSurfs + firstDrawSurf, tr.refdef.numDrawSurfs - firstDrawSurf );

	// draw main system development information (surface outlines, etc)
	R_DebugGraphics();
}