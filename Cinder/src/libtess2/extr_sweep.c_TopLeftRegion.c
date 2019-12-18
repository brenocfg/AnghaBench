#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_1__* eUp; } ;
struct TYPE_17__ {TYPE_2__* eUp; scalar_t__ fixUpperEdge; } ;
struct TYPE_16__ {int /*<<< orphan*/  mesh; } ;
struct TYPE_15__ {int /*<<< orphan*/  Lnext; int /*<<< orphan*/ * Org; } ;
struct TYPE_14__ {int /*<<< orphan*/  Sym; } ;
typedef  int /*<<< orphan*/  TESSvertex ;
typedef  TYPE_3__ TESStesselator ;
typedef  int /*<<< orphan*/  TESShalfEdge ;
typedef  TYPE_4__ ActiveRegion ;

/* Variables and functions */
 int /*<<< orphan*/  FixUpperEdge (TYPE_3__*,TYPE_4__*,int /*<<< orphan*/ *) ; 
 TYPE_4__* RegionAbove (TYPE_4__*) ; 
 TYPE_8__* RegionBelow (TYPE_4__*) ; 
 int /*<<< orphan*/ * tessMeshConnect (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ActiveRegion *TopLeftRegion( TESStesselator *tess, ActiveRegion *reg )
{
	TESSvertex *org = reg->eUp->Org;
	TESShalfEdge *e;

	/* Find the region above the uppermost edge with the same origin */
	do {
		reg = RegionAbove( reg );
	} while( reg->eUp->Org == org );

	/* If the edge above was a temporary edge introduced by ConnectRightVertex,
	* now is the time to fix it.
	*/
	if( reg->fixUpperEdge ) {
		e = tessMeshConnect( tess->mesh, RegionBelow(reg)->eUp->Sym, reg->eUp->Lnext );
		if (e == NULL) return NULL;
		if ( !FixUpperEdge( tess, reg, e ) ) return NULL;
		reg = RegionAbove( reg );
	}
	return reg;
}