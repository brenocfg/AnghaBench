#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
struct TYPE_13__ {scalar_t__ surfaceType; } ;
typedef  TYPE_1__ q3_dsurface_t ;
struct TYPE_14__ {int dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_2__ q3_dplane_t ;
struct TYPE_15__ {size_t planeNum; } ;
typedef  TYPE_3__ q3_dbrushside_t ;
struct TYPE_16__ {int numSides; int firstSide; } ;
typedef  TYPE_4__ q3_dbrush_t ;
struct TYPE_17__ {int dist; int /*<<< orphan*/  normal; } ;

/* Variables and functions */
 float DotProduct (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FreeWinding (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Log_Print (char*,...) ; 
 scalar_t__ MST_PLANAR ; 
 int /*<<< orphan*/ * Q3_BrushSideWinding (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  Q3_CreatePlanarSurfacePlanes () ; 
 scalar_t__ Q3_FaceOnWinding (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Q3_MAX_MAP_BRUSHSIDES ; 
 int WE_NOTENOUGHPOINTS ; 
 int WE_POINTBOGUSRANGE ; 
 int WE_SMALLAREA ; 
 int WindingArea (int /*<<< orphan*/ *) ; 
 int WindingError (int /*<<< orphan*/ *) ; 
 scalar_t__ WindingIsTiny (int /*<<< orphan*/ *) ; 
 int fabs (int) ; 
 scalar_t__ forcesidesvisible ; 
 int /*<<< orphan*/  memset (int*,int,int /*<<< orphan*/ ) ; 
 TYPE_4__* q3_dbrushes ; 
 TYPE_3__* q3_dbrushsides ; 
 int* q3_dbrushsidetextured ; 
 TYPE_7__* q3_dplanes ; 
 TYPE_1__* q3_drawSurfaces ; 
 int q3_numDrawSurfaces ; 
 int q3_numbrushes ; 
 int q3_numbrushsides ; 
 TYPE_2__* q3_surfaceplanes ; 
 int /*<<< orphan*/  qprintf (char*,int) ; 

void Q3_FindVisibleBrushSides(void)
{
	int i, j, k, we, numtextured, numsides;
	float dot;
	q3_dplane_t *plane;
	q3_dbrushside_t *brushside;
	q3_dbrush_t *brush;
	q3_dsurface_t *surface;
	winding_t *w;

	memset(q3_dbrushsidetextured, false, Q3_MAX_MAP_BRUSHSIDES);
	//
	numsides = 0;
	//create planes for the planar surfaces
	Q3_CreatePlanarSurfacePlanes();
	Log_Print("searching visible brush sides...\n");
	Log_Print("%6d brush sides", numsides);
	//go over all the brushes
	for (i = 0; i < q3_numbrushes; i++)
	{
		brush = &q3_dbrushes[i];
		//go over all the sides of the brush
		for (j = 0; j < brush->numSides; j++)
		{
			qprintf("\r%6d", numsides++);
			brushside = &q3_dbrushsides[brush->firstSide + j];
			//
			w = Q3_BrushSideWinding(brush, brushside);
			if (!w)
			{
				q3_dbrushsidetextured[brush->firstSide + j] = true;
				continue;
			} //end if
			else
			{
				//RemoveEqualPoints(w, 0.2);
				if (WindingIsTiny(w))
				{
					FreeWinding(w);
					q3_dbrushsidetextured[brush->firstSide + j] = true;
					continue;
				} //end if
				else
				{
					we = WindingError(w);
					if (we == WE_NOTENOUGHPOINTS
						|| we == WE_SMALLAREA
						|| we == WE_POINTBOGUSRANGE
//						|| we == WE_NONCONVEX
						)
					{
						FreeWinding(w);
						q3_dbrushsidetextured[brush->firstSide + j] = true;
						continue;
					} //end if
				} //end else
			} //end else
			if (WindingArea(w) < 20)
			{
				q3_dbrushsidetextured[brush->firstSide + j] = true;
				continue;
			} //end if
			//find a face for texturing this brush
			for (k = 0; k < q3_numDrawSurfaces; k++)
			{
				surface = &q3_drawSurfaces[k];
				if (surface->surfaceType != MST_PLANAR) continue;
				//
				//Q3_SurfacePlane(surface, plane.normal, &plane.dist);
				plane = &q3_surfaceplanes[k];
				//the surface plane and the brush side plane should be pretty much the same
				if (fabs(fabs(plane->dist) - fabs(q3_dplanes[brushside->planeNum].dist)) > 5) continue;
				dot = DotProduct(plane->normal, q3_dplanes[brushside->planeNum].normal);
				if (dot > -0.9 && dot < 0.9) continue;
				//if the face is partly or totally on the brush side
				if (Q3_FaceOnWinding(surface, w))
				{
					q3_dbrushsidetextured[brush->firstSide + j] = true;
					//Log_Write("Q3_FaceOnWinding");
					break;
				} //end if
			} //end for
			FreeWinding(w);
		} //end for
	} //end for
	qprintf("\r%6d brush sides\n", numsides);
	numtextured = 0;
	for (i = 0; i < q3_numbrushsides; i++)
	{
		if (forcesidesvisible) q3_dbrushsidetextured[i] = true;
		if (q3_dbrushsidetextured[i]) numtextured++;
	} //end for
	Log_Print("%d brush sides textured out of %d\n", numtextured, q3_numbrushsides);
}