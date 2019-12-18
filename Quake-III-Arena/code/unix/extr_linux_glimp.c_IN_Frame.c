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
struct TYPE_2__ {int keyCatchers; } ;

/* Variables and functions */
 int /*<<< orphan*/  Cvar_VariableString (char*) ; 
 scalar_t__ Cvar_VariableValue (char*) ; 
 int /*<<< orphan*/  IN_ActivateMouse () ; 
 int /*<<< orphan*/  IN_DeactivateMouse () ; 
 int /*<<< orphan*/  IN_JoyMove () ; 
 int KEYCATCH_CONSOLE ; 
 int /*<<< orphan*/  _3DFX_DRIVER_NAME ; 
 TYPE_1__ cls ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void IN_Frame (void) {

  // bk001130 - from cvs 1.17 (mkv)
  IN_JoyMove(); // FIXME: disable if on desktop?

  if ( cls.keyCatchers & KEYCATCH_CONSOLE )
  {
    // temporarily deactivate if not in the game and
    // running on the desktop
    // voodoo always counts as full screen
    if (Cvar_VariableValue ("r_fullscreen") == 0
        && strcmp( Cvar_VariableString("r_glDriver"), _3DFX_DRIVER_NAME ) )
    {
      IN_DeactivateMouse ();
      return;
    }
  }

  IN_ActivateMouse();
}