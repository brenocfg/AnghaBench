#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  winding_t ;
struct TYPE_7__ {int planenum; int surfaceFlags; int /*<<< orphan*/ * visibleHull; } ;
typedef  TYPE_1__ side_t ;
struct TYPE_8__ {int planenum; int /*<<< orphan*/  hint; struct TYPE_8__* next; int /*<<< orphan*/  w; } ;
typedef  TYPE_2__ bspface_t ;
struct TYPE_9__ {int numsides; TYPE_1__* sides; scalar_t__ detail; struct TYPE_9__* next; } ;
typedef  TYPE_3__ bspbrush_t ;

/* Variables and functions */
 TYPE_2__* AllocBspFace () ; 
 int /*<<< orphan*/  CopyWinding (int /*<<< orphan*/ *) ; 
 int SURF_HINT ; 
 int /*<<< orphan*/  qtrue ; 

bspface_t	*MakeVisibleBspFaceList( bspbrush_t *list ) {
	bspbrush_t	*b;
	int			i;
	side_t		*s;
	winding_t	*w;
	bspface_t	*f, *flist;

	flist = NULL;
	for ( b = list ; b ; b = b->next ) {
		if ( b->detail ) {
			continue;
		}
		for ( i = 0 ; i < b->numsides ; i++ ) {
			s = &b->sides[i];
			w = s->visibleHull;
			if ( !w ) {
				continue;
			}
			f = AllocBspFace();
			f->w = CopyWinding( w );
			f->planenum = s->planenum & ~1;
			f->next = flist;
			if (s->surfaceFlags & SURF_HINT) {
				//f->priority = HINT_PRIORITY;
				f->hint = qtrue;
			}
			flist = f;
		}
	}

	return flist;
}