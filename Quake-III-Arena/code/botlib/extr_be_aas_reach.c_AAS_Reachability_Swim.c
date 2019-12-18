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
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_9__ {int /*<<< orphan*/  normal; } ;
typedef  TYPE_1__ aas_plane_t ;
struct TYPE_10__ {int areanum; int facenum; int traveltime; struct TYPE_10__* next; int /*<<< orphan*/  traveltype; int /*<<< orphan*/  end; int /*<<< orphan*/  start; scalar_t__ edgenum; } ;
typedef  TYPE_2__ aas_lreachability_t ;
struct TYPE_11__ {int planenum; } ;
typedef  TYPE_3__ aas_face_t ;
struct TYPE_12__ {int presencetype; } ;
typedef  TYPE_4__ aas_areasettings_t ;
struct TYPE_13__ {scalar_t__* mins; scalar_t__* maxs; int numfaces; int firstface; } ;
typedef  TYPE_5__ aas_area_t ;
struct TYPE_14__ {int* faceindex; TYPE_1__* planes; TYPE_4__* areasettings; TYPE_3__* faces; TYPE_5__* areas; } ;

/* Variables and functions */
 TYPE_2__* AAS_AllocReachability () ; 
 int /*<<< orphan*/  AAS_AreaSwim (int) ; 
 int AAS_AreaVolume (int) ; 
 int /*<<< orphan*/  AAS_FaceCenter (int,int /*<<< orphan*/ ) ; 
 int AAS_PointContents (int /*<<< orphan*/ ) ; 
 int CONTENTS_LAVA ; 
 int CONTENTS_SLIME ; 
 int CONTENTS_WATER ; 
 int /*<<< orphan*/  INSIDEUNITS ; 
 int PRESENCE_NORMAL ; 
 int /*<<< orphan*/  TRAVEL_SWIM ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorMA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__ aasworld ; 
 int abs (int) ; 
 TYPE_2__** areareachability ; 
 int qfalse ; 
 int qtrue ; 
 int /*<<< orphan*/  reach_swim ; 

int AAS_Reachability_Swim(int area1num, int area2num)
{
	int i, j, face1num, face2num, side1;
	aas_area_t *area1, *area2;
	aas_areasettings_t *areasettings;
	aas_lreachability_t *lreach;
	aas_face_t *face1;
	aas_plane_t *plane;
	vec3_t start;

	if (!AAS_AreaSwim(area1num) || !AAS_AreaSwim(area2num)) return qfalse;
	//if the second area is crouch only
	if (!(aasworld.areasettings[area2num].presencetype & PRESENCE_NORMAL)) return qfalse;

	area1 = &aasworld.areas[area1num];
	area2 = &aasworld.areas[area2num];

	//if the areas are not near anough
	for (i = 0; i < 3; i++)
	{
		if (area1->mins[i] > area2->maxs[i] + 10) return qfalse;
		if (area1->maxs[i] < area2->mins[i] - 10) return qfalse;
	} //end for
	//find a shared face and create a reachability link
	for (i = 0; i < area1->numfaces; i++)
	{
		face1num = aasworld.faceindex[area1->firstface + i];
		side1 = face1num < 0;
		face1num = abs(face1num);
		//
		for (j = 0; j < area2->numfaces; j++)
		{
			face2num = abs(aasworld.faceindex[area2->firstface + j]);
			//
			if (face1num == face2num)
			{
				AAS_FaceCenter(face1num, start);
				//
				if (AAS_PointContents(start) & (CONTENTS_LAVA|CONTENTS_SLIME|CONTENTS_WATER))
				{
					//
					face1 = &aasworld.faces[face1num];
					areasettings = &aasworld.areasettings[area1num];
					//create a new reachability link
					lreach = AAS_AllocReachability();
					if (!lreach) return qfalse;
					lreach->areanum = area2num;
					lreach->facenum = face1num;
					lreach->edgenum = 0;
					VectorCopy(start, lreach->start);
					plane = &aasworld.planes[face1->planenum ^ side1];
					VectorMA(lreach->start, -INSIDEUNITS, plane->normal, lreach->end);
					lreach->traveltype = TRAVEL_SWIM;
					lreach->traveltime = 1;
					//if the volume of the area is rather small
					if (AAS_AreaVolume(area2num) < 800)
						lreach->traveltime += 200;
					//if (!(AAS_PointContents(start) & MASK_WATER)) lreach->traveltime += 500;
					//link the reachability
					lreach->next = areareachability[area1num];
					areareachability[area1num] = lreach;
					reach_swim++;
					return qtrue;
				} //end if
			} //end if
		} //end for
	} //end for
	return qfalse;
}