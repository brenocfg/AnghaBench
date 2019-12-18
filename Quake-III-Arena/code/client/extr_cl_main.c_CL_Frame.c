#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int integer; } ;
struct TYPE_13__ {scalar_t__ integer; } ;
struct TYPE_12__ {scalar_t__ integer; } ;
struct TYPE_11__ {scalar_t__ state; int keyCatchers; int realFrametime; int frametime; int realtime; int /*<<< orphan*/  framecount; scalar_t__ cddialog; } ;
struct TYPE_10__ {int /*<<< orphan*/  integer; } ;
struct TYPE_9__ {int /*<<< orphan*/  integer; } ;
struct TYPE_8__ {int value; } ;

/* Variables and functions */
 scalar_t__ CA_ACTIVE ; 
 scalar_t__ CA_DISCONNECTED ; 
 int /*<<< orphan*/  CL_CheckForResend () ; 
 int /*<<< orphan*/  CL_CheckTimeout () ; 
 int /*<<< orphan*/  CL_CheckUserinfo () ; 
 int /*<<< orphan*/  CL_SendCmd () ; 
 int /*<<< orphan*/  CL_SetCGameTime () ; 
 int /*<<< orphan*/  Cbuf_ExecuteText (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  Con_RunConsole () ; 
 int /*<<< orphan*/  EXEC_NOW ; 
 int KEYCATCH_UI ; 
 int /*<<< orphan*/  SCR_DebugGraph (double,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCR_RunCinematic () ; 
 int /*<<< orphan*/  SCR_UpdateScreen () ; 
 int /*<<< orphan*/  S_StopAllSounds () ; 
 int /*<<< orphan*/  S_Update () ; 
 int /*<<< orphan*/  UIMENU_MAIN ; 
 int /*<<< orphan*/  UIMENU_NEED_CD ; 
 int /*<<< orphan*/  UI_SET_ACTIVE_MENU ; 
 int /*<<< orphan*/  VM_Call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_7__* cl_avidemo ; 
 TYPE_6__* cl_forceavidemo ; 
 TYPE_5__* cl_timegraph ; 
 TYPE_4__ cls ; 
 TYPE_3__* com_cl_running ; 
 TYPE_2__* com_sv_running ; 
 TYPE_1__* com_timescale ; 
 scalar_t__ qfalse ; 
 int /*<<< orphan*/  uivm ; 

void CL_Frame ( int msec ) {

	if ( !com_cl_running->integer ) {
		return;
	}

	if ( cls.cddialog ) {
		// bring up the cd error dialog if needed
		cls.cddialog = qfalse;
		VM_Call( uivm, UI_SET_ACTIVE_MENU, UIMENU_NEED_CD );
	} else	if ( cls.state == CA_DISCONNECTED && !( cls.keyCatchers & KEYCATCH_UI )
		&& !com_sv_running->integer ) {
		// if disconnected, bring up the menu
		S_StopAllSounds();
		VM_Call( uivm, UI_SET_ACTIVE_MENU, UIMENU_MAIN );
	}

	// if recording an avi, lock to a fixed fps
	if ( cl_avidemo->integer && msec) {
		// save the current screen
		if ( cls.state == CA_ACTIVE || cl_forceavidemo->integer) {
			Cbuf_ExecuteText( EXEC_NOW, "screenshot silent\n" );
		}
		// fixed time for next frame'
		msec = (1000 / cl_avidemo->integer) * com_timescale->value;
		if (msec == 0) {
			msec = 1;
		}
	}
	
	// save the msec before checking pause
	cls.realFrametime = msec;

	// decide the simulation time
	cls.frametime = msec;

	cls.realtime += cls.frametime;

	if ( cl_timegraph->integer ) {
		SCR_DebugGraph ( cls.realFrametime * 0.25, 0 );
	}

	// see if we need to update any userinfo
	CL_CheckUserinfo();

	// if we haven't gotten a packet in a long time,
	// drop the connection
	CL_CheckTimeout();

	// send intentions now
	CL_SendCmd();

	// resend a connection request if necessary
	CL_CheckForResend();

	// decide on the serverTime to render
	CL_SetCGameTime();

	// update the screen
	SCR_UpdateScreen();

	// update audio
	S_Update();

	// advance local effects for next frame
	SCR_RunCinematic();

	Con_RunConsole();

	cls.framecount++;
}