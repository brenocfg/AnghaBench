#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {void* dirty; void* sentinel; void* fixUpperEdge; int /*<<< orphan*/ * nodeUp; TYPE_2__* eUp; } ;
struct TYPE_10__ {TYPE_3__* activeRegion; } ;
struct TYPE_9__ {int /*<<< orphan*/  env; int /*<<< orphan*/  dict; int /*<<< orphan*/  regionPool; } ;
typedef  TYPE_1__ TESStesselator ;
typedef  TYPE_2__ TESShalfEdge ;
typedef  TYPE_3__ ActiveRegion ;

/* Variables and functions */
 void* FALSE ; 
 scalar_t__ bucketAlloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * dictInsertBefore (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ActiveRegion *AddRegionBelow( TESStesselator *tess,
									ActiveRegion *regAbove,
									TESShalfEdge *eNewUp )
/*
* Add a new active region to the sweep line, *somewhere* below "regAbove"
* (according to where the new edge belongs in the sweep-line dictionary).
* The upper edge of the new region will be "eNewUp".
* Winding number and "inside" flag are not updated.
*/
{
	ActiveRegion *regNew = (ActiveRegion *)bucketAlloc( tess->regionPool );
	if (regNew == NULL) longjmp(tess->env,1);

	regNew->eUp = eNewUp;
	regNew->nodeUp = dictInsertBefore( tess->dict, regAbove->nodeUp, regNew );
	if (regNew->nodeUp == NULL) longjmp(tess->env,1);
	regNew->fixUpperEdge = FALSE;
	regNew->sentinel = FALSE;
	regNew->dirty = FALSE;

	eNewUp->activeRegion = regNew;
	return regNew;
}