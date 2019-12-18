#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_12__ {int /*<<< orphan*/  currentOrigin; int /*<<< orphan*/  ownerNum; int /*<<< orphan*/  svFlags; } ;
struct TYPE_10__ {int /*<<< orphan*/  trDelta; int /*<<< orphan*/  trBase; scalar_t__ trTime; int /*<<< orphan*/  trType; } ;
struct TYPE_11__ {TYPE_1__ pos; int /*<<< orphan*/  number; int /*<<< orphan*/  otherEntityNum; int /*<<< orphan*/  weapon; int /*<<< orphan*/  eType; } ;
struct TYPE_14__ {char* classname; TYPE_4__* client; TYPE_3__ r; TYPE_2__ s; int /*<<< orphan*/ * target_ent; struct TYPE_14__* parent; int /*<<< orphan*/  clipmask; int /*<<< orphan*/  methodOfDeath; int /*<<< orphan*/  think; scalar_t__ nextthink; } ;
typedef  TYPE_5__ gentity_t ;
struct TYPE_15__ {scalar_t__ time; } ;
struct TYPE_13__ {TYPE_5__* hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  ET_MISSILE ; 
 TYPE_5__* G_Spawn () ; 
 int /*<<< orphan*/  MASK_SHOT ; 
 scalar_t__ MISSILE_PRESTEP_TIME ; 
 int /*<<< orphan*/  MOD_GRAPPLE ; 
 int /*<<< orphan*/  SVF_USE_CURRENT_ORIGIN ; 
 int /*<<< orphan*/  SnapVector (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TR_LINEAR ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorNormalize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorScale (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WP_GRAPPLING_HOOK ; 
 int /*<<< orphan*/  Weapon_HookFree ; 
 TYPE_6__ level ; 

gentity_t *fire_grapple (gentity_t *self, vec3_t start, vec3_t dir) {
	gentity_t	*hook;

	VectorNormalize (dir);

	hook = G_Spawn();
	hook->classname = "hook";
	hook->nextthink = level.time + 10000;
	hook->think = Weapon_HookFree;
	hook->s.eType = ET_MISSILE;
	hook->r.svFlags = SVF_USE_CURRENT_ORIGIN;
	hook->s.weapon = WP_GRAPPLING_HOOK;
	hook->r.ownerNum = self->s.number;
	hook->methodOfDeath = MOD_GRAPPLE;
	hook->clipmask = MASK_SHOT;
	hook->parent = self;
	hook->target_ent = NULL;

	hook->s.pos.trType = TR_LINEAR;
	hook->s.pos.trTime = level.time - MISSILE_PRESTEP_TIME;		// move a bit on the very first frame
	hook->s.otherEntityNum = self->s.number; // use to match beam in client
	VectorCopy( start, hook->s.pos.trBase );
	VectorScale( dir, 800, hook->s.pos.trDelta );
	SnapVector( hook->s.pos.trDelta );			// save net bandwidth
	VectorCopy (start, hook->r.currentOrigin);

	self->client->hook = hook;

	return hook;
}