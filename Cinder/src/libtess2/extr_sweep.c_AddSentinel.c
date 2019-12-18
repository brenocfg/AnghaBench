#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/ * nodeUp; void* dirty; int /*<<< orphan*/  sentinel; void* fixUpperEdge; void* inside; scalar_t__ windingNumber; TYPE_4__* eUp; } ;
struct TYPE_12__ {TYPE_2__* Dst; TYPE_1__* Org; } ;
struct TYPE_11__ {int /*<<< orphan*/  env; int /*<<< orphan*/  dict; TYPE_2__* event; int /*<<< orphan*/  mesh; int /*<<< orphan*/  regionPool; } ;
struct TYPE_10__ {void* t; void* s; } ;
struct TYPE_9__ {void* t; void* s; } ;
typedef  TYPE_3__ TESStesselator ;
typedef  void* TESSreal ;
typedef  TYPE_4__ TESShalfEdge ;
typedef  TYPE_5__ ActiveRegion ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bucketAlloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictInsert (int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 
 TYPE_4__* tessMeshMakeEdge (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void AddSentinel( TESStesselator *tess, TESSreal smin, TESSreal smax, TESSreal t )
/*
* We add two sentinel edges above and below all other edges,
* to avoid special cases at the top and bottom.
*/
{
	TESShalfEdge *e;
	ActiveRegion *reg = (ActiveRegion *)bucketAlloc( tess->regionPool );
	if (reg == NULL) longjmp(tess->env,1);

	e = tessMeshMakeEdge( tess->mesh );
	if (e == NULL) longjmp(tess->env,1);

	e->Org->s = smax;
	e->Org->t = t;
	e->Dst->s = smin;
	e->Dst->t = t;
	tess->event = e->Dst;		/* initialize it */

	reg->eUp = e;
	reg->windingNumber = 0;
	reg->inside = FALSE;
	reg->fixUpperEdge = FALSE;
	reg->sentinel = TRUE;
	reg->dirty = FALSE;
	reg->nodeUp = dictInsert( tess->dict, reg );
	if (reg->nodeUp == NULL) longjmp(tess->env,1);
}