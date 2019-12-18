#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int CVAR_ARCHIVE ; 
 int CVAR_LATCH ; 
 int CVAR_TEMP ; 
 int /*<<< orphan*/  Cmd_AddCommand (char*,int /*<<< orphan*/ ) ; 
 void* Cvar_Get (char*,char*,int) ; 
 int /*<<< orphan*/  IN_Startup () ; 
 int /*<<< orphan*/  MidiInfo_f ; 
 void* in_debugJoystick ; 
 void* in_joyBallScale ; 
 void* in_joystick ; 
 void* in_logitechbug ; 
 void* in_midi ; 
 void* in_midichannel ; 
 void* in_mididevice ; 
 void* in_midiport ; 
 void* in_mouse ; 
 void* joy_threshold ; 

void IN_Init( void ) {
	// MIDI input controler variables
	in_midi					= Cvar_Get ("in_midi",					"0",		CVAR_ARCHIVE);
	in_midiport				= Cvar_Get ("in_midiport",				"1",		CVAR_ARCHIVE);
	in_midichannel			= Cvar_Get ("in_midichannel",			"1",		CVAR_ARCHIVE);
	in_mididevice			= Cvar_Get ("in_mididevice",			"0",		CVAR_ARCHIVE);

	Cmd_AddCommand( "midiinfo", MidiInfo_f );

	// mouse variables
  in_mouse				= Cvar_Get ("in_mouse",					"1",		CVAR_ARCHIVE|CVAR_LATCH);
	in_logitechbug  = Cvar_Get ("in_logitechbug", "0", CVAR_ARCHIVE);

	// joystick variables
	in_joystick				= Cvar_Get ("in_joystick",				"0",		CVAR_ARCHIVE|CVAR_LATCH);
	in_joyBallScale			= Cvar_Get ("in_joyBallScale",			"0.02",		CVAR_ARCHIVE);
	in_debugJoystick		= Cvar_Get ("in_debugjoystick",			"0",		CVAR_TEMP);

	joy_threshold			= Cvar_Get ("joy_threshold",			"0.15",		CVAR_ARCHIVE);

	IN_Startup();
}