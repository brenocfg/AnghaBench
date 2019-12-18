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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int keyCatchers; } ;
struct TYPE_5__ {scalar_t__ hWnd; } ;
struct TYPE_4__ {scalar_t__ mouseStartupDelayed; int /*<<< orphan*/  mouseInitialized; } ;

/* Variables and functions */
 int /*<<< orphan*/  Com_Printf (char*) ; 
 int /*<<< orphan*/  Cvar_VariableString (char*) ; 
 scalar_t__ Cvar_VariableValue (char*) ; 
 int /*<<< orphan*/  IN_ActivateMouse () ; 
 int /*<<< orphan*/  IN_DeactivateMouse () ; 
 int /*<<< orphan*/  IN_JoyMove () ; 
 int /*<<< orphan*/  IN_MouseMove () ; 
 int /*<<< orphan*/  IN_StartupMouse () ; 
 int KEYCATCH_CONSOLE ; 
 int /*<<< orphan*/  _3DFX_DRIVER_NAME ; 
 TYPE_3__ cls ; 
 TYPE_2__ g_wv ; 
 int /*<<< orphan*/  in_appactive ; 
 scalar_t__ qfalse ; 
 TYPE_1__ s_wmv ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void IN_Frame (void) {
	// post joystick events
	IN_JoyMove();

	if ( !s_wmv.mouseInitialized ) {
    if (s_wmv.mouseStartupDelayed && g_wv.hWnd)
		{
			Com_Printf("Proceeding with delayed mouse init\n");
      IN_StartupMouse();
			s_wmv.mouseStartupDelayed = qfalse;
		}
		return;
	}

	if ( cls.keyCatchers & KEYCATCH_CONSOLE ) {
		// temporarily deactivate if not in the game and
		// running on the desktop
		// voodoo always counts as full screen
		if (Cvar_VariableValue ("r_fullscreen") == 0
			&& strcmp( Cvar_VariableString("r_glDriver"), _3DFX_DRIVER_NAME) )	{
			IN_DeactivateMouse ();
			return;
		}
	}

	if ( !in_appactive ) {
		IN_DeactivateMouse ();
		return;
	}

	IN_ActivateMouse();

	// post events to the system que
	IN_MouseMove();

}