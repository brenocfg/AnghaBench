#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ value; } ;

/* Variables and functions */
 int CVAR_ARCHIVE ; 
 int CVAR_LATCH ; 
 int CVAR_TEMP ; 
 int /*<<< orphan*/  Com_Printf (char*) ; 
 void* Cvar_Get (char*,char*,int) ; 
 int /*<<< orphan*/  IN_StartupJoystick () ; 
 void* in_dgamouse ; 
 void* in_joystick ; 
 void* in_joystickDebug ; 
 TYPE_1__* in_mouse ; 
 void* in_nograb ; 
 void* in_subframe ; 
 void* joy_threshold ; 
 int /*<<< orphan*/  mouse_avail ; 
 int /*<<< orphan*/  qfalse ; 
 int /*<<< orphan*/  qtrue ; 

void IN_Init(void) {
	Com_Printf ("\n------- Input Initialization -------\n");
  // mouse variables
  in_mouse = Cvar_Get ("in_mouse", "1", CVAR_ARCHIVE);
  in_dgamouse = Cvar_Get ("in_dgamouse", "1", CVAR_ARCHIVE);
	
	// turn on-off sub-frame timing of X events
	in_subframe = Cvar_Get ("in_subframe", "1", CVAR_ARCHIVE);
	
	// developer feature, allows to break without loosing mouse pointer
	in_nograb = Cvar_Get ("in_nograb", "0", 0);

  // bk001130 - from cvs.17 (mkv), joystick variables
  in_joystick = Cvar_Get ("in_joystick", "0", CVAR_ARCHIVE|CVAR_LATCH);
  // bk001130 - changed this to match win32
  in_joystickDebug = Cvar_Get ("in_debugjoystick", "0", CVAR_TEMP);
  joy_threshold = Cvar_Get ("joy_threshold", "0.15", CVAR_ARCHIVE); // FIXME: in_joythreshold

  if (in_mouse->value)
    mouse_avail = qtrue;
  else
    mouse_avail = qfalse;

  IN_StartupJoystick( ); // bk001130 - from cvs1.17 (mkv)
	Com_Printf ("------------------------------------\n");
}