#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* frontarea; TYPE_2__* backarea; struct TYPE_6__** next; } ;
typedef  TYPE_1__ tmp_face_t ;
struct TYPE_7__ {TYPE_1__* tmpfaces; scalar_t__ invalid; struct TYPE_7__* l_next; } ;
typedef  TYPE_2__ tmp_area_t ;
struct TYPE_8__ {int /*<<< orphan*/  nodes; TYPE_2__* areas; } ;

/* Variables and functions */
 int /*<<< orphan*/  AAS_GroundArea (TYPE_2__*) ; 
 int /*<<< orphan*/  AAS_RefreshMergedTree_r (int /*<<< orphan*/ ) ; 
 scalar_t__ AAS_TryMergeFaceAreas (TYPE_1__*) ; 
 int /*<<< orphan*/  Log_Write (char*,...) ; 
 int /*<<< orphan*/  qprintf (char*,...) ; 
 TYPE_3__ tmpaasworld ; 

void AAS_MergeAreas(void)
{
	int side, nummerges, merges, groundfirst;
	tmp_area_t *tmparea, *othertmparea;
	tmp_face_t *face;

	nummerges = 0;
	Log_Write("AAS_MergeAreas\r\n");
	qprintf("%6d areas merged", 1);
	//
	groundfirst = true;
	//for (i = 0; i < 4 || merges; i++)
	while(1)
	{
		//if (i < 2) groundfirst = true;
		//else groundfirst = false;
		//
		merges = 0;
		//first merge grounded areas only
		for (tmparea = tmpaasworld.areas; tmparea; tmparea = tmparea->l_next)
		{
			//if the area is invalid
			if (tmparea->invalid)
			{
				continue;
			} //end if
			//
			if (groundfirst)
			{
				if (!AAS_GroundArea(tmparea)) continue;
			} //end if
			//
			for (face = tmparea->tmpfaces; face; face = face->next[side])
			{
				side = (face->frontarea != tmparea);
				//if the face has both a front and back area
				if (face->frontarea && face->backarea)
				{
					//
					if (face->frontarea == tmparea) othertmparea = face->backarea;
					else othertmparea = face->frontarea;
					//
					if (groundfirst)
					{
						if (!AAS_GroundArea(othertmparea)) continue;
					} //end if
					if (AAS_TryMergeFaceAreas(face))
					{
						qprintf("\r%6d", ++nummerges);
						merges++;
						break;
					} //end if
				} //end if
			} //end for
		} //end for
		if (!merges)
		{
			if (groundfirst) groundfirst = false;
			else break;
		} //end if
	} //end for
	qprintf("\n");
	Log_Write("%6d areas merged\r\n", nummerges);
	//refresh the merged tree
	AAS_RefreshMergedTree_r(tmpaasworld.nodes);
}