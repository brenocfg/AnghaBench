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
struct TYPE_7__ {float fraction; int /*<<< orphan*/  contents; int /*<<< orphan*/  surfaceFlags; } ;
struct TYPE_8__ {TYPE_1__ trace; } ;
typedef  TYPE_2__ traceWork_t ;
struct TYPE_9__ {int /*<<< orphan*/  contents; int /*<<< orphan*/  surfaceFlags; int /*<<< orphan*/  pc; } ;
typedef  TYPE_3__ cPatch_t ;

/* Variables and functions */
 int /*<<< orphan*/  CM_TraceThroughPatchCollide (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_patch_traces ; 

void CM_TraceThroughPatch( traceWork_t *tw, cPatch_t *patch ) {
	float		oldFrac;

	c_patch_traces++;

	oldFrac = tw->trace.fraction;

	CM_TraceThroughPatchCollide( tw, patch->pc );

	if ( tw->trace.fraction < oldFrac ) {
		tw->trace.surfaceFlags = patch->surfaceFlags;
		tw->trace.contents = patch->contents;
	}
}