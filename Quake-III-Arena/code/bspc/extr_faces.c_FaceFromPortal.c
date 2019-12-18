#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int planenum; int /*<<< orphan*/  texinfo; } ;
typedef  TYPE_2__ side_t ;
struct TYPE_10__ {TYPE_1__** nodes; int /*<<< orphan*/  winding; TYPE_2__* side; } ;
typedef  TYPE_3__ portal_t ;
struct TYPE_11__ {int planenum; int contents; int /*<<< orphan*/  w; TYPE_3__* portal; int /*<<< orphan*/  texinfo; } ;
typedef  TYPE_4__ face_t ;
struct TYPE_8__ {int contents; } ;

/* Variables and functions */
 TYPE_4__* AllocFace () ; 
 int CONTENTS_WINDOW ; 
 int /*<<< orphan*/  CopyWinding (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReverseWinding (int /*<<< orphan*/ ) ; 
 int VisibleContents (int) ; 

face_t *FaceFromPortal (portal_t *p, int pside)
{
	face_t	*f;
	side_t	*side;

	side = p->side;
	if (!side)
		return NULL;	// portal does not bridge different visible contents

	f = AllocFace ();

	f->texinfo = side->texinfo;
	f->planenum = (side->planenum & ~1) | pside;
	f->portal = p;

	if ( (p->nodes[pside]->contents & CONTENTS_WINDOW)
		&& VisibleContents(p->nodes[!pside]->contents^p->nodes[pside]->contents) == CONTENTS_WINDOW )
		return NULL;	// don't show insides of windows

	if (pside)
	{
		f->w = ReverseWinding(p->winding);
		f->contents = p->nodes[1]->contents;
	}
	else
	{
		f->w = CopyWinding(p->winding);
		f->contents = p->nodes[0]->contents;
	}
	return f;
}