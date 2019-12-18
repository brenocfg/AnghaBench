#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_5__ {scalar_t__ solid; size_t modelindex; int /*<<< orphan*/  number; } ;
struct TYPE_6__ {int /*<<< orphan*/  lerpOrigin; TYPE_1__ currentState; } ;
typedef  TYPE_2__ centity_t ;
struct TYPE_7__ {float** inlineModelMidpoints; } ;

/* Variables and functions */
 scalar_t__ SOLID_BMODEL ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ ,float*,int /*<<< orphan*/ ) ; 
 TYPE_3__ cgs ; 
 int /*<<< orphan*/  trap_S_UpdateEntityPosition (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void CG_SetEntitySoundPosition( centity_t *cent ) {
	if ( cent->currentState.solid == SOLID_BMODEL ) {
		vec3_t	origin;
		float	*v;

		v = cgs.inlineModelMidpoints[ cent->currentState.modelindex ];
		VectorAdd( cent->lerpOrigin, v, origin );
		trap_S_UpdateEntityPosition( cent->currentState.number, origin );
	} else {
		trap_S_UpdateEntityPosition( cent->currentState.number, cent->lerpOrigin );
	}
}