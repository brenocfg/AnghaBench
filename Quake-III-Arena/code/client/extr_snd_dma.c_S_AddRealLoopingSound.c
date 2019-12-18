#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vec3_t ;
struct TYPE_5__ {scalar_t__ inMemory; int /*<<< orphan*/  soundName; int /*<<< orphan*/  soundLength; } ;
typedef  TYPE_1__ sfx_t ;
typedef  size_t sfxHandle_t ;
struct TYPE_6__ {scalar_t__ doppler; scalar_t__ kill; int /*<<< orphan*/  active; TYPE_1__* sfx; int /*<<< orphan*/  velocity; int /*<<< orphan*/  origin; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Com_Printf (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  ERR_DROP ; 
 int /*<<< orphan*/  S_COLOR_YELLOW ; 
 int /*<<< orphan*/  S_memoryLoad (TYPE_1__*) ; 
 int /*<<< orphan*/  VectorCopy (int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 TYPE_3__* loopSounds ; 
 scalar_t__ qfalse ; 
 int /*<<< orphan*/  qtrue ; 
 TYPE_1__* s_knownSfx ; 
 size_t s_numSfx ; 
 scalar_t__ s_soundMuted ; 
 int /*<<< orphan*/  s_soundStarted ; 

void S_AddRealLoopingSound( int entityNum, const vec3_t origin, const vec3_t velocity, sfxHandle_t sfxHandle ) {
	sfx_t *sfx;

	if ( !s_soundStarted || s_soundMuted ) {
		return;
	}

	if ( sfxHandle < 0 || sfxHandle >= s_numSfx ) {
		Com_Printf( S_COLOR_YELLOW, "S_AddRealLoopingSound: handle %i out of range\n", sfxHandle );
		return;
	}

	sfx = &s_knownSfx[ sfxHandle ];

	if (sfx->inMemory == qfalse) {
		S_memoryLoad(sfx);
	}

	if ( !sfx->soundLength ) {
		Com_Error( ERR_DROP, "%s has length 0", sfx->soundName );
	}
	VectorCopy( origin, loopSounds[entityNum].origin );
	VectorCopy( velocity, loopSounds[entityNum].velocity );
	loopSounds[entityNum].sfx = sfx;
	loopSounds[entityNum].active = qtrue;
	loopSounds[entityNum].kill = qfalse;
	loopSounds[entityNum].doppler = qfalse;
}