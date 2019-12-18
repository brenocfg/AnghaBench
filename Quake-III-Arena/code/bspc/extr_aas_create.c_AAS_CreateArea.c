#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ vec3_t ;
struct TYPE_20__ {TYPE_4__* tmparea; scalar_t__* children; scalar_t__ planenum; } ;
typedef  TYPE_2__ tmp_node_t ;
struct TYPE_21__ {int planenum; int faceflags; scalar_t__ aasfacenum; int /*<<< orphan*/  winding; } ;
typedef  TYPE_3__ tmp_face_t ;
struct TYPE_22__ {int presencetype; int /*<<< orphan*/  modelnum; int /*<<< orphan*/  contents; int /*<<< orphan*/  areanum; int /*<<< orphan*/ * tmpfaces; } ;
typedef  TYPE_4__ tmp_area_t ;
struct TYPE_23__ {int planenum; TYPE_6__** nodes; int /*<<< orphan*/  winding; TYPE_3__* tmpface; struct TYPE_23__** next; } ;
typedef  TYPE_5__ portal_t ;
struct TYPE_24__ {int contents; int expansionbboxes; int /*<<< orphan*/  modelnum; TYPE_5__* portals; } ;
typedef  TYPE_6__ node_t ;
struct TYPE_25__ {int allpresencetypes; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_AddFaceSideToArea (TYPE_3__*,int,TYPE_4__*) ; 
 TYPE_4__* AAS_AllocTmpArea () ; 
 TYPE_3__* AAS_AllocTmpFace () ; 
 TYPE_2__* AAS_AllocTmpNode () ; 
 int /*<<< orphan*/  AAS_CheckArea (TYPE_4__*) ; 
 int /*<<< orphan*/  AAS_CheckFaceWindingPlane (TYPE_3__*) ; 
 int /*<<< orphan*/  AAS_FlipAreaFaces (TYPE_4__*) ; 
 scalar_t__ AAS_GroundFace (TYPE_3__*) ; 
 int /*<<< orphan*/  AREACONTENTS_CLUSTERPORTAL ; 
 int /*<<< orphan*/  AREACONTENTS_DONOTENTER ; 
 int /*<<< orphan*/  AREACONTENTS_JUMPPAD ; 
 int /*<<< orphan*/  AREACONTENTS_LAVA ; 
 int /*<<< orphan*/  AREACONTENTS_MOVER ; 
 int /*<<< orphan*/  AREACONTENTS_NOTTEAM1 ; 
 int /*<<< orphan*/  AREACONTENTS_NOTTEAM2 ; 
 int /*<<< orphan*/  AREACONTENTS_SLIME ; 
 int /*<<< orphan*/  AREACONTENTS_TELEPORTER ; 
 int /*<<< orphan*/  AREACONTENTS_WATER ; 
 int CONTENTS_CLUSTERPORTAL ; 
 int CONTENTS_DONOTENTER ; 
 int CONTENTS_JUMPPAD ; 
 int CONTENTS_LADDER ; 
 int CONTENTS_LAVA ; 
 int CONTENTS_MOVER ; 
 int CONTENTS_NOTTEAM1 ; 
 int CONTENTS_NOTTEAM2 ; 
 int CONTENTS_PLAYERCLIP ; 
 int CONTENTS_SLIME ; 
 int CONTENTS_SOLID ; 
 int CONTENTS_TELEPORTER ; 
 int CONTENTS_WATER ; 
 int /*<<< orphan*/  CopyWinding (int /*<<< orphan*/ ) ; 
 int FACE_GROUND ; 
 int FACE_LADDER ; 
 int FACE_LIQUID ; 
 int FACE_LIQUIDSURFACE ; 
 int FACE_SOLID ; 
 int /*<<< orphan*/  ReverseWinding (int /*<<< orphan*/ ) ; 
 TYPE_7__ cfg ; 
 int /*<<< orphan*/  qprintf (char*,int /*<<< orphan*/ ) ; 

tmp_node_t *AAS_CreateArea(node_t *node)
{
	int pside;
	int areafaceflags;
	portal_t	*p;
	tmp_face_t *tmpface;
	tmp_area_t *tmparea;
	tmp_node_t *tmpnode;
	vec3_t up = {0, 0, 1};

	//create an area from this leaf
	tmparea = AAS_AllocTmpArea();
	tmparea->tmpfaces = NULL;
	//clear the area face flags
	areafaceflags = 0;
	//make aas faces from the portals
	for (p = node->portals; p; p = p->next[pside])
	{
		pside = (p->nodes[1] == node);
		//don't create faces from very small portals
//		if (WindingArea(p->winding) < 1) continue;
		//if there's already a face created for this portal
		if (p->tmpface)
		{
			//add the back side of the face to the area
			AAS_AddFaceSideToArea(p->tmpface, 1, tmparea);
		} //end if
		else
		{
			tmpface = AAS_AllocTmpFace();
			//set the face pointer at the portal so we can see from
			//the portal there's a face created for it
			p->tmpface = tmpface;
			//FIXME: test this change
			//tmpface->planenum = (p->planenum & ~1) | pside;
			tmpface->planenum = p->planenum ^ pside;
			if (pside) tmpface->winding = ReverseWinding(p->winding);
			else tmpface->winding = CopyWinding(p->winding);
#ifdef L_DEBUG
			//
			AAS_CheckFaceWindingPlane(tmpface);
#endif //L_DEBUG
			//if there's solid at the other side of the portal
			if (p->nodes[!pside]->contents & (CONTENTS_SOLID | CONTENTS_PLAYERCLIP))
			{
				tmpface->faceflags |= FACE_SOLID;
			} //end if
			//else there is no solid at the other side and if there
			//is a liquid at this side
			else if (node->contents & (CONTENTS_WATER|CONTENTS_SLIME|CONTENTS_LAVA))
			{
				tmpface->faceflags |= FACE_LIQUID;
				//if there's no liquid at the other side
				if (!(p->nodes[!pside]->contents & (CONTENTS_WATER|CONTENTS_SLIME|CONTENTS_LAVA)))
				{
					tmpface->faceflags |= FACE_LIQUIDSURFACE;
				} //end if
			} //end else
			//if there's ladder contents at other side of the portal
			if ((p->nodes[pside]->contents & CONTENTS_LADDER) ||
					(p->nodes[!pside]->contents & CONTENTS_LADDER))
			{

				//NOTE: doesn't have to be solid at the other side because
				// when standing one can use a crouch area (which is not solid)
				// as a ladder
				// imagine a ladder one can walk underthrough,
				// under the ladder against the ladder is a crouch area
				// the (vertical) sides of this crouch area area also used as
				// ladder sides when standing (not crouched)
				tmpface->faceflags |= FACE_LADDER;
			} //end if
			//if it is possible to stand on the face
			if (AAS_GroundFace(tmpface))
			{
				tmpface->faceflags |= FACE_GROUND;
			} //end if
			//
			areafaceflags |= tmpface->faceflags;
			//no aas face number yet (zero is a dummy in the aasworld faces)
			tmpface->aasfacenum = 0;
			//add the front side of the face to the area
			AAS_AddFaceSideToArea(tmpface, 0, tmparea);
		} //end else
	} //end for
	qprintf("\r%6d", tmparea->areanum);
	//presence type in the area
	tmparea->presencetype = ~node->expansionbboxes & cfg.allpresencetypes;
	//
	tmparea->contents = 0;
	if (node->contents & CONTENTS_CLUSTERPORTAL) tmparea->contents |= AREACONTENTS_CLUSTERPORTAL;
	if (node->contents & CONTENTS_MOVER) tmparea->contents |= AREACONTENTS_MOVER;
	if (node->contents & CONTENTS_TELEPORTER) tmparea->contents |= AREACONTENTS_TELEPORTER;
	if (node->contents & CONTENTS_JUMPPAD) tmparea->contents |= AREACONTENTS_JUMPPAD;
	if (node->contents & CONTENTS_DONOTENTER) tmparea->contents |= AREACONTENTS_DONOTENTER;
	if (node->contents & CONTENTS_WATER) tmparea->contents |= AREACONTENTS_WATER;
	if (node->contents & CONTENTS_LAVA) tmparea->contents |= AREACONTENTS_LAVA;
	if (node->contents & CONTENTS_SLIME) tmparea->contents |= AREACONTENTS_SLIME;
	if (node->contents & CONTENTS_NOTTEAM1) tmparea->contents |= AREACONTENTS_NOTTEAM1;
	if (node->contents & CONTENTS_NOTTEAM2) tmparea->contents |= AREACONTENTS_NOTTEAM2;

	//store the bsp model that's inside this node
	tmparea->modelnum = node->modelnum;
	//sorta check for flipped area faces (remove??)
	AAS_FlipAreaFaces(tmparea);
	//check if the area is ok (remove??)
	AAS_CheckArea(tmparea);
	//
	tmpnode = AAS_AllocTmpNode();
	tmpnode->planenum = 0;
	tmpnode->children[0] = 0;
	tmpnode->children[1] = 0;
	tmpnode->tmparea = tmparea;
	//
	return tmpnode;
}