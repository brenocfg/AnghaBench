#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;

/* Type definitions */
typedef  int vec_t ;
typedef  int* vec3_t ;
struct TYPE_20__ {int flags; } ;
struct TYPE_22__ {int fraction; int* endpos; TYPE_3__ surface; } ;
typedef  TYPE_5__ bsp_trace_t ;
struct TYPE_23__ {int* endpos; int fraction; scalar_t__ startsolid; } ;
typedef  TYPE_6__ aas_trace_t ;
struct TYPE_24__ {int areanum; int facenum; int* start; int* end; struct TYPE_24__* next; scalar_t__ traveltime; int /*<<< orphan*/  traveltype; scalar_t__ edgenum; } ;
typedef  TYPE_7__ aas_lreachability_t ;
struct TYPE_25__ {int faceflags; size_t firstedge; size_t planenum; } ;
typedef  TYPE_8__ aas_face_t ;
struct TYPE_26__ {scalar_t__* maxs; scalar_t__* mins; int* center; int numfaces; int firstface; } ;
typedef  TYPE_9__ aas_area_t ;
struct TYPE_21__ {int contents; } ;
struct TYPE_19__ {int* normal; } ;
struct TYPE_18__ {size_t* v; } ;
struct TYPE_17__ {scalar_t__ rs_startgrapple; } ;
struct TYPE_16__ {int* faceindex; int** vertexes; int* edgeindex; TYPE_4__* areasettings; TYPE_2__* planes; TYPE_1__* edges; TYPE_8__* faces; TYPE_9__* areas; } ;

/* Variables and functions */
 TYPE_7__* AAS_AllocReachability () ; 
 int /*<<< orphan*/  AAS_AreaGrounded (int) ; 
 int AAS_AreaPresenceType (int) ; 
 scalar_t__ AAS_AreaSwim (int) ; 
 int /*<<< orphan*/  AAS_FaceCenter (int,int*) ; 
 scalar_t__ AAS_FallDamageDistance () ; 
 int AAS_PointAreaNum (int*) ; 
 int AAS_PointContents (int*) ; 
 scalar_t__ AAS_ReachabilityExists (int,int) ; 
 TYPE_5__ AAS_Trace (int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int AAS_TraceAreas (int*,int*,int*,int /*<<< orphan*/ *,int) ; 
 TYPE_6__ AAS_TraceClientBBox (int*,int*,int,int) ; 
 int AREACONTENTS_CLUSTERPORTAL ; 
 int AREACONTENTS_LAVA ; 
 int AREACONTENTS_SLIME ; 
 int CONTENTS_LAVA ; 
 int CONTENTS_SLIME ; 
 int /*<<< orphan*/  CONTENTS_SOLID ; 
 int CONTENTS_WATER ; 
 scalar_t__ DotProduct (int*,int*) ; 
 int FACE_SOLID ; 
 int /*<<< orphan*/  Log_Write (char*,int,int,int,int) ; 
 int M_PI ; 
 int PRESENCE_CROUCH ; 
 int PRESENCE_NORMAL ; 
 int SURF_SKY ; 
 int /*<<< orphan*/  TRAVEL_GRAPPLEHOOK ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 double VectorLength (int*) ; 
 int /*<<< orphan*/  VectorMA (int*,int,int*,int*) ; 
 int /*<<< orphan*/  VectorNormalize (int*) ; 
 int /*<<< orphan*/  VectorSubtract (int*,int*,int*) ; 
 TYPE_12__ aassettings ; 
 TYPE_11__ aasworld ; 
 size_t abs (int) ; 
 TYPE_7__** areareachability ; 
 int qfalse ; 
 int /*<<< orphan*/  reach_grapple ; 
 float tan (int) ; 

int AAS_Reachability_Grapple(int area1num, int area2num)
{
	int face2num, i, j, areanum, numareas, areas[20];
	float mingrappleangle, z, hordist;
	bsp_trace_t bsptrace;
	aas_trace_t trace;
	aas_face_t *face2;
	aas_area_t *area1, *area2;
	aas_lreachability_t *lreach;
	vec3_t areastart, facecenter, start, end, dir, down = {0, 0, -1};
	vec_t *v;

	//only grapple when on the ground or swimming
	if (!AAS_AreaGrounded(area1num) && !AAS_AreaSwim(area1num)) return qfalse;
	//don't grapple from a crouch area
	if (!(AAS_AreaPresenceType(area1num) & PRESENCE_NORMAL)) return qfalse;
	//NOTE: disabled area swim it doesn't work right
	if (AAS_AreaSwim(area1num)) return qfalse;
	//
	area1 = &aasworld.areas[area1num];
	area2 = &aasworld.areas[area2num];
	//don't grapple towards way lower areas
	if (area2->maxs[2] < area1->mins[2]) return qfalse;
	//
	VectorCopy(aasworld.areas[area1num].center, start);
	//if not a swim area
	if (!AAS_AreaSwim(area1num))
	{
		if (!AAS_PointAreaNum(start)) Log_Write("area %d center %f %f %f in solid?\r\n", area1num,
								start[0], start[1], start[2]);
		VectorCopy(start, end);
		end[2] -= 1000;
		trace = AAS_TraceClientBBox(start, end, PRESENCE_CROUCH, -1);
		if (trace.startsolid) return qfalse;
		VectorCopy(trace.endpos, areastart);
	} //end if
	else
	{
		if (!(AAS_PointContents(start) & (CONTENTS_LAVA|CONTENTS_SLIME|CONTENTS_WATER))) return qfalse;
	} //end else
	//
	//start is now the start point
	//
	for (i = 0; i < area2->numfaces; i++)
	{
		face2num = aasworld.faceindex[area2->firstface + i];
		face2 = &aasworld.faces[abs(face2num)];
		//if it is not a solid face
		if (!(face2->faceflags & FACE_SOLID)) continue;
		//direction towards the first vertex of the face
		v = aasworld.vertexes[aasworld.edges[abs(aasworld.edgeindex[face2->firstedge])].v[0]];
		VectorSubtract(v, areastart, dir);
		//if the face plane is facing away
		if (DotProduct(aasworld.planes[face2->planenum].normal, dir) > 0) continue;
		//get the center of the face
		AAS_FaceCenter(face2num, facecenter);
		//only go higher up with the grapple
		if (facecenter[2] < areastart[2] + 64) continue;
		//only use vertical faces or downward facing faces
		if (DotProduct(aasworld.planes[face2->planenum].normal, down) < 0) continue;
		//direction towards the face center
		VectorSubtract(facecenter, areastart, dir);
		//
		z = dir[2];
		dir[2] = 0;
		hordist = VectorLength(dir);
		if (!hordist) continue;
		//if too far
		if (hordist > 2000) continue;
		//check the minimal angle of the movement
		mingrappleangle = 15; //15 degrees
		if (z / hordist < tan(2 * M_PI * mingrappleangle / 360)) continue;
		//
		VectorCopy(facecenter, start);
		VectorMA(facecenter, -500, aasworld.planes[face2->planenum].normal, end);
		//
		bsptrace = AAS_Trace(start, NULL, NULL, end, 0, CONTENTS_SOLID);
		//the grapple won't stick to the sky and the grapple point should be near the AAS wall
		if ((bsptrace.surface.flags & SURF_SKY) || (bsptrace.fraction * 500 > 32)) continue;
		//trace a full bounding box from the area center on the ground to
		//the center of the face
		VectorSubtract(facecenter, areastart, dir);
		VectorNormalize(dir);
		VectorMA(areastart, 4, dir, start);
		VectorCopy(bsptrace.endpos, end);
		trace = AAS_TraceClientBBox(start, end, PRESENCE_NORMAL, -1);
		VectorSubtract(trace.endpos, facecenter, dir);
		if (VectorLength(dir) > 24) continue;
		//
		VectorCopy(trace.endpos, start);
		VectorCopy(trace.endpos, end);
		end[2] -= AAS_FallDamageDistance();
		trace = AAS_TraceClientBBox(start, end, PRESENCE_NORMAL, -1);
		if (trace.fraction >= 1) continue;
		//area to end in
		areanum = AAS_PointAreaNum(trace.endpos);
		//if not in lava or slime
		if (aasworld.areasettings[areanum].contents & (AREACONTENTS_SLIME|AREACONTENTS_LAVA))
		{
			continue;
		} //end if
		//do not go the the source area
		if (areanum == area1num) continue;
		//don't create reachabilities if they already exist
		if (AAS_ReachabilityExists(area1num, areanum)) continue;
		//only end in areas we can stand
		if (!AAS_AreaGrounded(areanum)) continue;
		//never go through cluster portals!!
		numareas = AAS_TraceAreas(areastart, bsptrace.endpos, areas, NULL, 20);
		if (numareas >= 20) continue;
		for (j = 0; j < numareas; j++)
		{
			if (aasworld.areasettings[areas[j]].contents & AREACONTENTS_CLUSTERPORTAL) break;
		} //end for
		if (j < numareas) continue;
		//create a new reachability link
		lreach = AAS_AllocReachability();
		if (!lreach) return qfalse;
		lreach->areanum = areanum;
		lreach->facenum = face2num;
		lreach->edgenum = 0;
		VectorCopy(areastart, lreach->start);
		//VectorCopy(facecenter, lreach->end);
		VectorCopy(bsptrace.endpos, lreach->end);
		lreach->traveltype = TRAVEL_GRAPPLEHOOK;
		VectorSubtract(lreach->end, lreach->start, dir);
		lreach->traveltime = aassettings.rs_startgrapple + VectorLength(dir) * 0.25;
		lreach->next = areareachability[area1num];
		areareachability[area1num] = lreach;
		//
		reach_grapple++;
	} //end for
	//
	return qfalse;
}