#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int outputnumber; int numpoints; int planenum; int /*<<< orphan*/ * vertexnums; int /*<<< orphan*/  texinfo; scalar_t__* split; scalar_t__ merged; } ;
typedef  TYPE_1__ face_t ;
struct TYPE_7__ {int planenum; int side; size_t firstedge; int numedges; int /*<<< orphan*/  texinfo; } ;
typedef  TYPE_2__ dface_t ;

/* Variables and functions */
 int /*<<< orphan*/  Error (char*) ; 
 int GetEdge2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 size_t MAX_MAP_FACES ; 
 size_t MAX_MAP_SURFEDGES ; 
 TYPE_2__* dfaces ; 
 int* dsurfedges ; 
 size_t numfaces ; 
 size_t numsurfedges ; 

void EmitFace (face_t *f)
{
	dface_t	*df;
	int		i;
	int		e;

	f->outputnumber = -1;

	if (f->numpoints < 3)
	{
		return;		// degenerated
	}
	if (f->merged || f->split[0] || f->split[1])
	{
		return;		// not a final face
	}

	// save output number so leaffaces can use
	f->outputnumber = numfaces;

	if (numfaces >= MAX_MAP_FACES)
		Error ("numfaces == MAX_MAP_FACES");
	df = &dfaces[numfaces];
	numfaces++;

	// planenum is used by qlight, but not quake
	df->planenum = f->planenum & (~1);
	df->side = f->planenum & 1;

	df->firstedge = numsurfedges;
	df->numedges = f->numpoints;
	df->texinfo = f->texinfo;
	for (i=0 ; i<f->numpoints ; i++)
	{
//		e = GetEdge (f->pts[i], f->pts[(i+1)%f->numpoints], f);
		e = GetEdge2 (f->vertexnums[i], f->vertexnums[(i+1)%f->numpoints], f);
		if (numsurfedges >= MAX_MAP_SURFEDGES)
			Error ("numsurfedges == MAX_MAP_SURFEDGES");
		dsurfedges[numsurfedges] = e;
		numsurfedges++;
	}
}