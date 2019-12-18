#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_6__* anEdge; struct TYPE_15__* next; } ;
struct TYPE_14__ {scalar_t__ winding; struct TYPE_14__* Lnext; TYPE_3__* Dst; TYPE_2__* Org; } ;
struct TYPE_13__ {int /*<<< orphan*/ * tUnit; TYPE_1__* mesh; } ;
struct TYPE_12__ {int /*<<< orphan*/  t; struct TYPE_12__* next; } ;
struct TYPE_11__ {int s; int t; } ;
struct TYPE_10__ {int s; int t; } ;
struct TYPE_9__ {TYPE_4__ vHead; TYPE_7__ fHead; } ;
typedef  TYPE_4__ TESSvertex ;
typedef  TYPE_5__ TESStesselator ;
typedef  scalar_t__ TESSreal ;
typedef  TYPE_6__ TESShalfEdge ;
typedef  TYPE_7__ TESSface ;

/* Variables and functions */

__attribute__((used)) static void CheckOrientation( TESStesselator *tess )
{
	TESSreal area;
	TESSface *f, *fHead = &tess->mesh->fHead;
	TESSvertex *v, *vHead = &tess->mesh->vHead;
	TESShalfEdge *e;

	/* When we compute the normal automatically, we choose the orientation
	* so that the the sum of the signed areas of all contours is non-negative.
	*/
	area = 0;
	for( f = fHead->next; f != fHead; f = f->next ) {
		e = f->anEdge;
		if( e->winding <= 0 ) continue;
		do {
			area += (e->Org->s - e->Dst->s) * (e->Org->t + e->Dst->t);
			e = e->Lnext;
		} while( e != f->anEdge );
	}
	if( area < 0 ) {
		/* Reverse the orientation by flipping all the t-coordinates */
		for( v = vHead->next; v != vHead; v = v->next ) {
			v->t = - v->t;
		}
		tess->tUnit[0] = - tess->tUnit[0];
		tess->tUnit[1] = - tess->tUnit[1];
		tess->tUnit[2] = - tess->tUnit[2];
	}
}