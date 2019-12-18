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
struct TYPE_9__ {int /*<<< orphan*/  nodeUp; TYPE_1__* eUp; scalar_t__ fixUpperEdge; } ;
struct TYPE_8__ {int /*<<< orphan*/  regionPool; int /*<<< orphan*/  dict; } ;
struct TYPE_7__ {scalar_t__ winding; int /*<<< orphan*/ * activeRegion; } ;
typedef  TYPE_2__ TESStesselator ;
typedef  TYPE_3__ ActiveRegion ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  bucketFree (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  dictDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DeleteRegion( TESStesselator *tess, ActiveRegion *reg )
{
	if( reg->fixUpperEdge ) {
		/* It was created with zero winding number, so it better be
		* deleted with zero winding number (ie. it better not get merged
		* with a real edge).
		*/
		assert( reg->eUp->winding == 0 );
	}
	reg->eUp->activeRegion = NULL;
	dictDelete( tess->dict, reg->nodeUp );
	bucketFree( tess->regionPool, reg );
}