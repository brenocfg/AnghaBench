#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec3_t ;
struct TYPE_13__ {int dist; int* normal; } ;
typedef  TYPE_1__ aas_plane_t ;
struct TYPE_14__ {int areanum; int* start; int* end; struct TYPE_14__* next; scalar_t__ traveltime; scalar_t__ traveltype; scalar_t__ edgenum; scalar_t__ facenum; } ;
typedef  TYPE_2__ aas_lreachability_t ;
struct TYPE_15__ {int faceflags; size_t planenum; int numedges; int firstedge; } ;
typedef  TYPE_3__ aas_face_t ;
struct TYPE_16__ {size_t* v; } ;
typedef  TYPE_4__ aas_edge_t ;
struct TYPE_17__ {int numfaces; int firstface; } ;
typedef  TYPE_5__ aas_area_t ;
struct TYPE_19__ {int /*<<< orphan*/  phys_jumpvel; } ;
struct TYPE_18__ {int numareas; int* faceindex; int* edgeindex; float** vertexes; TYPE_4__* edges; TYPE_1__* planes; TYPE_3__* faces; TYPE_5__* areas; } ;

/* Variables and functions */
 TYPE_2__* AAS_AllocReachability () ; 
 float AAS_ClosestEdgePoints (float*,float*,float*,float*,TYPE_1__*,TYPE_1__*,int*,int*,int*,int*,float) ; 
 int /*<<< orphan*/  AAS_HorizontalVelocityForJump (int /*<<< orphan*/ ,int*,int*,float*) ; 
 int AAS_MaxJumpDistance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AAS_PermanentLine (int*,int*,int) ; 
 int /*<<< orphan*/  AAS_PointInsideFace (int,int*,float) ; 
 int DotProduct (int*,int*) ; 
 int FACE_GROUND ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 float VectorLength (int*) ; 
 int /*<<< orphan*/  VectorMiddle (int*,int*,int*) ; 
 int /*<<< orphan*/  VectorSubtract (int*,int*,int*) ; 
 TYPE_7__ aassettings ; 
 TYPE_6__ aasworld ; 
 size_t abs (int) ; 

aas_lreachability_t *AAS_FindFaceReachabilities(vec3_t *facepoints, int numpoints, aas_plane_t *plane, int towardsface)
{
	int i, j, k, l;
	int facenum, edgenum, bestfacenum;
	float *v1, *v2, *v3, *v4;
	float bestdist, speed, hordist, dist;
	vec3_t beststart, beststart2, bestend, bestend2, tmp, hordir, testpoint;
	aas_lreachability_t *lreach, *lreachabilities;
	aas_area_t *area;
	aas_face_t *face;
	aas_edge_t *edge;
	aas_plane_t *faceplane, *bestfaceplane;

	//
	lreachabilities = NULL;
	bestfacenum = 0;
	bestfaceplane = NULL;
	//
	for (i = 1; i < aasworld.numareas; i++)
	{
		area = &aasworld.areas[i];
		// get the shortest distance between one of the func_bob start edges and
		// one of the face edges of area1
		bestdist = 999999;
		for (j = 0; j < area->numfaces; j++)
		{
			facenum = aasworld.faceindex[area->firstface + j];
			face = &aasworld.faces[abs(facenum)];
			//if not a ground face
			if (!(face->faceflags & FACE_GROUND)) continue;
			//get the ground planes
			faceplane = &aasworld.planes[face->planenum];
			//
			for (k = 0; k < face->numedges; k++)
			{
				edgenum = abs(aasworld.edgeindex[face->firstedge + k]);
				edge = &aasworld.edges[edgenum];
				//calculate the minimum distance between the two edges
				v1 = aasworld.vertexes[edge->v[0]];
				v2 = aasworld.vertexes[edge->v[1]];
				//
				for (l = 0; l < numpoints; l++)
				{
					v3 = facepoints[l];
					v4 = facepoints[(l+1) % numpoints];
					dist = AAS_ClosestEdgePoints(v1, v2, v3, v4, faceplane, plane,
													beststart, bestend,
													beststart2, bestend2, bestdist);
					if (dist < bestdist)
					{
						bestfacenum = facenum;
						bestfaceplane = faceplane;
						bestdist = dist;
					} //end if
				} //end for
			} //end for
		} //end for
		//
		if (bestdist > 192) continue;
		//
		VectorMiddle(beststart, beststart2, beststart);
		VectorMiddle(bestend, bestend2, bestend);
		//
		if (!towardsface)
		{
			VectorCopy(beststart, tmp);
			VectorCopy(bestend, beststart);
			VectorCopy(tmp, bestend);
		} //end if
		//
		VectorSubtract(bestend, beststart, hordir);
		hordir[2] = 0;
		hordist = VectorLength(hordir);
		//
		if (hordist > 2 * AAS_MaxJumpDistance(aassettings.phys_jumpvel)) continue;
		//the end point should not be significantly higher than the start point
		if (bestend[2] - 32 > beststart[2]) continue;
		//don't fall down too far
		if (bestend[2] < beststart[2] - 128) continue;
		//the distance should not be too far
		if (hordist > 32)
		{
			//check for walk off ledge
			if (!AAS_HorizontalVelocityForJump(0, beststart, bestend, &speed)) continue;
		} //end if
		//
		beststart[2] += 1;
		bestend[2] += 1;
		//
		if (towardsface) VectorCopy(bestend, testpoint);
		else VectorCopy(beststart, testpoint);
		testpoint[2] = 0;
		testpoint[2] = (bestfaceplane->dist - DotProduct(bestfaceplane->normal, testpoint)) / bestfaceplane->normal[2];
		//
		if (!AAS_PointInsideFace(bestfacenum, testpoint, 0.1f))
		{
			//if the faces are not overlapping then only go down
			if (bestend[2] - 16 > beststart[2]) continue;
		} //end if
		lreach = AAS_AllocReachability();
		if (!lreach) return lreachabilities;
		lreach->areanum = i;
		lreach->facenum = 0;
		lreach->edgenum = 0;
		VectorCopy(beststart, lreach->start);
		VectorCopy(bestend, lreach->end);
		lreach->traveltype = 0;
		lreach->traveltime = 0;
		lreach->next = lreachabilities;
		lreachabilities = lreach;
#ifndef BSPC
		if (towardsface) AAS_PermanentLine(lreach->start, lreach->end, 1);
		else AAS_PermanentLine(lreach->start, lreach->end, 2);
#endif
	} //end for
	return lreachabilities;
}