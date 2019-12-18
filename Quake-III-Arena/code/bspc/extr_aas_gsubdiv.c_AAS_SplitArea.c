#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
struct TYPE_21__ {int planenum; TYPE_2__* backarea; TYPE_2__* frontarea; struct TYPE_21__** next; int /*<<< orphan*/ * winding; } ;
typedef  TYPE_1__ tmp_face_t ;
struct TYPE_22__ {int invalid; TYPE_1__* tmpfaces; int /*<<< orphan*/  modelnum; int /*<<< orphan*/  contents; int /*<<< orphan*/  presencetype; int /*<<< orphan*/  areanum; } ;
typedef  TYPE_2__ tmp_area_t ;
struct TYPE_23__ {int /*<<< orphan*/  dist; int /*<<< orphan*/  normal; } ;
typedef  TYPE_3__ plane_t ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_AddFaceSideToArea (TYPE_1__*,int,TYPE_2__*) ; 
 TYPE_2__* AAS_AllocTmpArea () ; 
 TYPE_1__* AAS_AllocTmpFace () ; 
 int /*<<< orphan*/  AAS_CheckArea (TYPE_2__*) ; 
 int /*<<< orphan*/  AAS_FlipAreaFaces (TYPE_2__*) ; 
 int /*<<< orphan*/  AAS_FreeTmpFace (TYPE_1__*) ; 
 int /*<<< orphan*/  AAS_RemoveFaceFromArea (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  AAS_SplitFace (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**,TYPE_1__**) ; 
 int /*<<< orphan*/ * AAS_SplitWinding (TYPE_2__*,int) ; 
 int /*<<< orphan*/  Error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Log_Print (char*) ; 
 TYPE_3__* mapplanes ; 

void AAS_SplitArea(tmp_area_t *tmparea, int planenum, tmp_area_t **frontarea, tmp_area_t **backarea)
{
	int side;
	tmp_area_t *facefrontarea, *facebackarea, *faceotherarea;
	tmp_face_t *face, *frontface, *backface, *splitface, *nextface;
	winding_t *splitwinding;
	plane_t *splitplane;

/*
#ifdef AW_DEBUG
	int facesplits, groundsplits, epsilonface;
	Log_Print("\n----------------------\n");
	Log_Print("splitting area %d\n", areanum);
	Log_Print("with normal = \'%f %f %f\', dist = %f\n", normal[0], normal[1], normal[2], dist);
	AAS_TestSplitPlane(areanum, normal, dist,
										&facesplits, &groundsplits, &epsilonface);
	Log_Print("face splits = %d\nground splits = %d\n", facesplits, groundsplits);
	if (epsilonface) Log_Print("aaahh epsilon face\n");
#endif //AW_DEBUG*/
	//the original area

	AAS_FlipAreaFaces(tmparea);
	AAS_CheckArea(tmparea);
	//
	splitplane = &mapplanes[planenum];
/*	//create a split winding, first base winding for plane
	splitwinding = BaseWindingForPlane(splitplane->normal, splitplane->dist);
	//chop with all the faces of the area
	for (face = tmparea->tmpfaces; face && splitwinding; face = face->next[side])
	{
		//side of the face the original area was on
		side = face->frontarea != tmparea->areanum;
		plane = &mapplanes[face->planenum ^ side];
		ChopWindingInPlace(&splitwinding, plane->normal, plane->dist, 0); // PLANESIDE_EPSILON);
	} //end for*/
	splitwinding = AAS_SplitWinding(tmparea, planenum);
	if (!splitwinding)
	{
/*
#ifdef DEBUG
		AAS_TestSplitPlane(areanum, normal, dist,
											&facesplits, &groundsplits, &epsilonface);
		Log_Print("\nface splits = %d\nground splits = %d\n", facesplits, groundsplits);
		if (epsilonface) Log_Print("aaahh epsilon face\n");
#endif //DEBUG*/
		Error("AAS_SplitArea: no split winding when splitting area %d\n", tmparea->areanum);
	} //end if
	//create a split face
	splitface = AAS_AllocTmpFace();
	//get the map plane
	splitface->planenum = planenum;
	//store the split winding
	splitface->winding = splitwinding;
	//the new front area
	(*frontarea) = AAS_AllocTmpArea();
	(*frontarea)->presencetype = tmparea->presencetype;
	(*frontarea)->contents = tmparea->contents;
	(*frontarea)->modelnum = tmparea->modelnum;
	(*frontarea)->tmpfaces = NULL;
	//the new back area
	(*backarea) = AAS_AllocTmpArea();
	(*backarea)->presencetype = tmparea->presencetype;
	(*backarea)->contents = tmparea->contents;
	(*backarea)->modelnum = tmparea->modelnum;
	(*backarea)->tmpfaces = NULL;
	//add the split face to the new areas
	AAS_AddFaceSideToArea(splitface, 0, (*frontarea));
	AAS_AddFaceSideToArea(splitface, 1, (*backarea));

	//split all the faces of the original area
	for (face = tmparea->tmpfaces; face; face = nextface)
	{
		//side of the face the original area was on
		side = face->frontarea != tmparea;
		//next face of the original area
		nextface = face->next[side];
		//front area of the face
		facefrontarea = face->frontarea;
		//back area of the face
		facebackarea = face->backarea;
		//remove the face from both the front and back areas
		if (facefrontarea) AAS_RemoveFaceFromArea(face, facefrontarea);
		if (facebackarea) AAS_RemoveFaceFromArea(face, facebackarea);
		//split the face
		AAS_SplitFace(face, splitplane->normal, splitplane->dist, &frontface, &backface);
		//free the original face
		AAS_FreeTmpFace(face);
		//get the number of the area at the other side of the face
		if (side) faceotherarea = facefrontarea;
		else faceotherarea = facebackarea;
		//if there is an area at the other side of the original face
		if (faceotherarea)
		{
			if (frontface) AAS_AddFaceSideToArea(frontface, !side, faceotherarea);
			if (backface) AAS_AddFaceSideToArea(backface, !side, faceotherarea);
		} //end if
		//add the front and back part left after splitting the original face to the new areas
		if (frontface) AAS_AddFaceSideToArea(frontface, side, (*frontarea));
		if (backface) AAS_AddFaceSideToArea(backface, side, (*backarea));
	} //end for

	if (!(*frontarea)->tmpfaces) Log_Print("AAS_SplitArea: front area without faces\n");
	if (!(*backarea)->tmpfaces) Log_Print("AAS_SplitArea: back area without faces\n");

	tmparea->invalid = true;
/*
#ifdef AW_DEBUG
	for (i = 0, face = frontarea->tmpfaces; face; face = face->next[side])
	{
		side = face->frontarea != frontarea->areanum;
		i++;
	} //end for
	Log_Print("created front area %d with %d faces\n", frontarea->areanum, i);

	for (i = 0, face = backarea->tmpfaces; face; face = face->next[side])
	{
		side = face->frontarea != backarea->areanum;
		i++;
	} //end for
	Log_Print("created back area %d with %d faces\n", backarea->areanum, i);
#endif //AW_DEBUG*/

	AAS_FlipAreaFaces((*frontarea));
	AAS_FlipAreaFaces((*backarea));
	//
	AAS_CheckArea((*frontarea));
	AAS_CheckArea((*backarea));
}