#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int* vec3_t ;
typedef  int /*<<< orphan*/  usercmd_t ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_4__ {int* viewangles; } ;
struct TYPE_3__ {int integer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CL_AdjustAngles () ; 
 int /*<<< orphan*/  CL_CmdButtons (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CL_FinishMove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CL_JoystickMove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CL_KeyMove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CL_MouseMove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Com_Memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 size_t PITCH ; 
 int /*<<< orphan*/  SCR_DebugGraph (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VectorCopy (int*,int*) ; 
 size_t YAW ; 
 int /*<<< orphan*/  abs (int) ; 
 TYPE_2__ cl ; 
 TYPE_1__* cl_debugMove ; 

usercmd_t CL_CreateCmd( void ) {
	usercmd_t	cmd;
	vec3_t		oldAngles;

	VectorCopy( cl.viewangles, oldAngles );

	// keyboard angle adjustment
	CL_AdjustAngles ();
	
	Com_Memset( &cmd, 0, sizeof( cmd ) );

	CL_CmdButtons( &cmd );

	// get basic movement from keyboard
	CL_KeyMove( &cmd );

	// get basic movement from mouse
	CL_MouseMove( &cmd );

	// get basic movement from joystick
	CL_JoystickMove( &cmd );

	// check to make sure the angles haven't wrapped
	if ( cl.viewangles[PITCH] - oldAngles[PITCH] > 90 ) {
		cl.viewangles[PITCH] = oldAngles[PITCH] + 90;
	} else if ( oldAngles[PITCH] - cl.viewangles[PITCH] > 90 ) {
		cl.viewangles[PITCH] = oldAngles[PITCH] - 90;
	} 

	// store out the final values
	CL_FinishMove( &cmd );

	// draw debug graphs of turning for mouse testing
	if ( cl_debugMove->integer ) {
		if ( cl_debugMove->integer == 1 ) {
			SCR_DebugGraph( abs(cl.viewangles[YAW] - oldAngles[YAW]), 0 );
		}
		if ( cl_debugMove->integer == 2 ) {
			SCR_DebugGraph( abs(cl.viewangles[PITCH] - oldAngles[PITCH]), 0 );
		}
	}

	return cmd;
}