#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ state; int /*<<< orphan*/  keyCatchers; } ;
struct TYPE_4__ {int /*<<< orphan*/  widthInChars; } ;

/* Variables and functions */
 scalar_t__ CA_DISCONNECTED ; 
 int /*<<< orphan*/  CL_StartDemoLoop () ; 
 int /*<<< orphan*/  Con_ClearNotify () ; 
 int /*<<< orphan*/  Field_Clear (TYPE_1__*) ; 
 int /*<<< orphan*/  KEYCATCH_CONSOLE ; 
 TYPE_2__ cls ; 
 TYPE_1__ g_consoleField ; 
 int /*<<< orphan*/  g_console_field_width ; 

void Con_ToggleConsole_f (void) {
	// closing a full screen console restarts the demo loop
	if ( cls.state == CA_DISCONNECTED && cls.keyCatchers == KEYCATCH_CONSOLE ) {
		CL_StartDemoLoop();
		return;
	}

	Field_Clear( &g_consoleField );
	g_consoleField.widthInChars = g_console_field_width;

	Con_ClearNotify ();
	cls.keyCatchers ^= KEYCATCH_CONSOLE;
}