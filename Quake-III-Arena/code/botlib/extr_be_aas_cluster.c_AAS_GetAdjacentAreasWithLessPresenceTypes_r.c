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
struct TYPE_6__ {int faceflags; int frontarea; int backarea; } ;
typedef  TYPE_2__ aas_face_t ;
struct TYPE_7__ {int numfaces; int firstface; } ;
typedef  TYPE_3__ aas_area_t ;
struct TYPE_8__ {TYPE_1__* areasettings; TYPE_2__* faces; int /*<<< orphan*/ * faceindex; TYPE_3__* areas; } ;
struct TYPE_5__ {int presencetype; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_Error (char*) ; 
 int FACE_SOLID ; 
 int MAX_PORTALAREAS ; 
 TYPE_4__ aasworld ; 
 int abs (int /*<<< orphan*/ ) ; 

int AAS_GetAdjacentAreasWithLessPresenceTypes_r(int *areanums, int numareas, int curareanum)
{
	int i, j, presencetype, otherpresencetype, otherareanum, facenum;
	aas_area_t *area;
	aas_face_t *face;

	areanums[numareas++] = curareanum;
	area = &aasworld.areas[curareanum];
	presencetype = aasworld.areasettings[curareanum].presencetype;
	for (i = 0; i < area->numfaces; i++)
	{
		facenum = abs(aasworld.faceindex[area->firstface + i]);
		face = &aasworld.faces[facenum];
		//if the face is solid
		if (face->faceflags & FACE_SOLID) continue;
		//the area at the other side of the face
		if (face->frontarea != curareanum) otherareanum = face->frontarea;
		else otherareanum = face->backarea;
		//
		otherpresencetype = aasworld.areasettings[otherareanum].presencetype;
		//if the other area has less presence types
		if ((presencetype & ~otherpresencetype) &&
				!(otherpresencetype & ~presencetype))
		{
			//check if the other area isn't already in the list
			for (j = 0; j < numareas; j++)
			{
				if (otherareanum == areanums[j]) break;
			} //end for
			//if the other area isn't already in the list
			if (j == numareas)
			{
				if (numareas >= MAX_PORTALAREAS)
				{
					AAS_Error("MAX_PORTALAREAS");
					return numareas;
				} //end if
				numareas = AAS_GetAdjacentAreasWithLessPresenceTypes_r(areanums, numareas, otherareanum);
			} //end if
		} //end if
	} //end for
	return numareas;
}