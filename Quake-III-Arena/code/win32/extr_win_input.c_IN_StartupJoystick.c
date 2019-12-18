#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  integer; } ;
struct TYPE_6__ {int dwSize; int wCaps; int /*<<< orphan*/  wMaxAxes; int /*<<< orphan*/  wNumAxes; int /*<<< orphan*/  wMaxButtons; int /*<<< orphan*/  wNumButtons; int /*<<< orphan*/  szRegKey; int /*<<< orphan*/  szOEMVxD; int /*<<< orphan*/  szPname; int /*<<< orphan*/  dwFlags; } ;
struct TYPE_7__ {int id; int /*<<< orphan*/  avail; scalar_t__ oldpovstate; scalar_t__ oldbuttonstate; TYPE_1__ jc; TYPE_1__ ji; } ;
typedef  scalar_t__ MMRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Com_Printf (char*,...) ; 
 int JOYCAPS_HASPOV ; 
 scalar_t__ JOYERR_NOERROR ; 
 int /*<<< orphan*/  JOY_RETURNCENTERED ; 
 TYPE_4__* in_joystick ; 
 TYPE_3__ joy ; 
 scalar_t__ joyGetDevCaps (int,TYPE_1__*,int) ; 
 int joyGetNumDevs () ; 
 scalar_t__ joyGetPosEx (int,TYPE_1__*) ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

void IN_StartupJoystick (void) { 
	int			numdevs;
	MMRESULT	mmr;

	// assume no joystick
	joy.avail = qfalse; 

	if (! in_joystick->integer ) {
		Com_Printf ("Joystick is not active.\n");
		return;
	}

	// verify joystick driver is present
	if ((numdevs = joyGetNumDevs ()) == 0)
	{
		Com_Printf ("joystick not found -- driver not present\n");
		return;
	}

	// cycle through the joystick ids for the first valid one
	mmr = 0;
	for (joy.id=0 ; joy.id<numdevs ; joy.id++)
	{
		Com_Memset (&joy.ji, 0, sizeof(joy.ji));
		joy.ji.dwSize = sizeof(joy.ji);
		joy.ji.dwFlags = JOY_RETURNCENTERED;

		if ((mmr = joyGetPosEx (joy.id, &joy.ji)) == JOYERR_NOERROR)
			break;
	} 

	// abort startup if we didn't find a valid joystick
	if (mmr != JOYERR_NOERROR)
	{
		Com_Printf ("joystick not found -- no valid joysticks (%x)\n", mmr);
		return;
	}

	// get the capabilities of the selected joystick
	// abort startup if command fails
	Com_Memset (&joy.jc, 0, sizeof(joy.jc));
	if ((mmr = joyGetDevCaps (joy.id, &joy.jc, sizeof(joy.jc))) != JOYERR_NOERROR)
	{
		Com_Printf ("joystick not found -- invalid joystick capabilities (%x)\n", mmr); 
		return;
	}

	Com_Printf( "Joystick found.\n" );
	Com_Printf( "Pname: %s\n", joy.jc.szPname );
	Com_Printf( "OemVxD: %s\n", joy.jc.szOEMVxD );
	Com_Printf( "RegKey: %s\n", joy.jc.szRegKey );

	Com_Printf( "Numbuttons: %i / %i\n", joy.jc.wNumButtons, joy.jc.wMaxButtons );
	Com_Printf( "Axis: %i / %i\n", joy.jc.wNumAxes, joy.jc.wMaxAxes );
	Com_Printf( "Caps: 0x%x\n", joy.jc.wCaps );
	if ( joy.jc.wCaps & JOYCAPS_HASPOV ) {
		Com_Printf( "HASPOV\n" );
	} else {
		Com_Printf( "no POV\n" );
	}

	// old button and POV states default to no buttons pressed
	joy.oldbuttonstate = 0;
	joy.oldpovstate = 0;

	// mark the joystick as available
	joy.avail = qtrue; 
}