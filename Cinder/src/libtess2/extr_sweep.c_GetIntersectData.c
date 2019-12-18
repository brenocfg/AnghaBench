#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__* coords; } ;
typedef  TYPE_1__ TESSvertex ;
typedef  int /*<<< orphan*/  TESStesselator ;
typedef  int /*<<< orphan*/  TESSreal ;

/* Variables and functions */
 int /*<<< orphan*/  CallCombine (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  VertexWeights (TYPE_1__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void GetIntersectData( TESStesselator *tess, TESSvertex *isect,
							 TESSvertex *orgUp, TESSvertex *dstUp,
							 TESSvertex *orgLo, TESSvertex *dstLo )
 /*
 * We've computed a new intersection point, now we need a "data" pointer
 * from the user so that we can refer to this new vertex in the
 * rendering callbacks.
 */
{
	TESSreal weights[4];

	isect->coords[0] = isect->coords[1] = isect->coords[2] = 0;
	VertexWeights( isect, orgUp, dstUp, &weights[0] );
	VertexWeights( isect, orgLo, dstLo, &weights[2] );

	CallCombine( tess, isect, weights, TRUE );
}