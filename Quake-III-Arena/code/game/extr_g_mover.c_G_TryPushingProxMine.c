#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/ * vec3_t ;
typedef  int qboolean ;
struct TYPE_11__ {int /*<<< orphan*/ * currentOrigin; } ;
struct TYPE_9__ {int /*<<< orphan*/ * trBase; } ;
struct TYPE_10__ {TYPE_1__ pos; } ;
struct TYPE_12__ {TYPE_3__ r; TYPE_2__ s; } ;
typedef  TYPE_4__ gentity_t ;

/* Variables and functions */
 int /*<<< orphan*/  AngleVectors (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DotProduct (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int G_CheckProxMinePosition (TYPE_4__*) ; 
 int /*<<< orphan*/  VectorAdd (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VectorSubtract (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trap_LinkEntity (TYPE_4__*) ; 
 int /*<<< orphan*/ * vec3_origin ; 

qboolean G_TryPushingProxMine( gentity_t *check, gentity_t *pusher, vec3_t move, vec3_t amove ) {
	vec3_t		forward, right, up;
	vec3_t		org, org2, move2;
	int ret;

	// we need this for pushing things later
	VectorSubtract (vec3_origin, amove, org);
	AngleVectors (org, forward, right, up);

	// try moving the contacted entity 
	VectorAdd (check->s.pos.trBase, move, check->s.pos.trBase);

	// figure movement due to the pusher's amove
	VectorSubtract (check->s.pos.trBase, pusher->r.currentOrigin, org);
	org2[0] = DotProduct (org, forward);
	org2[1] = -DotProduct (org, right);
	org2[2] = DotProduct (org, up);
	VectorSubtract (org2, org, move2);
	VectorAdd (check->s.pos.trBase, move2, check->s.pos.trBase);

	ret = G_CheckProxMinePosition( check );
	if (ret) {
		VectorCopy( check->s.pos.trBase, check->r.currentOrigin );
		trap_LinkEntity (check);
	}
	return ret;
}