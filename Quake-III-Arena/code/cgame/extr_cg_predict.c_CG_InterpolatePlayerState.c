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
typedef  int /*<<< orphan*/  usercmd_t ;
struct TYPE_6__ {int bobCycle; float* origin; float* velocity; int /*<<< orphan*/ * viewangles; } ;
struct TYPE_5__ {scalar_t__ serverTime; TYPE_2__ ps; } ;
typedef  TYPE_1__ snapshot_t ;
typedef  scalar_t__ qboolean ;
typedef  TYPE_2__ playerState_t ;
struct TYPE_7__ {scalar_t__ time; scalar_t__ nextFrameTeleport; TYPE_1__* snap; TYPE_1__* nextSnap; TYPE_2__ predictedPlayerState; } ;

/* Variables and functions */
 int /*<<< orphan*/  LerpAngle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  PM_UpdateViewAngles (TYPE_2__*,int /*<<< orphan*/ *) ; 
 TYPE_3__ cg ; 
 int trap_GetCurrentCmdNumber () ; 
 int /*<<< orphan*/  trap_GetUserCmd (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void CG_InterpolatePlayerState( qboolean grabAngles ) {
	float			f;
	int				i;
	playerState_t	*out;
	snapshot_t		*prev, *next;

	out = &cg.predictedPlayerState;
	prev = cg.snap;
	next = cg.nextSnap;

	*out = cg.snap->ps;

	// if we are still allowing local input, short circuit the view angles
	if ( grabAngles ) {
		usercmd_t	cmd;
		int			cmdNum;

		cmdNum = trap_GetCurrentCmdNumber();
		trap_GetUserCmd( cmdNum, &cmd );

		PM_UpdateViewAngles( out, &cmd );
	}

	// if the next frame is a teleport, we can't lerp to it
	if ( cg.nextFrameTeleport ) {
		return;
	}

	if ( !next || next->serverTime <= prev->serverTime ) {
		return;
	}

	f = (float)( cg.time - prev->serverTime ) / ( next->serverTime - prev->serverTime );

	i = next->ps.bobCycle;
	if ( i < prev->ps.bobCycle ) {
		i += 256;		// handle wraparound
	}
	out->bobCycle = prev->ps.bobCycle + f * ( i - prev->ps.bobCycle );

	for ( i = 0 ; i < 3 ; i++ ) {
		out->origin[i] = prev->ps.origin[i] + f * (next->ps.origin[i] - prev->ps.origin[i] );
		if ( !grabAngles ) {
			out->viewangles[i] = LerpAngle( 
				prev->ps.viewangles[i], next->ps.viewangles[i], f );
		}
		out->velocity[i] = prev->ps.velocity[i] + 
			f * (next->ps.velocity[i] - prev->ps.velocity[i] );
	}

}