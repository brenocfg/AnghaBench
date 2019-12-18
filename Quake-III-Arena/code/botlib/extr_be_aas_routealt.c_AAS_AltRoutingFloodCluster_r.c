#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int frontarea; int backarea; } ;
typedef  TYPE_1__ aas_face_t ;
struct TYPE_6__ {int numfaces; int firstface; } ;
typedef  TYPE_2__ aas_area_t ;
struct TYPE_8__ {int /*<<< orphan*/ * faceindex; TYPE_1__* faces; TYPE_2__* areas; } ;
struct TYPE_7__ {int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 TYPE_4__ aasworld ; 
 size_t abs (int /*<<< orphan*/ ) ; 
 int* clusterareas ; 
 TYPE_3__* midrangeareas ; 
 size_t numclusterareas ; 
 int /*<<< orphan*/  qfalse ; 

void AAS_AltRoutingFloodCluster_r(int areanum)
{
	int i, otherareanum;
	aas_area_t *area;
	aas_face_t *face;

	//add the current area to the areas of the current cluster
	clusterareas[numclusterareas] = areanum;
	numclusterareas++;
	//remove the area from the mid range areas
	midrangeareas[areanum].valid = qfalse;
	//flood to other areas through the faces of this area
	area = &aasworld.areas[areanum];
	for (i = 0; i < area->numfaces; i++)
	{
		face = &aasworld.faces[abs(aasworld.faceindex[area->firstface + i])];
		//get the area at the other side of the face
		if (face->frontarea == areanum) otherareanum = face->backarea;
		else otherareanum = face->frontarea;
		//if there is an area at the other side of this face
		if (!otherareanum) continue;
		//if the other area is not a midrange area
		if (!midrangeareas[otherareanum].valid) continue;
		//
		AAS_AltRoutingFloodCluster_r(otherareanum);
	} //end for
}