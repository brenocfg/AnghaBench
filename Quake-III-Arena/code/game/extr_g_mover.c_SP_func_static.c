#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  currentOrigin; } ;
struct TYPE_8__ {int /*<<< orphan*/  trBase; } ;
struct TYPE_9__ {int /*<<< orphan*/  origin; TYPE_1__ pos; } ;
struct TYPE_11__ {TYPE_3__ r; TYPE_2__ s; int /*<<< orphan*/  model; } ;
typedef  TYPE_4__ gentity_t ;

/* Variables and functions */
 int /*<<< orphan*/  InitMover (TYPE_4__*) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trap_SetBrushModel (TYPE_4__*,int /*<<< orphan*/ ) ; 

void SP_func_static( gentity_t *ent ) {
	trap_SetBrushModel( ent, ent->model );
	InitMover( ent );
	VectorCopy( ent->s.origin, ent->s.pos.trBase );
	VectorCopy( ent->s.origin, ent->r.currentOrigin );
}