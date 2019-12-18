#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  (* callCombine ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {int /*<<< orphan*/ * coords; } ;
typedef  TYPE_1__ TESSvertex ;
typedef  TYPE_2__ TESStesselator ;
typedef  int /*<<< orphan*/  TESSreal ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CallCombine( TESStesselator *tess, TESSvertex *isect,
						TESSreal weights[4], int needed )
{
	TESSreal coords[3];

	/* Copy coord data in case the callback changes it. */
	coords[0] = isect->coords[0];
	coords[1] = isect->coords[1];
	coords[2] = isect->coords[2];

	(*tess->callCombine)( coords, weights );
}