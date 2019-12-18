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
typedef  int /*<<< orphan*/  numareafrontfaces ;
typedef  int /*<<< orphan*/  numareabackfaces ;
struct TYPE_6__ {int faceflags; int frontarea; int backarea; int planenum; int numedges; int firstedge; } ;
typedef  TYPE_2__ aas_face_t ;
struct TYPE_7__ {int numfaces; int firstface; } ;
typedef  TYPE_3__ aas_area_t ;
struct TYPE_8__ {TYPE_1__* areasettings; int /*<<< orphan*/ * edgeindex; TYPE_2__* faces; int /*<<< orphan*/ * faceindex; TYPE_3__* areas; } ;
struct TYPE_5__ {int contents; int areaflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_ConnectedAreas (int*,int) ; 
 int AAS_GetAdjacentAreasWithLessPresenceTypes_r (int*,int /*<<< orphan*/ ,int) ; 
 int AREACONTENTS_CLUSTERPORTAL ; 
 int AREACONTENTS_ROUTEPORTAL ; 
 int AREA_GROUNDED ; 
 int /*<<< orphan*/  Com_Memset (int*,int /*<<< orphan*/ ,int) ; 
 int FACE_SOLID ; 
 int /*<<< orphan*/  Log_Write (char*,int) ; 
 int MAX_PORTALAREAS ; 
 TYPE_4__ aasworld ; 
 int abs (int /*<<< orphan*/ ) ; 

int AAS_CheckAreaForPossiblePortals(int areanum)
{
	int i, j, k, fen, ben, frontedgenum, backedgenum, facenum;
	int areanums[MAX_PORTALAREAS], numareas, otherareanum;
	int numareafrontfaces[MAX_PORTALAREAS], numareabackfaces[MAX_PORTALAREAS];
	int frontfacenums[MAX_PORTALAREAS], backfacenums[MAX_PORTALAREAS];
	int numfrontfaces, numbackfaces;
	int frontareanums[MAX_PORTALAREAS], backareanums[MAX_PORTALAREAS];
	int numfrontareas, numbackareas;
	int frontplanenum, backplanenum, faceplanenum;
	aas_area_t *area;
	aas_face_t *frontface, *backface, *face;

	//if it isn't already a portal
	if (aasworld.areasettings[areanum].contents & AREACONTENTS_CLUSTERPORTAL) return 0;
	//it must be a grounded area
	if (!(aasworld.areasettings[areanum].areaflags & AREA_GROUNDED)) return 0;
	//
	Com_Memset(numareafrontfaces, 0, sizeof(numareafrontfaces));
	Com_Memset(numareabackfaces, 0, sizeof(numareabackfaces));
	numareas = numfrontfaces = numbackfaces = 0;
	numfrontareas = numbackareas = 0;
	frontplanenum = backplanenum = -1;
	//add any adjacent areas with less presence types
	numareas = AAS_GetAdjacentAreasWithLessPresenceTypes_r(areanums, 0, areanum);
	//
	for (i = 0; i < numareas; i++)
	{
		area = &aasworld.areas[areanums[i]];
		for (j = 0; j < area->numfaces; j++)
		{
			facenum = abs(aasworld.faceindex[area->firstface + j]);
			face = &aasworld.faces[facenum];
			//if the face is solid
			if (face->faceflags & FACE_SOLID) continue;
			//check if the face is shared with one of the other areas
			for (k = 0; k < numareas; k++)
			{
				if (k == i) continue;
				if (face->frontarea == areanums[k] || face->backarea == areanums[k]) break;
			} //end for
			//if the face is shared
			if (k != numareas) continue;
			//the number of the area at the other side of the face
			if (face->frontarea == areanums[i]) otherareanum = face->backarea;
			else otherareanum = face->frontarea;
			//if the other area already is a cluter portal
			if (aasworld.areasettings[otherareanum].contents & AREACONTENTS_CLUSTERPORTAL) return 0;
			//number of the plane of the area
			faceplanenum = face->planenum & ~1;
			//
			if (frontplanenum < 0 || faceplanenum == frontplanenum)
			{
				frontplanenum = faceplanenum;
				frontfacenums[numfrontfaces++] = facenum;
				for (k = 0; k < numfrontareas; k++)
				{
					if (frontareanums[k] == otherareanum) break;
				} //end for
				if (k == numfrontareas) frontareanums[numfrontareas++] = otherareanum;
				numareafrontfaces[i]++;
			} //end if
			else if (backplanenum < 0 || faceplanenum == backplanenum)
			{
				backplanenum = faceplanenum;
				backfacenums[numbackfaces++] = facenum;
				for (k = 0; k < numbackareas; k++)
				{
					if (backareanums[k] == otherareanum) break;
				} //end for
				if (k == numbackareas) backareanums[numbackareas++] = otherareanum;
				numareabackfaces[i]++;
			} //end else
			else
			{
				return 0;
			} //end else
		} //end for
	} //end for
	//every area should have at least one front face and one back face
	for (i = 0; i < numareas; i++)
	{
		if (!numareafrontfaces[i] || !numareabackfaces[i]) return 0;
	} //end for
	//the front areas should all be connected
	if (!AAS_ConnectedAreas(frontareanums, numfrontareas)) return 0;
	//the back areas should all be connected
	if (!AAS_ConnectedAreas(backareanums, numbackareas)) return 0;
	//none of the front faces should have a shared edge with a back face
	for (i = 0; i < numfrontfaces; i++)
	{
		frontface = &aasworld.faces[frontfacenums[i]];
		for (fen = 0; fen < frontface->numedges; fen++)
		{
			frontedgenum = abs(aasworld.edgeindex[frontface->firstedge + fen]);
			for (j = 0; j < numbackfaces; j++)
			{
				backface = &aasworld.faces[backfacenums[j]];
				for (ben = 0; ben < backface->numedges; ben++)
				{
					backedgenum = abs(aasworld.edgeindex[backface->firstedge + ben]);
					if (frontedgenum == backedgenum) break;
				} //end for
				if (ben != backface->numedges) break;
			} //end for
			if (j != numbackfaces) break;
		} //end for
		if (fen != frontface->numedges) break;
	} //end for
	if (i != numfrontfaces) return 0;
	//set the cluster portal contents
	for (i = 0; i < numareas; i++)
	{
		aasworld.areasettings[areanums[i]].contents |= AREACONTENTS_CLUSTERPORTAL;
		//this area can be used as a route portal
		aasworld.areasettings[areanums[i]].contents |= AREACONTENTS_ROUTEPORTAL;
		Log_Write("possible portal: %d\r\n", areanums[i]);
	} //end for
	//
	return numareas;
}