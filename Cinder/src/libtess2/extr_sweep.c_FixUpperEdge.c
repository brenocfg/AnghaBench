#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* eUp; int /*<<< orphan*/  fixUpperEdge; } ;
struct TYPE_9__ {TYPE_3__* activeRegion; } ;
struct TYPE_8__ {int /*<<< orphan*/  mesh; } ;
typedef  TYPE_1__ TESStesselator ;
typedef  TYPE_2__ TESShalfEdge ;
typedef  TYPE_3__ ActiveRegion ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tessMeshDelete (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int FixUpperEdge( TESStesselator *tess, ActiveRegion *reg, TESShalfEdge *newEdge )
/*
* Replace an upper edge which needs fixing (see ConnectRightVertex).
*/
{
	assert( reg->fixUpperEdge );
	if ( !tessMeshDelete( tess->mesh, reg->eUp ) ) return 0;
	reg->fixUpperEdge = FALSE;
	reg->eUp = newEdge;
	newEdge->activeRegion = reg;

	return 1; 
}