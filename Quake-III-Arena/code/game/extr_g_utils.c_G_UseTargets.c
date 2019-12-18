#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  inuse; int /*<<< orphan*/  (* use ) (TYPE_1__*,TYPE_1__*,TYPE_1__*) ;int /*<<< orphan*/  target; scalar_t__ targetShaderNewName; scalar_t__ targetShaderName; } ;
typedef  TYPE_1__ gentity_t ;
struct TYPE_11__ {double time; } ;

/* Variables and functions */
 int /*<<< orphan*/  AddRemap (scalar_t__,scalar_t__,float) ; 
 int /*<<< orphan*/  BuildShaderStateConfig () ; 
 int /*<<< orphan*/  CS_SHADERSTATE ; 
 int /*<<< orphan*/  FOFS (int /*<<< orphan*/ ) ; 
 TYPE_1__* G_Find (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_Printf (char*) ; 
 TYPE_5__ level ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  targetname ; 
 int /*<<< orphan*/  trap_SetConfigstring (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void G_UseTargets( gentity_t *ent, gentity_t *activator ) {
	gentity_t		*t;
	
	if ( !ent ) {
		return;
	}

	if (ent->targetShaderName && ent->targetShaderNewName) {
		float f = level.time * 0.001;
		AddRemap(ent->targetShaderName, ent->targetShaderNewName, f);
		trap_SetConfigstring(CS_SHADERSTATE, BuildShaderStateConfig());
	}

	if ( !ent->target ) {
		return;
	}

	t = NULL;
	while ( (t = G_Find (t, FOFS(targetname), ent->target)) != NULL ) {
		if ( t == ent ) {
			G_Printf ("WARNING: Entity used itself.\n");
		} else {
			if ( t->use ) {
				t->use (t, ent, activator);
			}
		}
		if ( !ent->inuse ) {
			G_Printf("entity was removed while using targets\n");
			return;
		}
	}
}