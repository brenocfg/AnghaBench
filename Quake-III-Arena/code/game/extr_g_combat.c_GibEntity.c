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
struct TYPE_8__ {scalar_t__ contents; } ;
struct TYPE_9__ {int eFlags; int /*<<< orphan*/  eType; } ;
struct TYPE_10__ {TYPE_1__ r; TYPE_2__ s; int /*<<< orphan*/  takedamage; int /*<<< orphan*/  classname; struct TYPE_10__* activator; int /*<<< orphan*/  inuse; } ;
typedef  TYPE_3__ gentity_t ;

/* Variables and functions */
 int EF_KAMIKAZE ; 
 int /*<<< orphan*/  ET_INVISIBLE ; 
 int /*<<< orphan*/  EV_GIB_PLAYER ; 
 int /*<<< orphan*/  G_AddEvent (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  G_FreeEntity (TYPE_3__*) ; 
 int MAX_GENTITIES ; 
 TYPE_3__* g_entities ; 
 int /*<<< orphan*/  qfalse ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

void GibEntity( gentity_t *self, int killer ) {
	gentity_t *ent;
	int i;

	//if this entity still has kamikaze
	if (self->s.eFlags & EF_KAMIKAZE) {
		// check if there is a kamikaze timer around for this owner
		for (i = 0; i < MAX_GENTITIES; i++) {
			ent = &g_entities[i];
			if (!ent->inuse)
				continue;
			if (ent->activator != self)
				continue;
			if (strcmp(ent->classname, "kamikaze timer"))
				continue;
			G_FreeEntity(ent);
			break;
		}
	}
	G_AddEvent( self, EV_GIB_PLAYER, killer );
	self->takedamage = qfalse;
	self->s.eType = ET_INVISIBLE;
	self->r.contents = 0;
}